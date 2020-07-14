#include "../inc/uchat.h"

void print(GtkWidget *widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;

    char *login = (char *) gtk_button_get_label(GTK_BUTTON(widget));

    printf("11111 = %s\n", login);
}

void *x_realloc(void *ptr, size_t size, ssize_t from) {
    void *new_ptr= malloc(size);
    if (new_ptr && ptr)
    {
        memcpy(new_ptr, ptr, from);
        free(ptr);
    }

    return new_ptr;
}

GtkWidget *mx_user_name_mess(char *user) {
    GtkWidget *box, *label, *username;

    label = gtk_label_new("");
    username = gtk_label_new(user);

    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);

    gtk_box_pack_start(GTK_BOX(box), label, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(box), username, 0, 0, 0);

    gtk_widget_set_name(username, "username_mess");

    return box;
}

GtkWidget *mx_data_mess(char *data) {
    GtkWidget *box, *label, *date;

    label = gtk_label_new("");
    date = gtk_label_new(data);

    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);

    gtk_box_pack_start(GTK_BOX(box), date, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(box), label, 1, 0, 0);

    gtk_widget_set_name(date, "mess_date");

    return box;
}

void mx_message_to(t_widget_my *widge, const gchar *text) {
    GtkWidget *row, *box, *box2, *grid, *label, *box_in, *box3, *user_name, *data_box;

    widge->message_send = x_realloc(widge->message_send, (widge->message_id + 1) * sizeof(widge->message_send), widge->message_id);

    row = gtk_list_box_row_new ();
    gtk_widget_set_size_request(row, 590, 30);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), FALSE);
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

    label = gtk_label_new("");

    widge->message_send[widge->message_id] = gtk_button_new_with_label(text);

    box_in = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    gtk_widget_set_size_request(box_in, 590, 30);

    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    box2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    box3 = gtk_box_new (GTK_ORIENTATION_VERTICAL, TRUE);

    user_name = mx_user_name_mess("user_name");
    data_box = mx_data_mess("2020.19220");

    gtk_box_pack_start(GTK_BOX(box), label, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(box3), user_name, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(box3), widge->message_send[widge->message_id], 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(box3), data_box, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(box2), box3, 1, 0, 0);

    gtk_container_add_with_properties (GTK_CONTAINER (box_in), box, "expand", TRUE, NULL);
    gtk_container_add(GTK_CONTAINER (box_in), box2);

    gtk_container_add (GTK_CONTAINER (row), box_in);

    gtk_widget_set_name(widge->message_send[widge->message_id], "message_to");
    gtk_widget_set_name(row, "row");

    gtk_widget_set_can_focus(widge->message_send[widge->message_id], FALSE);
    gtk_widget_set_can_focus(row, FALSE);


    gtk_list_box_insert (GTK_LIST_BOX(widge->list_box), row, -1);

    g_signal_connect(widge->message_send[widge->message_id], "clicked", G_CALLBACK(print), widge);

    widge->message_id++;

    widge->index_mess_to = gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(row));

    gtk_widget_show_all (widge->list_box);
}


