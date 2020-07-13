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

        GdkPixbuf *photo_prof;
        GtkWidget *photo;

        photo_prof = gdk_pixbuf_new_from_file(filename, NULL);
        photo_prof = gdk_pixbuf_scale_simple(photo_prof, 200, 200, GDK_INTERP_BILINEAR);
        photo = gtk_image_new_from_pixbuf(photo_prof);
        gtk_button_set_image (GTK_BUTTON(widge->profile_photo_button), photo);

        widge->res_png = filename;
        g_free (filename);
    }
    gtk_widget_destroy (dialog);
}
