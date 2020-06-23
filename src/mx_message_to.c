#include "../inc/uchat.h"

// static GtkWidget *create_row (const gchar *text) {
//     GtkWidget *row, *box, *label;

//     row = gtk_list_box_row_new ();

//     box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 50);
//     gtk_container_add (GTK_CONTAINER (row), box);

//     label = gtk_label_new (text);
//     gtk_container_add_with_properties (GTK_CONTAINER (box), label, "expand", TRUE, NULL);

//     return row;
// }

void mx_message_to(t_widget_my *widge, const gchar *text) {
    GtkWidget *row, *message_to;

    // row = create_row(text);
    row = gtk_list_box_row_new ();
    gtk_widget_set_name(row, "row");
    message_to = gtk_label_new (text);
    gtk_widget_set_name(message_to, "message_to");
    gtk_widget_set_size_request(row, 0, 30);
    gtk_widget_set_size_request(message_to, 0, 30);
    gtk_container_add(GTK_CONTAINER (row), message_to);
    gtk_list_box_insert (GTK_LIST_BOX(widge->list_box), row, -1);

    gtk_widget_show_all (widge->list_box);
    // gtk_widget_show_all (widge->sw);
}


