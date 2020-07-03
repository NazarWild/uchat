    #include "../inc/uchat.h"

    void theme_1(GtkWidget* widget, void *dat) {
        t_widget_my *widge = (t_widget_my *)dat;

        gtk_css_provider_load_from_path (widge->dark, "src/light.css", NULL);
    }

    void theme_2(GtkWidget* widget, void *dat) {
        t_widget_my *widge = (t_widget_my *)dat;

        gtk_css_provider_load_from_path (widge->dark, "src/theme.css", NULL);
    }

    void theme_3(GtkWidget* widget, void *dat) {
        t_widget_my *widge = (t_widget_my *)dat;

        gtk_widget_hide(widge->win_sett);
        gtk_widget_show_all(widge->main_chat);
    }


    void setting_win(GtkWidget* widget, void *dat) {
        t_widget_my *widge = (t_widget_my *)dat;

        g_signal_connect (widge->theme_1, "clicked", G_CALLBACK(theme_1), widge);
        g_signal_connect (widge->theme_2, "clicked", G_CALLBACK(theme_2), widge);
        g_signal_connect (widge->theme_3, "clicked", G_CALLBACK(theme_3), widge);
        gtk_widget_hide(widge->main_chat);
        gtk_widget_show_all(widge->win_sett);
    }

    static void send_message(GtkWidget* widget, void *dat) {
        t_widget_my *widge = (t_widget_my *)dat;
        char *str; //строка которую отправляем Лехе
        char *message = (char *)gtk_entry_get_text(GTK_ENTRY(widge->command_line)); //считываем данные с ввода

        if (strlen(message) == 0) { //если пустая строка, ничего не делать
            printf("Are you kidding me?\n");
        }
        else {
            mx_message_to(widge, message);
            asprintf(&str, "{\"FROM\" : \"%s\",\"TO\":\"%s\",\"MESS\":\"%s\"}\n", widge->login, widge->to, message); //записываем в строку данные для Лехи
            write(widge->sockfd, str, strlen(str)); //отпрвляем Лехе данные
            gtk_entry_set_text(GTK_ENTRY(widge->command_line), ""); //обнуляем вводимую строку, следовательно обнуляеться message
        }
    }

    static bool if_online(cJSON *js) {
        cJSON *online = cJSON_GetObjectItemCaseSensitive(js, "ONLINE");

        if(cJSON_IsTrue(online) == 1)
            return false;
        return true;
    }

    static void *Read(void *dat) {
        t_widget_my *widge = (t_widget_my *) dat;
        char *buff = (char *)malloc(1024);
        int len;
        cJSON *json;
        cJSON *users = NULL;
        cJSON *peoples = NULL;
        cJSON *user_id;
        cJSON *login;
        cJSON *online;

        while(1) {
            len = read(widge->sockfd, buff, 1024);
            json = cJSON_Parse(buff);
            //if (if_online(json))
                mx_message_to(widge, buff);
            // else {
            //     users = cJSON_GetObjectItemCaseSensitive(json, "users");
            //     cJSON_ArrayForEach(peoples, who_online) {
            //         login = cJSON_GetObjectItemCaseSensitive(peoples, "login");
            //         user_id = cJSON_GetObjectItemCaseSensitive(peoples, "id");
            //         online = cJSON_GetObjectItemCaseSensitive(peoples, "online");
            //         mx_create_friend(widge, login->valuestring);
            //     }
            // }
            cJSON_Delete(json);
        }
        int exit;
        pthread_exit(&exit);
        return (void*)0;
    }

    void profile(GtkWidget* widget, void *data) {
        t_widget_my *widge = (t_widget_my *)data;
        mx_profile_gtk(widge);
    }

    void mx_connection(t_widget_my *widge) {
        int portno;
        struct sockaddr_in serv_addr;
        struct hostent *server;
        pthread_t preg;
        char *str;
        char buff[1024];
        portno = widge->port;
        widge->sockfd = socket(AF_INET, SOCK_STREAM, 0);

        if (widge->sockfd < 0) {
            perror("ERROR opening socket");
            exit(1);
        }

        server = gethostbyname(widge->ip);
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }
        
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(portno);

        if (connect(widge->sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            perror("ERROR connecting");
            exit(1);
        }
        asprintf(&str, "{\"LOGIN\":\"%s\",\"PASS\":\"%s\"}\n", widge->login, widge->pass); //записываем в строку логин и пароль для Лехи
        write(widge->sockfd, str, strlen(str)); //отпраявляем логин и пароль Лехе
        free(str);


        read(widge->sockfd, buff, 1024);
        gtk_widget_hide(GTK_WIDGET(widge->wrong_login));
        if (atoi(buff) != -1) {
            mx_chat_win(widge);
            g_signal_connect (widge->profile_button, "clicked", G_CALLBACK(profile), widge);
            g_signal_connect (widge->send_button, "clicked", G_CALLBACK(send_message), widge);
            g_signal_connect (widge->command_line, "activate", G_CALLBACK(send_message), widge);
            g_signal_connect (widge->setting, "clicked", G_CALLBACK(setting_win), widge);
            pthread_create(&preg, 0, Read, widge);
        }
        else {
            gtk_widget_show(GTK_WIDGET(widge->wrong_login));
            gtk_label_set_text(widge->wrong_login, "WRONG LOGIN OR PASSWORD");
        }
    }
