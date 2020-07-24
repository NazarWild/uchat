#include "../inc/uchat.h"

void check_chat(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;
    t_list *list = widge->login_id;

    const gchar *find_login = gtk_entry_get_text(GTK_ENTRY(widget));

    while (strcmp(find_login, list->login) != 0 && list->next != NULL) {
        list = list->next;
    }
    if (strcmp(find_login, list->login) == 0) {
        t_page *page = malloc(sizeof(t_page));
        gtk_entry_set_text(GTK_ENTRY(widget), "");
        // mx_create_chat(page, widge, list->login);
        mx_create_friend(widge, list->login, list->online, page);
    }
    else {
        gtk_entry_set_text(GTK_ENTRY(widget), "");
        gtk_entry_set_placeholder_text(GTK_ENTRY(widget), "No such user");
    }
}

void mx_pop_front(t_list **head) {
    t_list *first = *head;
    *head = (*head)->next;
    free(first->login);
    free(first->id);
    first->login = NULL;
    first->id = NULL;
}

void free_list(t_list **head) {
    while(*head)
        mx_pop_front(head);
}

t_list *mx_create_node(char *login, char *id, int online) {
    t_list *node = (t_list *) malloc(sizeof(t_list));

    node->login = strdup(login);
    node->id = strdup(id);
    node->online = online;
    node->next = NULL;  
    return node;
}

void mx_push_back(t_list **list, char *login, char *id, int online){
    if(*list == NULL) {
        *list = mx_create_node(login, id, online);
        return;
    }
    t_list *copy = *list;

    while(copy->next != NULL) {
        copy = copy->next;
    }
    copy->next = mx_create_node(login, id, online);
    copy = copy->next;
}

void mx_parse_whoonline(t_widget_my *widge, cJSON *json) {
    cJSON *user = cJSON_GetObjectItemCaseSensitive(json, "user");
    cJSON *peoples = NULL;
    cJSON *user_id;
    cJSON *login;
    cJSON *online;

    write(1, "=======USERS=======\n\n", strlen("===================\n\n"));
    cJSON_ArrayForEach(peoples, user) { 
        login = cJSON_GetObjectItemCaseSensitive(peoples, "login");
        user_id = cJSON_GetObjectItemCaseSensitive(peoples, "user_id");
        online = cJSON_GetObjectItemCaseSensitive(peoples, "online");

        write(1, "=======USER=======\n", strlen("===================\n"));
        printf("LOGIN : %s\nID = %s\nONLINE = %d\n", login->valuestring, user_id->valuestring, online->valueint);
        write(1, "==================\n", strlen("==================\n"));
        mx_push_back(&widge->login_id, login->valuestring, user_id->valuestring, online->valueint);
    }
    write(1, "=====================\n\n", strlen("=====================\n\n"));
}

void change_pos(GtkWidget *widget, void *data) {
    static gdouble uper = 0;

    if (uper != gtk_adjustment_get_upper(GTK_ADJUSTMENT(widget))) {
        gtk_adjustment_set_value(GTK_ADJUSTMENT(widget), gtk_adjustment_get_upper(GTK_ADJUSTMENT(widget)));
        uper = gtk_adjustment_get_upper(GTK_ADJUSTMENT(widget));
    }
}

void mx_papa_bot(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;
    char *login = (char *) gtk_button_get_label(GTK_BUTTON(widget));
    widge->login_list = strdup(login);
    
    gtk_button_set_label (GTK_BUTTON(widge->who_writing), login);

    int i = (int)(uintptr_t)g_object_get_data(G_OBJECT(widget), "id");
    gtk_notebook_set_current_page(GTK_NOTEBOOK(widge->notebook), i);
}

void hazker_mode(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    gtk_css_provider_load_from_path (widge->theme, "src/hacker.css", NULL);
}

void send_file(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    mx_dialog_open(widge);
}

void theme_1(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    gtk_css_provider_load_from_path (widge->theme, "src/hacker.css", NULL);
}

void theme_2(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    gtk_css_provider_load_from_path (widge->theme, "src/default.css", NULL);
}

void theme_3(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    gtk_widget_hide(widge->win_sett);
    gtk_widget_show_all(widge->main_chat);
}

