#include "../inc/uchat.h"


char *mx_change_to_valid_time(char *full_time) {
    full_time[19] = '\0';
    return &full_time[4];
}

void mx_message_to(t_widget_my *widge, const gchar *text) {
    t_message *mess_struct = malloc(sizeof(t_message));
    t_row_mess *row_mess = malloc(sizeof(t_row_mess));

    row_mess->trash = gtk_button_new();

    row_mess->row = gtk_list_box_row_new ();
    gtk_widget_set_size_request(row_mess->row, 590, 30);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row_mess->row), FALSE);
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row_mess->row), FALSE);

    row_mess->label = gtk_label_new("");

    mess_struct->message = gtk_button_new_with_label(text);

    row_mess->box_in = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    gtk_widget_set_size_request(row_mess->box_in, 590, 30);

    row_mess->box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    row_mess->box2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    row_mess->box3 = gtk_box_new (GTK_ORIENTATION_VERTICAL, TRUE);
    row_mess->box4 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);

    row_mess->nickname = mx_name_mess_to(widge->login);
    time_t lt = time(NULL);
    widge->localtime = mx_change_to_valid_time(asctime(localtime(&lt)));
    row_mess->data_box = mx_time_mess_to(widge->localtime);

    widge->trash_img = gdk_pixbuf_new_from_file("./img_chat/trash.png", NULL);
    widge->trash_img = gdk_pixbuf_scale_simple(widge->trash_img, 20, 20, GDK_INTERP_BILINEAR);
    widge->trash_icon = gtk_image_new_from_pixbuf(widge->trash_img);
    gtk_button_set_image (GTK_BUTTON(row_mess->trash), widge->trash_icon);

    gtk_box_pack_start(GTK_BOX(row_mess->box), row_mess->label, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_mess->box3), row_mess->nickname, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_mess->box4), row_mess->trash, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_mess->box4), mess_struct->message, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_mess->box3), row_mess->box4, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_mess->box3), row_mess->data_box, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_mess->box2), row_mess->box3, 1, 0, 0);

    gtk_container_add_with_properties (GTK_CONTAINER (row_mess->box_in), row_mess->box, "expand", TRUE, NULL);
    gtk_container_add(GTK_CONTAINER (row_mess->box_in), row_mess->box2);

    gtk_container_add (GTK_CONTAINER (row_mess->row), row_mess->box_in);

    gtk_widget_set_name(mess_struct->message, "message_to");
    gtk_widget_set_name(row_mess->row, "row_to");
    gtk_widget_set_name(row_mess->trash, "edit");

    gtk_widget_set_can_focus(mess_struct->message, FALSE);
    gtk_widget_set_can_focus(row_mess->row, FALSE);
    gtk_widget_set_can_focus(row_mess->trash, FALSE);
///////////////////////////////////////////////////////////////////////////////
    t_page *page;
    t_list_gtk *list = widge->page_list;
    char *data_me;
    while (list) {
        page = (t_page *)list->data;
        data_me = (char*)g_object_get_data(G_OBJECT(page->list_box), "id");
        printf("{%s} {%s}\n", widge->login_list, data_me);
        if (strcmp(widge->login_list, data_me) == 0) {
            break;
        }
        list = list->next;
    }
///////////////////////////////////////////////////////////////////////////////
    char *id_list = strdup(data_me);
    g_object_set_data(G_OBJECT(row_mess->trash), "id_list", id_list);
    g_object_set_data(G_OBJECT(mess_struct->message), "id_list", id_list);

///////////////////////////////////////////////////////////////////////////////
    gtk_list_box_insert (GTK_LIST_BOX(page->list_box), row_mess->row, -1);

    widge->index_mess_to = gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(row_mess->row));

    int i = widge->index_mess_to;
    g_object_set_data(G_OBJECT(row_mess->trash), "index_row", (gpointer)(uintptr_t)(i));
    g_object_set_data(G_OBJECT(mess_struct->message), "index_row", (gpointer)(uintptr_t)(i));

    mx_push_front_gtk(&widge->message_list, mess_struct);

    g_signal_connect(row_mess->trash, "clicked", G_CALLBACK(mx_delete_rows), widge);

    gdk_threads_add_idle ((GSourceFunc) mx_idle_showall, page->list_box);
    // gtk_widget_show_all(page->list_box);
}


