#include "../inc/uchat.h"

static bool parse_object(cJSON *root, t_use_mutex *param) {
    // тут буду смотреть кому сообщение и смотрерть через бд его дескриптор, после чего отсылать сообщение 
    // если дескриптор -1, то пользователь не в сети и буду записывать в бд сообщение сразу 
    // после чего как только он зайдет надо будет подгружать сообщения 
    //show who online
    mx_whoonline(param);
    //delete account 
    if (mx_delete(param, root) == true)
        return false;
    //send mess and adding to db/ and PAPA_BOT
    mx_send_mess(root, param);

    cJSON_Delete(root);
    return true;
}

static void *some_sending(void *parametr) {
    t_use_mutex *param = (t_use_mutex *) malloc(sizeof(t_use_mutex));
    t_use_mutex *tmp = (t_use_mutex *) parametr;
    char buff[2048];
    int ret = 0;
    cJSON* request_json = NULL;

    param->mutex = tmp->mutex;
    param->cli_fd = tmp->cli_fd;
    param->my_ssl = tmp->my_ssl;
    param->ssl_list = tmp->ssl_list;

    if (mx_registr(param) == false) //otpravliaem cJSON chto ne poluchilos voiti i zacrivaem potok
        pthread_exit(&ret);

    // tut nado podgrughat s db v client
    //posle chego podgrugat vse chati, to est CHATS:
    mx_chats_send(param);
    while (SSL_read(param->my_ssl, buff, 2048) > 0) {
    // while(read(param->cli_fd, buff, 2048) > 0) { //tut budu parsit info from JSON file
        request_json = cJSON_Parse(buff);
        if (parse_object(request_json, param) == false)
            break;
        bzero(buff, 2048);
    }
    mx_delete_socket(param);
    printf("EXIT FROM THREAD\n");
    pthread_exit(&ret);
}

int main(int argc, char *argv[]) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    int clen = sizeof(cli_addr);
    pthread_t thread; 

    t_use_mutex param; //creting mutex
    pthread_mutex_t mute; // mutex

    pthread_mutex_init(&mute, NULL);
    param.mutex = &mute;

    mx_tables();
    if (argc > 1)
        inet_aton(argv[1], &serv_addr.sin_addr);
    else {
        printf("ENTER IP OF SERVER");
        exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("BINDING ERROR");
        exit(2);
    }
    listen(server_fd, USERS);
    SSL_CTX *ctx = mx_initserverctx();
    SSL *ssl = NULL;
    mx_loadcertificates(ctx, "CertFile.pem", "CertFile.pem");
    t_list * list = NULL;

    while (1) {
        if ((param.cli_fd = accept(server_fd, (struct sockaddr *) &cli_addr, (socklen_t *) &clen)) < 0) {
            perror("ACCEPTING ERROR");
            exit(3);
        }
        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, param.cli_fd);
        if (SSL_accept(ssl) == -1)     /* do SSL-protocol accept */
            ERR_print_errors_fp(stderr);
        param.my_ssl = ssl;
        param.ssl_list = &list;
        printf("THIS SHIT CONNECTED: %s\n", inet_ntoa(cli_addr.sin_addr));
        if (pthread_create(&thread, NULL, some_sending, (void *) &param) < 0) {
            perror("CREATING THREAD ERROR");
            exit(2);
        }
    }
    pthread_mutex_destroy(&mute);
    SSL_CTX_free(ctx);
    return 0;
}
