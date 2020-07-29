#include "../inc/uchat.h"

static bool parse_object(cJSON *root, t_use_mutex *param) {
    // show who online
    mx_whoonline(root, param);
    // отсылаю новые и старые чаты 
    mx_chats_send(root, param);
    // тут буду отсылать последние сообщение по запросу пользователя с их текст-айдишниками
    mx_slast_mess(root, param);
    // на изменение сообщения
    // mx_change_mess(root, param);
    // на удаление сообщения
    // mx_dell_mess();
    // sending info about user which you want
    // mx_usr_prof(root, param);
    // changing my profile
    mx_change_prof(root, param);
    // delete account 
    if (mx_delete(param, root) == true)
        return false;
    //send mess and adding to db/ and PAPA_BOT
    mx_send_mess(root, param);
    return true;
}

static void *some_sending(void *parametr) {
    t_use_mutex *param = (t_use_mutex *) malloc(sizeof(t_use_mutex));
    t_use_mutex *tmp = (t_use_mutex *) parametr;
    char buff[4096];
    int ret = 0;
    cJSON* request_json = NULL;

    param->mutex = tmp->mutex;
    param->cli_fd = tmp->cli_fd;
    param->my_ssl = tmp->my_ssl;
    param->ssl_list = tmp->ssl_list;
    param->fd_log = tmp->fd_log;
    if (mx_registr(param) == false) 
        pthread_exit(&ret);
    while (SSL_read(param->my_ssl, buff, 4096) > 0) {
        request_json = cJSON_Parse(buff);
        if (parse_object(request_json, param) == false) {
            cJSON_Delete(request_json);
            break;
        }
        bzero(buff, 4096);
    }
    mx_delete_socket(param);
    write(param->fd_log, "EXIT FROM THREAD\n", 17);
    free(param);
    pthread_exit(&ret);
}

static int create_log() {
    int file_descr = 0;
    file_descr = open("uchat_server.log",
                    O_CREAT | O_RDWR | O_APPEND, S_IREAD | S_IWRITE);
    return file_descr;
}

static void demonize() {  
    if (fork() != 0)
        exit(0);
    umask(0);
    setsid();
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

}

int main(int argc, char *argv[]) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    int clen = sizeof(cli_addr);
    pthread_t thread; 
    t_use_mutex param; //creting mutex
    pthread_mutex_t mute; // mutex

    demonize();
    signal(SIGPIPE, SIG_IGN);
    param.fd_log = create_log();
    pthread_mutex_init(&mute, NULL);
    param.mutex = &mute;
    mx_tables();
    if (argc > 1)
        serv_addr.sin_port = htons(atoi(argv[1]));
    else 
        exit(1);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_family = AF_INET;
    if (bind(server_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        exit(2); 
    listen(server_fd, USERS);
    SSL_CTX *ctx = mx_initserverctx();
    SSL *ssl = NULL;
    mx_loadcertificates(ctx, "CertFile.pem", "CertFile.pem");
    t_list * list = NULL;
    while (1) {
        if ((param.cli_fd = accept(server_fd, (struct sockaddr *) &cli_addr, (socklen_t *) &clen)) < 0)
            exit(3);
        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, param.cli_fd);
        if (SSL_accept(ssl) == -1)
            ERR_print_errors_fp(stderr);
        param.my_ssl = ssl;
        param.ssl_list = &list;
        write(param.fd_log, "USER CONNECTED: ", 16);
        write(param.fd_log, inet_ntoa(cli_addr.sin_addr), strlen(inet_ntoa(cli_addr.sin_addr)));
        write(param.fd_log, "\n", 1);
        if (pthread_create(&thread, NULL, some_sending, (void *) &param) < 0)
            exit(2);
    }
    pthread_mutex_destroy(&mute);
    SSL_CTX_free(ctx);
    return 0;
}
