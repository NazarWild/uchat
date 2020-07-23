#include "../inc/uchat.h"

GtkWidget *mx_time_mess_from(char *data) {
    GtkWidget *box, *label, *date;

    label = gtk_label_new("");
    date = gtk_label_new(data);

    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);

    gtk_box_pack_start(GTK_BOX(box), date, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(box), label, 1, 0, 0);

    gtk_widget_set_name(date, "mess_date_f");

    return box;
}

