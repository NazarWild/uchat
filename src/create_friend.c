#include "../inc/uchat.h"

void p(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;
    char *login = (char *) gtk_button_get_label(GTK_BUTTON(widget));
    
    gtk_button_set_label (GTK_BUTTON(widge->who_writing), login);
    widge->to = login;
}

void *f_realloc(void *ptr, size_t size, ssize_t from) {
    void *new_ptr= malloc(size);
    if (new_ptr && ptr)
    {
        memcpy(new_ptr, ptr, from);
        free(ptr);
    }

    return new_ptr;
}

void mx_create_friend(t_widget_my *widge, const gchar *text) {
    GtkWidget *row, *user, *fixed, *box;

    widge->friend_button = f_realloc(widge->friend_button, (widge->id_friend + 1) * sizeof(widge->message_send), widge->id_friend);

    row = gtk_list_box_row_new ();
    gtk_widget_set_size_request(row, 180, 40);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), FALSE);
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

    fixed = gtk_fixed_new();
    gtk_container_add (GTK_CONTAINER (row), fixed);

    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, TRUE);
    gtk_widget_set_size_request(box, 180, 35);
    gtk_container_add (GTK_CONTAINER (fixed), box);

    widge->friend_button[widge->id_friend] = gtk_button_new_with_label(text);
    gtk_widget_set_size_request(box, 170, 35);
    
    gtk_container_add (GTK_CONTAINER (box), widge->friend_button[widge->id_friend]);

    gtk_widget_set_name(widge->friend_button[widge->id_friend], "chat_button");

    g_signal_connect (widge->friend_button[widge->id_friend], "clicked", G_CALLBACK(p), widge);

    gtk_list_box_insert (GTK_LIST_BOX(widge->friends), row, -1);

    widge->id_friend++;

    widge->index = gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(row));

    gtk_widget_show_all (widge->friends);
}
