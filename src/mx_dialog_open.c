#include "../inc/uchat.h"

static char *parsing_filename(t_widget_my *widge, char *filename) {
    int i = strlen(filename) - 1;

    for (; filename[i] != '.'; i--) {}
    return &filename[i + 1];
}

static void type_of_file(t_widget_my *widge, char *file) {
    char *type = parsing_filename(widge, file);
    
    if (strcmp(type, "png") == 0
        ||strcmp(type, "jpg") == 0
        ||strcmp(type, "jpeg") == 0)
        printf("file = photo\n");
    if (strcmp(type, "mp4") == 0
        ||strcmp(type, "avi") == 0
        ||strcmp(type, "mp4") == 0)
        printf("file = video/audio\n");
    if (strcmp(type, "c") == 0)
        printf("file = code in c\n");
}

void mx_dialog_open(t_widget_my *widge) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    int res;

    dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(widge->window), action, ("_Cancel"), 
                                          GTK_RESPONSE_CANCEL, ("_Open"), GTK_RESPONSE_ACCEPT, NULL);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;

        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);
        printf("filename = %s\n", filename);
        widge->filename = filename;
        type_of_file(widge, filename);
        //gtk_entry_set_text(GTK_ENTRY(widge->command_line), filename);
        g_free (filename);
    }
    gtk_widget_destroy (dialog);
}