bool if_online(cJSON *js) {
    cJSON *online = cJSON_GetObjectItemCaseSensitive(js, "USERS");

    if(cJSON_IsTrue(online) == 1)
        return true;
    return false;
}

bool if_chats(cJSON *js) {
    cJSON *chats = cJSON_GetObjectItemCaseSensitive(js, "if_chats");

    if(cJSON_IsTrue(chats) == 1)
        return true;
    return false;
}

bool if_mess(cJSON *js) {
    cJSON *mess = cJSON_GetObjectItemCaseSensitive(js, "IF_MESS");

    if(cJSON_IsTrue(mess) == 1)
        return true;
    return false;
}

void parse_mess(cJSON *js, t_widget_my *widge) {
    cJSON *mess = cJSON_GetObjectItemCaseSensitive(js, "MESS");
    cJSON *to = cJSON_GetObjectItemCaseSensitive(js, "TO");

    printf("ТИ - %s\n", to->valuestring);
    mx_message_from(widge, mess->valuestring);
    write(1, mess->valuestring, strlen(mess->valuestring));
}

void mx_parse_chats(cJSON *json, t_widget_my *widge) {
    cJSON *chats = cJSON_GetObjectItemCaseSensitive(json, "chats");

    if(cJSON_IsFalse(chats) != 1) {
        cJSON *id = NULL;
        cJSON *last_mess = NULL;
        cJSON *who_write = NULL;
        cJSON *arr = NULL;
        cJSON *arr_2 = NULL;
        cJSON *who_in_chat = NULL;

        write(1, "=======CHATS=======\n\n", strlen("===================\n\n"));
        cJSON_ArrayForEach(arr, chats) { 
            id = cJSON_GetObjectItemCaseSensitive(arr, "id");
            last_mess = cJSON_GetObjectItemCaseSensitive(arr, "last_mess");
            who_write = cJSON_GetObjectItemCaseSensitive(arr, "who_write");
            who_in_chat = cJSON_GetObjectItemCaseSensitive(arr, "who_in_chat");
            printf("=======CHAT ID %s=======\n", id->valuestring);
            printf("MESS : %s\nWHO_WRITE : %s\n", last_mess->valuestring,  mx_find_login_by_id(widge->login_id, who_write->valuestring));
            printf("=======WHO IN CHAT =======\n");
            cJSON_ArrayForEach(arr_2, who_in_chat) {
                printf("%s\t",arr_2->valuestring);
            }
            printf("\n");
            printf("=====================\n");
            //mx_push_back();
        }
        write(1, "=====================\n\n", strlen("=====================\n\n"));
    }
}

void *Read(void *dat) {
    t_widget_my *widge = (t_widget_my *) dat;
    char buff[2048];
    int len;
    cJSON *json;
    t_list *p = widge->login_id;

    while(1) {
        len = SSL_read(widge->ssl, buff, 2048);
        // len = read(widge->sockfd, buff, 2048);
        if (len > 0) {
            json = cJSON_Parse(buff);

        //chats
            if (if_chats(json))
                mx_parse_chats(json, widge);
        //online
            if (if_online(json)) {
                free_list(&widge->login_id);
                mx_parse_whoonline(widge, json);
            }
        printf("----------WITHOUT PARSING----------\n[%s]\n-----------------------------------\n", buff);
        //mess
            if (if_mess(json))
                parse_mess(json, widge);

            bzero(buff, 2048);
            cJSON_Delete(json);
        }
    }
    int exit;
    pthread_exit(&exit);
    return (void *)0;
}

// void *Update(void *dat) {
//     t_widget_my *widge = (t_widget_my *) dat;
//     char *str;

//     while(1) {
//         sleep(20);//-----------------------------------------------------periods of update
//         asprintf(&str, "{\"IF_MESS\": false }\n");
//         write(widge->sockfd, str, strlen(str));
//         printf("\n-----------------------------------------------I AM %s\n", widge->login);
//         free(str);
//     }
//     int exit;
//     pthread_exit(&exit);
//     return (void *)0;
// }

void profile(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;

    if (widge->on_profile == 0) {
        t_list *p = widge->login_id;

        widge->on_profile = 1;
        mx_profile_gtk(widge);
    }
}

