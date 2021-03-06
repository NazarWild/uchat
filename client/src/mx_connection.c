#include "../inc/uchat.h"

void check_chat(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;
    t_list *list = widge->login_id;
    const gchar *find_login = gtk_entry_get_text(GTK_ENTRY(widget));
    t_login *log = list->data;

    while (strcmp(find_login, log->login) != 0 && list) {
        log = list->data;
        list = list->next;
    }
    if (strcmp(find_login, log->login) == 0) {
        t_page *page = malloc(sizeof(t_page));

        widge->chat_id = 0;
        mx_create_friend(widge, log->login, log->online, page);
        gtk_entry_set_text(GTK_ENTRY(widget), "");
        ////////////////////////////////////////////////////////////////////////
    }
    else {
        gtk_entry_set_text(GTK_ENTRY(widget), "");
        gtk_entry_set_placeholder_text(GTK_ENTRY(widget), "No such user");
    }
}

t_list *mx_create_node(void *data) {
    t_list *head = NULL;

    head = malloc(sizeof(t_list));
    if (head == NULL)
        return 0;
    head->data = data;
    head->next = NULL;
    return head;
}

void mx_push_front(t_list **list, void *data) {
    t_list *tmp = *list;

    if (*list == 0) {
        *list = mx_create_node(data);
        return;
    }
    *list = mx_create_node(data);
    (*list)->next = tmp;
}

static void push(t_widget_my *widge, char *login, char *id, int online) {
    t_login *log = malloc(sizeof(t_login));
    log->login = strdup(login);
    log->id = strdup(id);
    log->online = online;
    log->get_messages = false;

    mx_push_front(&widge->login_id, log);
}

static void free_list(t_list **list) {
    t_list *old = 0;
    t_login *log = 0;

    for (t_list *new = *list; new != 0; new = old) {
        log = new->data;
        old = new->next;
        free(log->login);
        free(log->id);
        free(log);
        free(new);
        // mx_pop_front(&new);
    }
}

void mx_parse_whoonline(t_widget_my *widge, cJSON *json) {
    cJSON *user = cJSON_GetObjectItemCaseSensitive(json, "user");
    cJSON *peoples = NULL;
    cJSON *user_id;
    cJSON *login;
    cJSON *online;

    widge->login_id = 0;
    //write(1, "=======USERS=======\n\n", strlen("===================\n\n"));
    cJSON_ArrayForEach(peoples, user) {
        login = cJSON_GetObjectItemCaseSensitive(peoples, "login");
        user_id = cJSON_GetObjectItemCaseSensitive(peoples, "user_id");
        online = cJSON_GetObjectItemCaseSensitive(peoples, "online");

        //write(1, "=======USER=======\n", strlen("===================\n"));
        //printf("LOGIN : %s\nID = %s\nONLINE = %d\n", login->valuestring, user_id->valuestring, online->valueint);
        //write(1, "==================\n", strlen("==================\n"));
        push(widge, login->valuestring, user_id->valuestring, online->valueint);
    }
    //write(1, "=====================\n\n", strlen("=====================\n\n"));
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
    int i;

    //mx_set_mini_profile();
    widge->to = strdup("PAPA_BOT");
    widge->login_list = strdup(login);
    gtk_button_set_label (GTK_BUTTON(widge->who_writing), login);

    i = (int)(uintptr_t)g_object_get_data(G_OBJECT(widget), "id");
    gtk_notebook_set_current_page(GTK_NOTEBOOK(widge->notebook), i);
}

void hazker_mode(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    gtk_css_provider_load_from_path (widge->theme, "client/src/hacker.css", NULL);
}

void send_file(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    mx_dialog_open(widge);
}

void theme_1(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    gtk_css_provider_load_from_path (widge->theme, "client/src/hacker.css", NULL);
}

void theme_2(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    gtk_css_provider_load_from_path (widge->theme, "client/src/default.css", NULL);
}

void theme_3(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    gdk_threads_add_idle ((GSourceFunc) mx_idle_hide, widge->win_sett);
    // gtk_widget_hide(widge->win_sett);
    gdk_threads_add_idle ((GSourceFunc) mx_idle_showall, widge->main_chat);
    // gtk_widget_show_all(widge->main_chat);
}

