#include "../inc/uchat.h"

void mx_message_from(t_widget_my *widge, const gchar *text) {
    GtkWidget *row, *message_from;

    row = gtk_list_box_row_new ();
    gtk_widget_set_name(row, "row");
    message_from = gtk_label_new (text);
    gtk_widget_set_name(message_from, "message_from");
    gtk_widget_set_size_request(row, 0, 30);
    gtk_widget_set_size_request(message_from, 0, 30);
    gtk_container_add(GTK_CONTAINER (row), message_from);
    gtk_list_box_insert (GTK_LIST_BOX(widge->list_box), row, -1);

    gtk_widget_show_all (widge->list_box);
    // gtk_widget_show_all (widge->sw);
}