//////////////////
gboolean show_mini_profile(GtkWidget* widget, GdkEvent  *event,void *data) {
    t_widget_my *widge = (t_widget_my *)data;
    
    //set position for mini profile
    gtk_window_get_position(GTK_WINDOW(widge->chat), &widge->window_x, &widge->window_y);
    gtk_window_move(GTK_WINDOW(widge->mini_window_profile), widge->window_x + 100, widge->window_y - 160);
    // 

    gtk_widget_show (widge->mini_window_profile);
    return false;
}

gboolean hide_mini_profile(GtkWidget* widget, GdkEvent  *event,void *data) {
    t_widget_my *widge = (t_widget_my *)data;

    //set position for mini profile
    gtk_window_get_position(GTK_WINDOW(widge->chat), &widge->window_x, &widge->window_y);
    gtk_window_move(GTK_WINDOW(widge->mini_window_profile), widge->window_x + 100, widge->window_y - 160);
    // 

    gtk_widget_hide (widge->mini_window_profile);
    return false;
}

void mx_create_bot(t_widget_my *widge) {
    t_page *page = malloc(sizeof(t_page));
    int i = 0;

    g_object_set_data(G_OBJECT(widge->papa_bot), "id", (gpointer)(uintptr_t)(i));
    mx_create_chat(page, widge, "Papa BOT");
    mx_push_front_gtk(&widge->page_list, page);
    widge->login_list = strdup("Papa BOT");
    gtk_button_set_label(GTK_BUTTON(widge->who_writing), "Papa BOT");
    gtk_notebook_set_current_page(GTK_NOTEBOOK(widge->notebook), 0);
}

void mx_connection(t_widget_my *widge) {
    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    pthread_t preg;
    char *str;
    char buff[2048];
    cJSON *json;
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
    widge->ssl = mx_ssl(widge->sockfd);
    asprintf(&str, "{\"LOGIN\":\"%s\",\"PASS\":\"%s\"}\n", widge->login, mx_hash(widge->login, widge->pass)); //записываем в строку логин и пароль для Лехи
    SSL_write(widge->ssl, str, strlen(str));
    // write(widge->sockfd, str, strlen(str)); //отпраявляем логин и пароль Лехе
    free(str);
    SSL_read(widge->ssl, buff, 2048);
    // read(widge->sockfd, buff, 2048);
    json = cJSON_Parse(buff);
    if (if_online(json))
        mx_parse_whoonline(widge, json);
    cJSON_Delete(json);
    gtk_widget_hide(GTK_WIDGET(widge->wrong_login));
    if (atoi(buff) != -1) {
        mx_chat_win(widge);
        mx_mini_profile_gtk(widge);
        mx_create_stick(widge);
        mx_create_bot(widge);//создаем окно бота
        g_signal_connect (widge->who_writing, "enter-notify-event", G_CALLBACK(show_mini_profile), widge);
        g_signal_connect (widge->who_writing, "leave-notify-event", G_CALLBACK(hide_mini_profile), widge);
        g_signal_connect (widge->profile_button, "clicked", G_CALLBACK(profile), widge);
        g_signal_connect (widge->achiev, "clicked", G_CALLBACK(hazker_mode), widge);
        g_signal_connect (widge->setting, "clicked", G_CALLBACK(mx_setting_win), widge);
        g_signal_connect (widge->file_button, "clicked", G_CALLBACK(send_file), widge);
        g_signal_connect(widge->papa_bot, "clicked", G_CALLBACK(mx_papa_bot), widge);
        g_signal_connect (widge->search_entry, "activate", G_CALLBACK(check_chat), widge);
        g_signal_connect(widge->command_line, "activate", G_CALLBACK(mx_send_message), widge);
        g_signal_connect (widge->send_button, "clicked", G_CALLBACK(mx_send_message), widge);
        g_signal_connect (widge->sticker_pack, "clicked", G_CALLBACK(mx_sticker), widge);
        pthread_create(&preg, 0, Read, widge);
        //pthread_create(&preg, 0, Update, widge);
    }
    else {
        gtk_widget_show(GTK_WIDGET(widge->wrong_login));
        gtk_label_set_text(widge->wrong_login, "WRONG LOGIN OR PASSWORD");
    }
}
