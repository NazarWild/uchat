#include "../inc/uchat.h"

// void mx_message_from(t_widget_my *widge, const gchar *text) {
//     GtkWidget *row, *message_from, *fixed, *box;

//     row = gtk_list_box_row_new ();
//     gtk_widget_set_size_request(row, 590, 40);
//     gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), FALSE);
//     gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

//     fixed = gtk_fixed_new();
//     gtk_container_add (GTK_CONTAINER (row), fixed);

//     box = gtk_box_new (GTK_ORIENTATION_VERTICAL, TRUE);
//     gtk_widget_set_size_request(box, 590, 35);
//     gtk_container_add (GTK_CONTAINER (fixed), box);

//     message_from = gtk_label_new (text);
//     gtk_label_set_xalign(GTK_LABEL(message_from), 0);
//     gtk_container_add_with_properties (GTK_CONTAINER (box), message_from, "expand", TRUE, "fill", TRUE, NULL);

//     gtk_list_box_insert (GTK_LIST_BOX(widge->list_box), row, -1);

//     gtk_widget_show_all (widge->list_box);
// }

void mx_message_from(t_widget_my *widge, const gchar *text) {
    GtkWidget *row, *message_to, *box, *box2, *grid, *label, *grid1;

    row = gtk_list_box_row_new ();
    gtk_widget_set_size_request(row, 590, 30);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), FALSE);
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

    label = gtk_label_new("");

    message_to = gtk_button_new_with_label(text);

    grid1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    gtk_widget_set_size_request(grid1, 590, 30);

    box2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    
    gtk_box_pack_start(GTK_BOX(box2), label, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(box), message_to, 1, 0, 0);

    gtk_container_add_with_properties (GTK_CONTAINER (grid1), box2, "expand", TRUE, NULL);
    gtk_container_add(GTK_CONTAINER (grid1), box);

    gtk_container_add (GTK_CONTAINER (row), grid1);

    gtk_widget_set_name(message_to, "message_to");

    gtk_list_box_insert (GTK_LIST_BOX(widge->list_box), row, -1);

    gtk_widget_show_all (widge->list_box);
}
