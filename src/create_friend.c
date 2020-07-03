#include "../inc/uchat.h"

void p(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;

    gtk_button_set_label (GTK_BUTTON(widge->who_writing), (char *) gtk_button_get_label(GTK_BUTTON(widge->friend_button[widge->id_friend])));
}


void mx_create_friend(t_widget_my *widge, const gchar *text) {
    GtkWidget *row, *user, *fixed, *box;

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
    // gtk_container_add_with_properties (GTK_CONTAINER (box), message_to, "expand", TRUE, "fill", TRUE, NULL);

    gtk_widget_set_name(widge->friend_button[widge->id_friend], "chat_button");

    // gtk_widget_set_name(widge->friend_button, "user");
    g_signal_connect (widge->friend_button[widge->id_friend], "clicked", G_CALLBACK(p), widge);

    gtk_list_box_insert (GTK_LIST_BOX(widge->friends), row, -1);

    widge->id_friend++;

    gtk_widget_show_all (widge->friends);
}
