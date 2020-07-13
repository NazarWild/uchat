#include "../inc/uchat.h" 

char *mx_strnew(const int size) {
    char *str = NULL;

    if(size < 0) {
        return NULL;
    }
    else {
        str = (char *) malloc(size + 1);
        for(int i = 0; i < size; i++) {
            str[i] = '\0';
        }
        str[size] = '\0';
    }
    return str;
}

static char *parsing_filename(char *filename, t_widget_my *widge) {
    int i = strlen(filename) - 1;

    for (; filename[i] != '.'; i--) {}
    widge->int_of_dot = i;
    return &filename[widge->int_of_dot + 1];
}

int mx_len_of_file(char *file) {
    struct stat lt;
    int file_size = 0;

    stat(file, &lt);
    file_size = lt.st_size;
    return file_size;
}

void sending_file(t_widget_my *widge) {
    if(widge->filename) {
        int stream = open(widge->filename, O_RDONLY);
        char str[mx_len_of_file(widge->filename)];

        widge->bytes = mx_len_of_file(widge->filename);
        stream = open(widge->filename, O_RDONLY);
        read(stream, str, widge->bytes);
        write(widge->sockfd, str, widge->bytes);
        close(stream);
    }
    else {
        write(2, "error in sending file\n", 23);
    }
}

static cJSON *create_json(t_widget_my *widge) {
    cJSON *send = cJSON_CreateObject();
    cJSON *TO = cJSON_CreateString(widge->to);
    cJSON *MESS = cJSON_CreateString("/Users/ndykyy/Desktop/");//okolevatov
    cJSON *TYPE = cJSON_CreateString(parsing_filename(widge->filename, widge));
    cJSON *BYTES = cJSON_CreateNumber(widge->bytes);
    char *file_without_dot = strdup(widge->filename);

    cJSON_AddItemToObject(send, "TO", TO);
    cJSON_AddItemToObject(send, "MESS", MESS);
    cJSON_AddItemToObject(send, "TYPE", TYPE);
    cJSON_AddItemToObject(send, "BYTES", BYTES);
    //free(&file_without_dot);
    return send;
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

        //write(1, file, widge->bytes);
        file_js = create_json(widge);
        str_js = cJSON_Print(file_js);
        write(widge->sockfd, str_js, strlen(str_js));
        sending_file(widge);
        mx_send_file_to(widge, widge->filename);
        g_free (widge->filename);
    }
    gtk_widget_destroy (dialog);
}
