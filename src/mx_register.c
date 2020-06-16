#include "../inc/uchat.h"

int mx_register(char *login, char *pass, t_widget_my *widge) {
    int sockfd;
    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    pthread_t preg;
    char *str;


    portno = 6969;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    server = gethostbyname("10.111.9.5");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    printf("ffgdf\n");
    serv_addr.sin_family = AF_INET;
    printf("ffgdf\n");
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    printf("ffgdf\n");
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
    asprintf(&str, "{\"REG\":true,\"LOGIN\":\"%s\",\"PASS\":\"%s\"}\n", login, pass); //записываем в строку логин и пароль для Лехи
    write(sockfd, str, strlen(str)); //отпраявляем логин и пароль Лехе
    free(str);

    return 1;
}
