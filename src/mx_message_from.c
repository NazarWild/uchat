#include "../inc/uchat.h"

void print_1(GtkWidget *widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;

    char *login = (char *) gtk_button_get_label(GTK_BUTTON(widget));

    printf("from = %s\n", login);
}

void *from_realloc(void *ptr, size_t size, ssize_t from) {
    void *new_ptr= malloc(size);
    if (new_ptr && ptr)
    {
        memcpy(new_ptr, ptr, from);
        free(ptr);
    }

    return new_ptr;
}

void mx_message_from(t_widget_my *widge, const gchar *text) {
    GtkWidget *row, *message_to, *box, *box2, *grid, *label, *grid1;

    widge->message_send = from_realloc(widge->message_send, (widge->message_id + 1) * sizeof(widge->message_send), widge->message_id);

    row = gtk_list_box_row_new ();
    gtk_widget_set_size_request(row, 590, 30);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), FALSE);
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

    label = gtk_label_new("");

    widge->message_send[widge->message_id] = gtk_button_new_with_label(text);

    grid1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    gtk_widget_set_size_request(grid1, 590, 30);

    box2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    
    gtk_box_pack_start(GTK_BOX(box2), label, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(box), widge->message_send[widge->message_id], 1, 0, 0);

    gtk_container_add_with_properties (GTK_CONTAINER (grid1), box2, "expand", TRUE, NULL);
    gtk_container_add(GTK_CONTAINER (grid1), box);

    gtk_container_add (GTK_CONTAINER (row), grid1);

    gtk_widget_set_name(widge->message_send[widge->message_id], "message_to");

    gtk_list_box_insert (GTK_LIST_BOX(widge->list_box), row, -1);

    g_signal_connect(widge->message_send[widge->message_id], "clicked", G_CALLBACK(print_1), widge);

    widge->message_id++;

    widge->index_mess_to = gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(row));

    gtk_widget_show_all (widge->list_box);
}
