#include "../inc/uchat.h"

void mx_message_from(t_widget_my *widge, const gchar *text) {
    GtkWidget *row, *message_from, *fixed, *box;

    row = gtk_list_box_row_new ();
    gtk_widget_set_size_request(row, 590, 40);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), FALSE);
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

    fixed = gtk_fixed_new();
    gtk_container_add (GTK_CONTAINER (row), fixed);

    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, TRUE);
    gtk_widget_set_size_request(box, 590, 35);
    gtk_container_add (GTK_CONTAINER (fixed), box);

    message_from = gtk_label_new (text);
    gtk_label_set_xalign(GTK_LABEL(message_from), 0);
    gtk_container_add_with_properties (GTK_CONTAINER (box), message_from, "expand", TRUE, "fill", TRUE, NULL);

    gtk_list_box_insert (GTK_LIST_BOX(widge->list_box), row, -1);

    gtk_widget_show_all (widge->list_box);
}