void setting_win(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    g_signal_connect (widge->theme_1, "clicked", G_CALLBACK(theme_1), widge);
    g_signal_connect (widge->theme_2, "clicked", G_CALLBACK(theme_2), widge);
    g_signal_connect (widge->theme_3, "clicked", G_CALLBACK(theme_3), widge);
    gdk_threads_add_idle ((GSourceFunc) mx_idle_showall, widge->win_sett);
    gdk_threads_add_idle ((GSourceFunc) mx_idle_hide, widge->main_chat);
    // gtk_widget_hide(widge->main_chat);
    // gtk_widget_show_all(widge->win_sett);
}

char *mx_create_json_mess(char *message, t_widget_my *widge) {
    cJSON *send = cJSON_CreateObject();
    cJSON *IF_MESS = cJSON_CreateTrue();
    cJSON *TO = cJSON_CreateString(widge->to);
    cJSON *TYPE = cJSON_CreateString("text");
    cJSON *MESS = cJSON_CreateString(message);
    cJSON *BYTES = cJSON_CreateNumber(strlen(message));
    cJSON *CHAT_ID = cJSON_CreateString(mx_itoa(widge->cur_chat_id));
    cJSON *DATE = cJSON_CreateString(widge->localtime);;
    char *str_js = NULL;

    cJSON_AddItemToObject(send, "IF_MESS", IF_MESS);
    cJSON_AddItemToObject(send, "TO", TO);
    cJSON_AddItemToObject(send, "MESS", MESS);
    cJSON_AddItemToObject(send, "TYPE", TYPE);
    cJSON_AddItemToObject(send, "BYTES", BYTES);
    cJSON_AddItemToObject(send, "CHAT_ID", CHAT_ID);
    cJSON_AddItemToObject(send, "DATE", DATE);
    str_js = cJSON_Print(send);
    cJSON_Delete(send);
    return str_js;
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

bool last_mess(cJSON *js) {
    cJSON *mess = cJSON_GetObjectItemCaseSensitive(js, "LAST");

    if(cJSON_IsTrue(mess) == 1)
        return true;
    return false;
}

///TUT

void mx_parse_last_mess(cJSON *json, t_widget_my *widge) {
    cJSON *messages = cJSON_GetObjectItemCaseSensitive(json, "messages");
    cJSON *text = NULL;
    cJSON *user_id = NULL;
    cJSON *chats_id = NULL;
    cJSON *arr = NULL;

    // write(1, "=======ВІДНОВЛЕННЯ СМС=======\n\n", strlen("=======ВІДНОВЛЕННЯ СМС=======\n\n"));
    cJSON_ArrayForEach(arr, messages) { 
        text = cJSON_GetObjectItemCaseSensitive(arr, "text");
        user_id = cJSON_GetObjectItemCaseSensitive(arr, "user_id");
        chats_id = cJSON_GetObjectItemCaseSensitive(arr, "chats_id");
        //printf("TEXT : %s\nUSER_ID : %d\nCHATS_ID : %d\n", text->valuestring, user_id->valueint, chats_id->valueint);
        //printf("CHATS_ID : %d\n", chats_id->valueint);
        mx_find_listbox_by_chat_id(widge, chats_id->valueint, user_id->valueint, text->valuestring);
    }
    //write(1, "=====================\n\n", strlen("=====================\n\n"));
}

void mx_parse_mess(cJSON *js, t_widget_my *widge) {
    cJSON *mess = cJSON_GetObjectItemCaseSensitive(js, "MESS");
    cJSON *from = cJSON_GetObjectItemCaseSensitive(js, "FROM");
    cJSON *TYPE = cJSON_GetObjectItemCaseSensitive(js, "TYPE");
    cJSON *CHAT_ID = cJSON_GetObjectItemCaseSensitive(js, "CHAT_ID");

    widge->login_list = strdup(mx_find_login_by_id(widge->login_id, mx_itoa(from->valueint)));
    if (mx_unique_listbox_id(widge, widge->login_list)) {
        t_page *page = malloc(sizeof(t_page));

        widge->chat_id = atoi(CHAT_ID->valuestring);
        mx_create_friend(widge, widge->login_list, 1, page);
    }
    //printf("TYPE->valuestring ================ %s\n", TYPE->valuestring);
    write(1, "\a", 1);
    if (mx_strcmp(TYPE->valuestring, "text") == 0)
        mx_message_from(widge, mess->valuestring);
    if (mx_strcmp(TYPE->valuestring, "sticker") == 0 && mx_strcmp(TYPE->valuestring, "text") != 0)
        mx_sendsticker_from(mess->valuestring, widge);
    if (mx_strcmp(TYPE->valuestring, "text") != 0 && mx_strcmp(TYPE->valuestring, "sticker") != 0) 
        mx_file_receive(js, widge);
}

bool mx_user_status(t_list *login_id, char *id) {
    t_list *p = login_id;
    t_login *log = p->data;


    while(p) {
        log = p->data;
        if (mx_strcmp(id, log->id) == 0)
            return log->online;
        p = p->next;
    }
    return false;
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

        //write(1, "=======CHATS=======\n\n", strlen("===================\n\n"));
        cJSON_ArrayForEach(arr, chats) { 
            id = cJSON_GetObjectItemCaseSensitive(arr, "id");
            last_mess = cJSON_GetObjectItemCaseSensitive(arr, "last_mess");
            who_write = cJSON_GetObjectItemCaseSensitive(arr, "who_write");
            who_in_chat = cJSON_GetObjectItemCaseSensitive(arr, "who_in_chat");
            //printf("=======CHAT ID %s=======\n", id->valuestring);
            //printf("=======WHO IN CHAT =======\n");
            cJSON_ArrayForEach(arr_2, who_in_chat) {
                //printf("%s\t",arr_2->valuestring);
                widge->to_whom = atoi(arr_2->valuestring);
                //printf("to_whom  ===  %s\n", arr_2->valuestring);
            }
            // printf("\nme[%s] --- him[%s]\n", widge->login, mx_find_login_by_id(widge->login_id, mx_itoa(widge->to_whom)));
            //printf("=====================\n");
            if (mx_unique_listbox_id(widge, mx_find_login_by_id(widge->login_id, mx_itoa(widge->to_whom)))) {
                t_page *page = malloc(sizeof(t_page));

                widge->chat_id = atoi(id->valuestring);
                //printf("widge->chat_id %d\n", widge->chat_id);
                mx_create_friend(widge, mx_find_login_by_id(widge->login_id, mx_itoa(widge->to_whom)), mx_user_status(widge->login_id, mx_itoa(widge->to_whom)), page);
                mx_push_front_mess(&widge->mess_id, mx_itoa(widge->to_whom));
            }
            mx_update_chat_id(widge, mx_find_login_by_id(widge->login_id, mx_itoa(widge->to_whom)), atoi(id->valuestring));
        }
        //write(1, "=====================\n\n", strlen("=====================\n\n"));
    }
}

