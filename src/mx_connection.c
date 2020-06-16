#include "../inc/uchat.h"

static void send_message(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;
    char *str; //строка которую отправляем Лехе
    char *message = (char *)gtk_entry_get_text(GTK_ENTRY(widge->command_line)); //считываем данные с ввода

    gtk_label_set_text(widge->message, ""); //потм убрать, обнуляем лейбл

    if (strlen(message) == 0) { //если пустая строка, ничего не делать
        printf("Are you kidding me?\n");
    }
    else {
        asprintf(&str, "{\"FROM\" : \"%s\",\"TO\":\"%s\",\"MESS\":\"%s\"}\n", widge->login, widge->to, message); //записываем в строку данные для Лехи
        write(widge->sockfd, str, strlen(str)); //отпрвляем Лехе данные
        gtk_label_set_text(widge->message, message); //заполняем лейбл текстом
        gtk_entry_set_text(GTK_ENTRY(widge->command_line), ""); //обнуляем вводимую строку, следовательно обнуляеться message
    }
} 

// static void *Write(void *dat) {
//     t_userdata *data = (t_userdata *) dat;
//     char *buff;
//     char *str;
//     //data->widge = (t_widget_my *)malloc(sizeof(t_widget_my));


//     while(1) {
//         //g_signal_connect (widge->chat, "clicked", G_CALLBACK(in_chat), widge);
//         //buff = (data->widge)->str;
//         buff[strlen(buff) - 1] = '\0';
//         str = (char *)malloc(sizeof(char) * (strlen(buff) + strlen(data->login) + strlen(data->to) + 10));
//         sprintf(str, "{\"FROM\" : \"%s\",\"TO\":\"%s\",\"MESS\":\"%s\"}", data->login, data->to, buff);
//         write(data->sockfd, str, strlen(str));
//         free(str);
//     }
//     int exit;
//     pthread_exit(&exit);
//     return (void*)0;
// }

// static void *Read(void *dat) {
//     t_userdata *data = (t_userdata *) dat;
//     char buff[1024];
//     int len;

//     while(1) {
//         len = read(data->sockfd, buff, 1024);
//         write(1, buff, strlen(buff));
//         //gtk_entry_set_text(GTK_ENTRY(widge->vivod), buff);
//     }
//     int exit;
//     pthread_exit(&exit);
//     return (void*)0;
// }

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
    widge->sockfd = sockfd;

    asprintf(&str, "{\"LOGIN\":\"%s\",\"PASS\":\"%s\"}\n", widge->login, widge->pass); //записываем в строку логин и пароль для Лехи
    write(widge->sockfd, str, strlen(str)); //отпраявляем логин и пароль Лехе
    free(str);

    // char buff[1024];
    // read(data->sockfd, buff, 1024);
    mx_chat_win(widge); //открываем окно чата
    
    g_signal_connect (widge->setting, "clicked", G_CALLBACK(send_message), widge);

    //if (atoi(buff) == 1) {
        //gtk_entry_set_text(GTK_ENTRY(widge->vivod), "");
        // pthread_create(&preg, 0, Write, data);
        // pthread_create(&preg, 0, Read, data);
    //}
    //else
    //    printf("WRONG PASSWORD OR LOGIN");
}
