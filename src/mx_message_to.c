#include "../inc/uchat.h"

// void mx_message_to(t_widget_my *widge, const gchar *text) {
//     GtkWidget *row, *message_to, *fixed, *box;

//     row = gtk_list_box_row_new ();
//     gtk_widget_set_size_request(row, 590, 40);
//     gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), FALSE);
//     gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

//     fixed = gtk_fixed_new();
//     gtk_container_add (GTK_CONTAINER (row), fixed);

//     box = gtk_box_new (GTK_ORIENTATION_VERTICAL, TRUE);
//     gtk_widget_set_size_request(box, 580, 35);
//     gtk_container_add (GTK_CONTAINER (fixed), box);

//     message_to = gtk_label_new (text);
//     gtk_label_set_xalign(GTK_LABEL(message_to), 1);
//     gtk_container_add_with_properties (GTK_CONTAINER (box), message_to, "expand", TRUE, "fill", TRUE, NULL);

//     gtk_widget_set_name(message_to, "message_to");
//     gtk_widget_set_name(box, "box");

//     gtk_list_box_insert (GTK_LIST_BOX(widge->list_box), row, -1);

//     gtk_widget_show_all (widge->list_box);
// }

void mx_message_to(t_widget_my *widge, const gchar *text) {
    GtkWidget *row, *message_to, *fixed, *box, *box2, *grid, *label, *grid1, *grid2, *grid3;

    row = gtk_list_box_row_new ();
    gtk_widget_set_size_request(row, 590, 30);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), FALSE);
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

    label = gtk_label_new("");

    message_to = gtk_button_new_with_label(text);

    grid1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    gtk_widget_set_size_request(grid1, 590, 30);

    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    box2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    
    gtk_box_pack_start(GTK_BOX(box), label, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(box2), message_to, 1, 0, 0);

    gtk_container_add_with_properties (GTK_CONTAINER (grid1), box, "expand", TRUE, NULL);
    gtk_container_add(GTK_CONTAINER (grid1), box2);

    gtk_container_add (GTK_CONTAINER (row), grid1);

    gtk_widget_set_name(message_to, "message_to");
    gtk_widget_set_name(row, "row");

    gtk_list_box_insert (GTK_LIST_BOX(widge->list_box), row, -1);

    gtk_widget_show_all (widge->list_box);
}


