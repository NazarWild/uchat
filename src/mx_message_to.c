#include "../inc/uchat.h"

void mx_message_to(t_widget_my *widge, const gchar *text) {
    GtkWidget *row, *message_to, *fixed, *box;

    row = gtk_list_box_row_new ();
    gtk_widget_set_size_request(row, 590, 40);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), FALSE);
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

    fixed = gtk_fixed_new();
    gtk_container_add (GTK_CONTAINER (row), fixed);

    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, TRUE);
    gtk_widget_set_size_request(box, 580, 35);
    gtk_container_add (GTK_CONTAINER (fixed), box);

    message_to = gtk_label_new (text);
    gtk_label_set_xalign(GTK_LABEL(message_to), 1);
    gtk_container_add_with_properties (GTK_CONTAINER (box), message_to, "expand", TRUE, "fill", TRUE, NULL);

    gtk_widget_set_name(message_to, "message_to");
    gtk_widget_set_name(box, "box");

    gtk_list_box_insert (GTK_LIST_BOX(widge->list_box), row, -1);

    gtk_widget_show_all (widge->list_box);
}


