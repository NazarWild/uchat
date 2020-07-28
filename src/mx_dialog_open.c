#include "../inc/uchat.h" 

char *mx_parsing_filename(char *filename, t_widget_my *widge) {
    int i = strlen(filename) - 1;

    for (; filename[i] != '.'; i--) {}
    widge->int_of_dot = i;
    for (; filename[i] != '/'; i--) {}
    widge->int_of_slesh = i;
    return &filename[widge->int_of_dot];
}

void sending_file(t_widget_my *widge) {
    if(widge->filename) {
        int stream = open(widge->filename, O_RDONLY);
        char str[mx_len_of_file(widge->filename)];

        widge->bytes = mx_len_of_file(widge->filename);
        read(stream, str, widge->bytes);
        write(widge->sockfd, str, widge->bytes);
        close(stream);
    }
    else
        write(2, "error in sending file\n", 23);
}

static cJSON *create_json(t_widget_my *widge) {
    cJSON *send = cJSON_CreateObject();
    cJSON *IF_MESS = cJSON_CreateTrue();
    cJSON *TO = cJSON_CreateString(widge->to);
    cJSON *TYPE = cJSON_CreateString(mx_parsing_filename(widge->filename, widge));
    cJSON *MESS = cJSON_CreateString(&widge->filename[widge->int_of_slesh + 1]);
    cJSON *BYTES = cJSON_CreateNumber(widge->bytes);
    //cJSON *CHAT_ID = cJSON_CreateString(mx_itoa(widge->cur_chat_id));
    cJSON *CHAT_ID = cJSON_CreateString("2");
    cJSON *DATE = cJSON_CreateString(widge->localtime);;
    char *file_without_dot = strdup(widge->filename);

    cJSON_AddItemToObject(send, "IF_MESS", IF_MESS);
    cJSON_AddItemToObject(send, "TO", TO);
    cJSON_AddItemToObject(send, "MESS", MESS);
    cJSON_AddItemToObject(send, "TYPE", TYPE);
    cJSON_AddItemToObject(send, "BYTES", BYTES);
    cJSON_AddItemToObject(send, "CHAT_ID", CHAT_ID);
    cJSON_AddItemToObject(send, "DATE", DATE);
    //free(&file_without_dot);
    return send;
}

bool mx_if_photo(char *filename, t_widget_my *widge) {
    char *type = mx_parsing_filename(filename, widge);

    if (strcmp(type, ".png") == 0
        || strcmp(type, ".jpg") == 0
        || strcmp(type, ".jpeg") == 0
        || strcmp(type, ".gif") == 0)
        return true;
    return false;
}

void mx_dialog_open(t_widget_my *widge) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    cJSON *file_js;
    char *str;
    int res;
    char *str_js;

    dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(widge->chat), action, ("_Cancel"), 
                                          GTK_RESPONSE_CANCEL, ("_Send"), GTK_RESPONSE_ACCEPT, NULL);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        widge->filename = gtk_file_chooser_get_filename (chooser);
        widge->bytes = mx_len_of_file(widge->filename);
        printf("bytes = %d filename = %s\n", widge->bytes, widge->filename);

        if (mx_if_photo(widge->filename, widge))
            mx_sendphoto_to(widge->filename, widge);
        else
            mx_send_file_to(widge, widge->filename);
        file_js = create_json(widge);
        str_js = cJSON_Print(file_js);
        SSL_write(widge->ssl, str_js, strlen(str_js));
        sending_file(widge);
        g_free (widge->filename);
    }
    gdk_threads_add_idle ((GSourceFunc) mx_idle_destroy, dialog);
    // gtk_widget_destroy (dialog);
}
