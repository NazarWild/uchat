#include "../inc/uchat.h"

void try_function(t_widget_my *widge, GtkWidget *list_box, gint index) {
    t_message *mess_struct = malloc(sizeof(t_message));
    GtkWidget *row, *box, *box2, *label, *box_in, *box3, *user_name, *data_box, *box4;
    char *to;

    row = gtk_list_box_row_new ();
    gtk_widget_set_size_request(row, 590, 30);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), FALSE);
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

    label = gtk_label_new("");

    mess_struct->message = gtk_button_new_with_label("this message was deleted");

    box_in = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    gtk_widget_set_size_request(box_in, 590, 30);

    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    box2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    box3 = gtk_box_new (GTK_ORIENTATION_VERTICAL, TRUE);
    box4 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);

    user_name = mx_name_mess_to("opoliarenk");
    data_box = mx_time_mess_to("22:12");

    gtk_box_pack_start(GTK_BOX(box), label, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(box3), user_name, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(box4), mess_struct->message, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(box3), box4, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(box3), data_box, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(box2), box3, 1, 0, 0);

    gtk_container_add_with_properties (GTK_CONTAINER (box_in), box, "expand", TRUE, NULL);
    gtk_container_add(GTK_CONTAINER (box_in), box2);

    gtk_container_add (GTK_CONTAINER (row), box_in);

    gtk_widget_set_name(mess_struct->message, "deleted");
    gtk_widget_set_name(row, "row_to");

    gtk_widget_set_can_focus(mess_struct->message, FALSE);
    gtk_widget_set_can_focus(row, FALSE);

    gtk_list_box_insert (GTK_LIST_BOX(list_box), row, index);

    mx_push_front_gtk(&widge->message_list, mess_struct);

    gdk_threads_add_idle ((GSourceFunc) mx_idle_showall, list_box);
    // gtk_widget_show_all(list_box);
}



void mx_delete_rows(GtkWidget *widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;
    t_list_gtk *list = widge->page_list;
    t_page *page;
    char *data_me;
    GtkWidget *row;
    int index = (int)(uintptr_t)g_object_get_data(G_OBJECT(widget), "index_row");

    char *id_list = (char *)g_object_get_data(G_OBJECT(widget), "id_list");

    while (list) {
        page = (t_page *)list->data;
        data_me = (char*)g_object_get_data(G_OBJECT(page->list_box), "id");
        //printf("{%s} {%s}\n", id_list, data_me);
        if (strcmp(id_list, data_me) == 0) {
            break;
        }
        list = list->next;
    }
    mx_delete_row(page->list_box, index);
    try_function(widge, page->list_box, index);
    // gtk_container_remove(GTK_CONTAINER(), GTK_WIDGET(row));
}
