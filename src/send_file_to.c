#include "../inc/uchat.h"

void print_1(GtkWidget *widget, void *data) {
    // t_widget_my *widge = (t_widget_my *)data;
    GtkWidget *button = (GtkWidget *)data;

    char *login = (char *) gtk_button_get_label(GTK_BUTTON(button));

    printf("%s\n", login);
}

void mx_send_file_to(t_widget_my *widge, const gchar *text) {
    // GtkWidget *row, *box, *box2, *installbutt, *label, *box_in, *box3, *user_name, *data_box, *box4, *trash;

    // widge->message_send = mx_realloc(widge->message_send, (widge->message_id + 1) * sizeof(widge->message_send), widge->message_id);

    // installbutt = gtk_button_new();
    // trash = gtk_button_new();

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
    // box4 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);

    // user_name = mx_name_mess_to("opoliarenk");
    // data_box = mx_time_mess_to("22:12");

    // widge->installbutt_img = gdk_pixbuf_new_from_file("./img_chat/install.png", NULL);
    // widge->installbutt_img = gdk_pixbuf_scale_simple(widge->installbutt_img, 20, 20, GDK_INTERP_BILINEAR);
    // widge->installbutt_icon = gtk_image_new_from_pixbuf(widge->installbutt_img);
    // gtk_button_set_image (GTK_BUTTON(installbutt), widge->installbutt_icon);

    // widge->trash_img = gdk_pixbuf_new_from_file("./img_chat/trash.png", NULL);
    // widge->trash_img = gdk_pixbuf_scale_simple(widge->trash_img, 20, 20, GDK_INTERP_BILINEAR);
    // widge->trash_icon = gtk_image_new_from_pixbuf(widge->trash_img);
    // gtk_button_set_image (GTK_BUTTON(trash), widge->trash_icon);
    
    // gtk_box_pack_start(GTK_BOX(box), label, 1, 0, 0);
    // gtk_box_pack_start(GTK_BOX(box3), user_name, 0, 0, 0);
    // gtk_box_pack_start(GTK_BOX(box4), trash, 0, 0, 0);
    // gtk_box_pack_start(GTK_BOX(box4), installbutt, 0, 0, 0);
    // gtk_box_pack_start(GTK_BOX(box4), widge->message_send[widge->message_id], 1, 0, 0);
    // gtk_box_pack_start(GTK_BOX(box3), box4, 1, 0, 0);
    // gtk_box_pack_start(GTK_BOX(box3), data_box, 0, 0, 0);
    // gtk_box_pack_start(GTK_BOX(box2), box3, 1, 0, 0);

    // gtk_container_add_with_properties (GTK_CONTAINER (box_in), box, "expand", TRUE, NULL);
    // gtk_container_add(GTK_CONTAINER (box_in), box2);

    // gtk_container_add (GTK_CONTAINER (row), box_in);

    // gtk_widget_set_name(widge->message_send[widge->message_id], "message_to");
    // gtk_widget_set_name(row, "row_to");
    // gtk_widget_set_name(installbutt, "install_button");
    // gtk_widget_set_name(trash, "edit");

    // gtk_widget_set_can_focus(widge->message_send[widge->message_id], FALSE);
    // gtk_widget_set_can_focus(row, FALSE);
    // gtk_widget_set_can_focus(installbutt, FALSE);
    // gtk_widget_set_can_focus(trash, FALSE);


    // gtk_list_box_insert (GTK_LIST_BOX(widge->list_box), row, -1);

    // // g_signal_connect(widge->message_send[widge->message_id], "clicked", G_CALLBACK(print), widge);
    // g_signal_connect(installbutt, "clicked", G_CALLBACK(print_1), widge->message_send[widge->message_id]);

    // widge->message_id++;

    // widge->index_mess_to = gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(row));

    // gtk_widget_show_all (widge->list_box);
}


