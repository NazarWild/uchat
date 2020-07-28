#include "../inc/uchat.h"

void mx_send_file_from(t_widget_my *widge, const gchar *text) {
    t_message *mess_struct = malloc(sizeof(t_message));
    t_row_mess *row_mess = malloc(sizeof(t_row_mess));

    row_mess->installbutt = gtk_button_new();

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

    row_mess->nickname = mx_name_mess_from("opoliarenk");
    row_mess->data_box = mx_time_mess_from("22:12");

    widge->installbutt_img = gdk_pixbuf_new_from_file("./img_chat/install.png", NULL);
    widge->installbutt_img = gdk_pixbuf_scale_simple(widge->installbutt_img, 20, 20, GDK_INTERP_BILINEAR);
    widge->installbutt_icon = gtk_image_new_from_pixbuf(widge->installbutt_img);
    gtk_button_set_image (GTK_BUTTON(row_mess->installbutt), widge->installbutt_icon);

    gtk_box_pack_start(GTK_BOX(row_mess->box), row_mess->label, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_mess->box3), row_mess->nickname, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_mess->box4), row_mess->installbutt, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_mess->box4), mess_struct->message, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_mess->box3), row_mess->box4, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_mess->box3), row_mess->data_box, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_mess->box2), row_mess->box3, 1, 0, 0);

    gtk_container_add_with_properties (GTK_CONTAINER (row_mess->box_in), row_mess->box, "expand", TRUE, NULL);
    gtk_container_add(GTK_CONTAINER (row_mess->box_in), row_mess->box2);

    gtk_container_add (GTK_CONTAINER (row_mess->row), row_mess->box_in);

    gtk_widget_set_name(mess_struct->message, "message_from");
    gtk_widget_set_name(row_mess->row, "row_from");
    gtk_widget_set_name(row_mess->installbutt, "edit");

    gtk_widget_set_can_focus(mess_struct->message, FALSE);
    gtk_widget_set_can_focus(row_mess->row, FALSE);
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

    gtk_list_box_insert (GTK_LIST_BOX(page->list_box), row_mess->row, -1);

    mx_push_front_gtk(&widge->message_list, mess_struct);

    gdk_threads_add_idle ((GSourceFunc) mx_idle_showall, page->list_box);
    // gtk_widget_show_all (page->list_box);
}


