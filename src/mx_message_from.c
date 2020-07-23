#include "../inc/uchat.h"

void mx_message_from(t_widget_my *widge, const gchar *text) {
    t_message *mess_struct = malloc(sizeof(t_message));
    GtkWidget *row, *box, *box2, *label, *box_in, *box3, *user_name, *data_box, *box4;
    char *to;
    int i = 0;

    // widge->message_send = mx_realloc(widge->message_send, (widge->message_id + 1) * sizeof(widge->message_send), widge->message_id);

    row = gtk_list_box_row_new ();
    gtk_widget_set_size_request(row, 590, 30);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), FALSE);
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

    label = gtk_label_new("");

    mess_struct->message = gtk_button_new_with_label(text);

    box_in = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    gtk_widget_set_size_request(box_in, 590, 30);

    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    box2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    box3 = gtk_box_new (GTK_ORIENTATION_VERTICAL, TRUE);
    box4 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);

    user_name = mx_name_mess_from("opoliarenk");
    data_box = mx_time_mess_from("22:12");

    // gtk_box_pack_start(GTK_BOX(box), label, 1, 0, 0);
    // gtk_box_pack_start(GTK_BOX(box3), user_name, 0, 0, 0);
    // gtk_box_pack_start(GTK_BOX(box4), mess_struct->message, 1, 0, 0);
    // gtk_box_pack_start(GTK_BOX(box3), box4, 1, 0, 0);
    // gtk_box_pack_start(GTK_BOX(box3), data_box, 0, 0, 0);
    // gtk_box_pack_start(GTK_BOX(box2), box3, 1, 0, 0);


    gtk_box_pack_start(GTK_BOX(box3), user_name, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(box3), mess_struct->message, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(box3), data_box, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(box2), box3, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(box), label, 1, 0, 0);

    gtk_container_add(GTK_CONTAINER (box_in), box2);
    gtk_container_add_with_properties (GTK_CONTAINER (box_in), box, "expand", TRUE, NULL);

    // gtk_container_add_with_properties (GTK_CONTAINER (box_in), box, "expand", TRUE, NULL);
    // gtk_container_add(GTK_CONTAINER (box_in), box2);

    gtk_container_add (GTK_CONTAINER (row), box_in);

    gtk_widget_set_name(mess_struct->message, "message_from");
    gtk_widget_set_name(row, "row_from");

    gtk_widget_set_can_focus(mess_struct->message, FALSE);
    gtk_widget_set_can_focus(row, FALSE);
///////////////////////////////////////////////////////////////////////////////
    t_page *page;
    t_list_gtk *list = widge->page_list;
    char *data_me;
    while (list->next != NULL) {
        page = (t_page *)list->data;
        data_me = (char*)g_object_get_data(G_OBJECT(page->list_box), "id");
        printf("{%s} {%s}\n", widge->login_list, data_me);
        if (strcmp(widge->login_list, data_me) == 0) {
            break;
        }
        list = list->next;
    }
///////////////////////////////////////////////////////////////////////////////
    gtk_list_box_insert (GTK_LIST_BOX(page->list_box), row, -1);

    mx_push_front_gtk(&widge->message_list, mess_struct);

    widge->index_mess_to = gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(row));

    printf("here\n");
    gtk_widget_show_all (page->list_box);
}








// void mx_message_from(t_widget_my *widge, const gchar *text) {
    // GtkWidget *row, *box, *box2, *grid, *label, *box_in, *box3, *user_name, *data_box;

    // widge->message_send = mx_realloc(widge->message_send, (widge->message_id + 1) * sizeof(widge->message_send), widge->message_id);

    // row = gtk_list_box_row_new ();
    // gtk_widget_set_size_request(row, 590, 30);
    // gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), FALSE);
    // gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

    // label = gtk_label_new("");

    // widge->message_send[widge->message_id] = gtk_button_new_with_label(text);

    // box_in = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    // gtk_widget_set_size_request(box_in, 590, 30);

    // box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    // box2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    // box3 = gtk_box_new (GTK_ORIENTATION_VERTICAL, TRUE);

    // user_name = mx_name_mess_from("okolevatov");
    // data_box = mx_time_mess_from("22:53");

    // gtk_box_pack_start(GTK_BOX(box3), user_name, 0, 0, 0);
    // gtk_box_pack_start(GTK_BOX(box3), widge->message_send[widge->message_id], 1, 0, 0);
    // gtk_box_pack_start(GTK_BOX(box3), data_box, 0, 0, 0);
    // gtk_box_pack_start(GTK_BOX(box2), box3, 1, 0, 0);
    // gtk_box_pack_start(GTK_BOX(box), label, 1, 0, 0);

    // gtk_container_add(GTK_CONTAINER (box_in), box2);
    // gtk_container_add_with_properties (GTK_CONTAINER (box_in), box, "expand", TRUE, NULL);
// }


