#include "../inc/uchat.h"

static char *read_line(void) {
    char *line = NULL;
    size_t bufsize = 0;

    getline(&line, &bufsize, stdin);
    return line;
}

static void *Write(void *sock) {
    int socket = *((int*)sock);
    char *buff;

    while(1) {
        buff = read_line();
        write(socket, buff, strlen(buff));
    }
    return (void*)0;
}

static void *Read(void *sock) {
    int socket = *((int*)sock);
    char buff[1024];
    int len;

    while(1) {
        len = read(socket, buff, 1024);
        write(1, buff, len);
    }
    return (void*)0;
}

void mx_connection(void) {
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
     
    server = gethostbyname("10.111.9.3");
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
    while (1) {
        pthread_create(&preg, 0, Write, &sockfd);
        pthread_create(&preg, 0, Read, &sockfd);
    }
}
