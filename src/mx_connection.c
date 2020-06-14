#include "../inc/uchat.h"

static void in_chat(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my*)data;

    const gchar *str = gtk_entry_get_text(GTK_ENTRY(widge->enter));
    widge->str = strdup(str);
}

static void *Write(void *dat) {
    t_userdata *data = (t_userdata *) dat;
    char *buff;
    char *str;
    //data->widge = (t_widget_my *)malloc(sizeof(t_widget_my));


    while(1) {
        //g_signal_connect (widge->chat, "clicked", G_CALLBACK(in_chat), widge);
        //buff = (data->widge)->str;
        buff[strlen(buff) - 1] = '\0';
        str = (char *)malloc(sizeof(char) * (strlen(buff) + strlen(data->login) + strlen(data->to) + 10));
        sprintf(str, "{\"FROM\" : \"%s\",\"TO\":\"%s\",\"MESS\":\"%s\"}", data->login, data->to, buff);
        write(data->sockfd, str, strlen(str));
        free(str);
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
        write(1, buff, strlen(buff));
        //gtk_entry_set_text(GTK_ENTRY(widge->vivod), buff);
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
    char *str;

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
    data->sockfd = sockfd;
    str = (char *)malloc(sizeof(char) * (strlen(data->login) + strlen(data->pass) + 11));
    sprintf(str, "{\"LOGIN\":\"%s\",\"PASS\":\"%s\"}", data->login, data->pass);
    write(data->sockfd, str, strlen(str));
    free(str);

    char buff[1024];
    read(data->sockfd, buff, 1024);
    mx_chat_win(widge);
    //if (atoi(buff) == 1) {
        //gtk_entry_set_text(GTK_ENTRY(widge->vivod), "");
        //pthread_create(&preg, 0, Write, data);
        pthread_create(&preg, 0, Read, data);
    //}
    //else
    //    printf("WRONG PASSWORD OR LOGIN");
}
