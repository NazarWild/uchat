#include "../inc/uchat.h"

void mx_photo_set(t_widget_my *widge) {
    GtkWidget *dialog;
    char *str;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    int res;

    dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(widge->chat), action, ("_Cancel"), 
                                          GTK_RESPONSE_CANCEL, ("_Set photo"), GTK_RESPONSE_ACCEPT, NULL);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;

        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);
        printf("filename = %s\n", filename);
        GtkWidget *photo = gtk_image_new_from_file(filename);

        widge->res_png = "img_chat/res/girl3.png";
        gtk_button_set_image(GTK_BUTTON(widge->profile_photo_button), photo);
        g_free (filename);
    }
    gtk_widget_destroy (dialog);
}