void *Read(void *dat) {
    t_widget_my *widge = (t_widget_my *) dat;
    char buff[4096];
    int len;
    cJSON *json;

    while(SSL_read(widge->ssl, buff, 4096) > 0) {
        json = cJSON_Parse(buff);
        //
        //printf("----------WITHOUT PARSING----------\n[%s]\n-----------------------------------\n", buff);
        // chats
        //write(1, "if_last_mess\n", strlen("if_last_mess\n"));
        if (last_mess(json))
            mx_parse_last_mess(json, widge);
        //write(1, "chats\n", strlen("chats\n"));
        if (if_chats(json))
            mx_parse_chats(json, widge);
        //online
        //write(1, "if_ONLINE\n", strlen("if_ONLINE\n"));
        if (if_online(json)) {
            free_list(&widge->login_id);
            mx_parse_whoonline(widge, json);
        }
        //mess
        //write(1, "if_mess\n", strlen("if_mess\n"));
        if (if_mess(json))
            mx_parse_mess(json, widge);
        bzero(buff, 4096);
        cJSON_Delete(json);
    }
    int exit;
    widge->exit = 666;
    pthread_exit(&exit);
    return (void *)0;
}

void *Update(void *dat) {
    t_widget_my *widge = (t_widget_my *) dat;
    char *str;
    char *str1;

    while(widge->exit != 666) {
        asprintf(&str, "{\"WHO_ONLINE\": true }\n");
        SSL_write(widge->ssl, str, strlen(str));
        free(str);
        asprintf(&str1, "{\"CHATS_SEND\": true }\n");
        SSL_write(widge->ssl, str1, strlen(str1));
        free(str1);
        sleep(1);//-----------------------------------------------------periods of update
    }
    printf("SERVER UPAL\n");
    exit(666);
    int exit;
    pthread_exit(&exit);
    return (void *)0;
}

