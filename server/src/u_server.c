#include "../inc/uchat.h"

static bool parse_object(cJSON *root, int fd) {
    // тут буду смотреть кому сообщение и смотрерть через бд его дескриптор, после чего отсылать сообщение 
    // если дескриптор -1, то пользователь не в сети и буду записывать в бд сообщение сразу 
    // после чего как только он зайдет надо будет подгружать сообщения 



    //show who online
    mx_whoonline(fd);

    //delete account 
    if (mx_delete(fd, root) == true) {
        return false;
    }
    
    //send mess and adding to db/ and PAPA_BOT
    mx_send_mess(root, fd);

    cJSON_Delete(root);
    return true;
}

static void *some_sending(void *parametr) {
    use_mutex_t *param = (use_mutex_t *) parametr;
    int fd = param->cli_fd;
    char buff[1024];
    int ret = 0;
    cJSON* request_json = NULL;

    if (mx_registr(fd) == false) //otpravliaem cJSON chto ne poluchilos voiti i zacrivaem potok
        pthread_exit(&ret);

    // tut nado podgrughat s db v client

    while(read(fd, buff, 1024) > 0) { //tut budu parsit info from JSON file
        
        request_json = cJSON_Parse(buff);
        if (parse_object(request_json, fd) == false)
            break;
        bzero(buff, 1024);
    }
    mx_delete_socket(fd);
    printf("EXIT FROM THREAD\n");
    pthread_exit(&ret);
}

int main(int argc, char *argv[]) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    int clen = sizeof(cli_addr);
    pthread_t thread; 


    use_mutex_t param; //creting mutex

    pthread_mutex_init(&(param.mutex), NULL); //mutex init
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

    while (1) {
        if ((param.cli_fd = accept(server_fd, (struct sockaddr *) &cli_addr, (socklen_t *) &clen)) < 0) {
            perror("ACCEPTING ERROR");
            exit(3);
        }
        printf("THIS SHIT CONNECTED: %s\n", inet_ntoa(cli_addr.sin_addr));
        if (pthread_create(&thread, NULL, some_sending, (void *) &param) < 0) {
            perror("CREATING THREAD ERROR");
            exit(2);
        }
    }
    return 0;
}
