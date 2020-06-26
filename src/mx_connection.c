#include "../inc/uchat.h"

static void send_message(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;
    char *str; //строка которую отправляем Лехе
    char *message = (char *)gtk_entry_get_text(GTK_ENTRY(widge->command_line)); //считываем данные с ввода

    // gtk_label_set_text(widge->message, ""); //потм убрать, обнуляем лейбл

    if (strlen(message) == 0) { //если пустая строка, ничего не делать
        printf("Are you kidding me?\n");
    }
    else {
        mx_message_to(widge, message);
        asprintf(&str, "{\"FROM\" : \"%s\",\"TO\":\"%s\",\"MESS\":\"%s\"}\n", widge->login, widge->to, message); //записываем в строку данные для Лехи
        write(widge->sockfd, str, strlen(str)); //отпрвляем Лехе данные
        // gtk_label_set_text(widge->message, message); //заполняем лейбл текстом
        gtk_entry_set_text(GTK_ENTRY(widge->command_line), ""); //обнуляем вводимую строку, следовательно обнуляеться message
    }
}

static void *Read(void *dat) {
    t_widget_my *widge = (t_widget_my *) dat;
    char buff[1024];
    int len;

    while(1) {
        len = read(widge->sockfd, buff, 1024);
        mx_message_to(widge, buff);
        // gtk_label_set_text(widge->message, buff); //заполняем лейбл текстом
    }
    int exit;
    pthread_exit(&exit);
    return (void*)0;
}

void mx_connection(t_widget_my *widge) {
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

    server = gethostbyname("10.111.8.10");
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
    widge->sockfd = sockfd;

    asprintf(&str, "{\"LOGIN\":\"%s\",\"PASS\":\"%s\"}\n", widge->login, widge->pass); //записываем в строку логин и пароль для Лехи
    write(widge->sockfd, str, strlen(str)); //отпраявляем логин и пароль Лехе
    free(str);

    char buff[1024];
    read(sockfd, buff, 1024);
    gtk_widget_hide(GTK_WIDGET(widge->wrong_login));
    printf("%s\n",buff);
    if (atoi(buff) != -1) {
        mx_chat_win(widge);
        g_signal_connect (widge->send_button, "clicked", G_CALLBACK(send_message), widge);
        pthread_create(&preg, 0, Read, widge);
    }
    else {
        gtk_widget_show(GTK_WIDGET(widge->wrong_login));
        gtk_label_set_text(widge->wrong_login, "WRONG LOGIN OR PASSWORD");
    }
}
