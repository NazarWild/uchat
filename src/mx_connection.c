#include "../inc/uchat.h"

static char *read_line(void) {
    char *line = NULL;
    size_t bufsize = 0;

    getline(&line, &bufsize, stdin);
    return line;
}

static void *Write(void *dat) {
    t_userdata *data = (t_userdata *) dat;
    char *buff;
    char *str = (char *)malloc(sizeof(char) * 40);
    while(1) {
        buff = read_line();
        buff[strlen(buff) - 1] = '\0';
        sprintf(str, "{\"FROM\" : \"%s\",\"TO\":\"%s\",\"MESS\":\"%s\"}", data->login, data->to, buff);
        write(data->sockfd, str, strlen(str));
    }
    int exit;
    pthread_exit(&exit);
    return (void*)0;
}

static void *Read(void *dat) {
    t_userdata *data = (t_userdata *) dat;
    char buff[1024];
    int len;

    while(1) {
        len = read(data->sockfd, buff, 1024);
        write(1, buff, len);
    }
    int exit;
    pthread_exit(&exit);
    return (void*)0;
}

void mx_connection(t_widget_my *widge, t_userdata *data) {
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    pthread_t preg;
    
    portno = 6969;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
     
    server = gethostbyname("10.111.9.1");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
    data->sockfd = sockfd;
    while (1) {
        pthread_create(&preg, 0, Write, data);
        pthread_create(&preg, 0, Read, data);
    }
}