void profile(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;
    t_login *log = 0;

    if (widge->on_profile == 0) {
        t_list *p = widge->login_id;

        log = p->data;
        widge->on_profile = 1;
        mx_profile_gtk(widge);
    }
}

//////////////////

gboolean show_mini_profile(GtkWidget* widget, GdkEvent  *event,void *data) {
    t_widget_my *widge = (t_widget_my *)data;
    GdkPixbuf *anon_pix;

    anon_pix = gdk_pixbuf_new_from_file(widge->res_png, NULL);
    anon_pix = gdk_pixbuf_scale_simple(anon_pix, 100, 100, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(widge->mini_photo), anon_pix);
    gtk_label_set_text (GTK_LABEL(widge->mini_level), "LEVEL : 0");
    gtk_label_set_text (GTK_LABEL(widge->mini_date), widge->user_profile->birth);
    gtk_label_set_text (GTK_LABEL(widge->mini_name), widge->user_profile->fullname);
    gtk_label_set_text (GTK_LABEL(widge->mini_nick), widge->user_profile->nickname);
    //set position for mini profile
    gtk_window_get_position(GTK_WINDOW(widge->chat), &widge->window_x, &widge->window_y);
    gtk_window_move(GTK_WINDOW(widge->mini_window_profile), widge->window_x + 100, widge->window_y - 160);
    //
    gtk_widget_show(widge->mini_window_profile);
    // gdk_threads_add_idle ((GSourceFunc) mx_idle_show, widge->mini_window_profile);
    return false;
}

gboolean hide_mini_profile(GtkWidget* widget, GdkEvent  *event,void *data) {
    t_widget_my *widge = (t_widget_my *)data;

    //set position for mini profile
    gtk_window_get_position(GTK_WINDOW(widge->chat), &widge->window_x, &widge->window_y);
    gtk_window_move(GTK_WINDOW(widge->mini_window_profile), widge->window_x + 100, widge->window_y - 160);
    //

    // gdk_threads_add_idle ((GSourceFunc) mx_idle_hide, widge->mini_window_profile);
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
    //int set = 1;
    cJSON *json;

    portno = widge->port;
    widge->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //setsockopt(widge->sockfd, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));


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
    inet_aton(widge->ip, &serv_addr.sin_addr);
    serv_addr.sin_port = htons(portno);


    if (connect(widge->sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
    widge->ssl = mx_ssl(widge->sockfd);
    asprintf(&str, "{\"LOGIN\":\"%s\",\"PASS\":\"%s\"}\n", widge->login, mx_hash(widge->login, widge->pass)); //записываем в строку логин и пароль для Лехи
    SSL_write(widge->ssl, str, strlen(str)); //отпраявляем логин и пароль Лехе
    //write(widge->sockfd, str, strlen(str)); //отпраявляем логин и пароль Лехе
    free(str);
    //read(widge->sockfd, buff, 2048);
    SSL_read(widge->ssl, buff, 2048);
    // gdk_threads_add_idle ((GSourceFunc) mx_idle_hide, widge->wrong_login);
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
        pthread_create(&preg, 0, Update, widge);
        pthread_create(&preg, 0, Read, widge);
    }
    else {
        // gdk_threads_add_idle ((GSourceFunc) mx_idle_show, widge->wrong_login);
        gtk_widget_show(GTK_WIDGET(widge->wrong_login));
        gtk_label_set_text(widge->wrong_login, "WRONG LOGIN OR PASSWORD");
    }
}
