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

static char *parsing_filename(t_widget_my *widge, char *filename) {
    int i = strlen(filename) - 1;

    for (; filename[i] != '.'; i--) {}
    return &filename[i + 1];
}

static char *mx_file_to_str(const char *file, t_widget_my *widge) {
    if(!file)
        return NULL;
    int stream = open(file, O_RDONLY);
    char c;
    char *str = NULL;
    if(stream <= 0) {
        return NULL;
    }
    while(read(stream, &c, 1)) {
        widge->bytes++;
    }
    close(stream);
    stream = open(file, O_RDONLY);
    str = mx_strnew(widge->bytes);
    read(stream, str, widge->bytes);
    close(stream);
    return str;
}

void mx_dialog_open(t_widget_my *widge) {
    GtkWidget *dialog;
    char *str;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    int res;

    dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(widge->chat), action, ("_Cancel"), 
                                          GTK_RESPONSE_CANCEL, ("_Send"), GTK_RESPONSE_ACCEPT, NULL);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;

        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);
        printf("filename = %s\n", filename);
        widge->filename = filename;
        char *file = mx_file_to_str(filename, widge);
        asprintf(&str, "{\"FROM\" : \"%s\",\"TO\":\"%s\",\"MESS\":\"%s\",\"TYPE\":\"%s\",\"BYTES\":%d}\n", widge->login, widge->to, file, parsing_filename(widge, filename), widge->bytes);
        write(widge->sockfd, str, widge->bytes + 50); //отпрвляем Лехе данные
        mx_send_file_to(widge, filename);
        //gtk_entry_set_text(GTK_ENTRY(widge->command_line), filename);
        g_free (filename);
    }
    gtk_widget_destroy (dialog);
}