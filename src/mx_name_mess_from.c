#include "../inc/uchat.h"

GtkWidget *mx_name_mess_from(char *user) {
    GtkWidget *box, *label, *username;

    label = gtk_label_new("");
    username = gtk_label_new(user);

    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);

    gtk_box_pack_start(GTK_BOX(box), username, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(box), label, 1, 0, 0);

    gtk_widget_set_name(username, "username_name_f");

    return box;
}
