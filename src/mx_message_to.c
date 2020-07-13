#include "../inc/uchat.h"

void print(GtkWidget *widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;

    char *login = (char *) gtk_button_get_label(GTK_BUTTON(widget));
    printf("%s\n", login);
    // printf("%i\n", widge->message_id);
    // printf("%s\n", gtk_button_get_label(GTK_BUTTON(widge->message_send[widge->message_id - 1])));
}

void mx_message_to(t_widget_my *widge, const gchar *text) {
    // GtkWidget *row, *fixed, *box, *box2, *grid, *label, *grid1, *grid2, *grid3;

    // widge->message_send = realloc((GtkWidget **)widge->message_send, widge->message_id + 2);

    // widge->message_send[widge->message_id + 1] = NULL;

    // row = gtk_list_box_row_new ();
    // gtk_widget_set_size_request(row, 590, 30);
    // gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), FALSE);
    // gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

    // label = gtk_label_new("");

    // widge->message_send[widge->message_id] = gtk_button_new_with_label(text);

    // grid1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    // gtk_widget_set_size_request(grid1, 590, 30);

    // box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    // box2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);

    // gtk_box_pack_start(GTK_BOX(box), label, 1, 0, 0);
    // gtk_box_pack_start(GTK_BOX(box2), widge->message_send[widge->message_id], 1, 0, 0);

    // gtk_container_add_with_properties (GTK_CONTAINER (grid1), box, "expand", TRUE, NULL);
    // gtk_container_add(GTK_CONTAINER (grid1), box2);

    // gtk_container_add (GTK_CONTAINER (row), grid1);

    // gtk_widget_set_name(widge->message_send[widge->message_id], "message_to");
    // gtk_widget_set_name(row, "row");

    // gtk_list_box_insert (GTK_LIST_BOX(widge->list_box), row, -1);

    // g_signal_connect(widge->message_send[widge->message_id], "clicked", G_CALLBACK(print), widge);

    // widge->message_id++;

    // gtk_widget_show_all (widge->list_box);
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


