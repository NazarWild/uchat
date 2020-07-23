#include "../inc/uchat.h"


void mx_message_to(t_widget_my *widge, const gchar *text) {
    t_message *mess_struct = malloc(sizeof(t_message));
    GtkWidget *row, *box, *box2, *label, *box_in, *box3, *user_name, *data_box, *box4, *trash;
    char *to;

    trash = gtk_button_new();

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

    user_name = mx_name_mess_to("opoliarenk");
    data_box = mx_time_mess_to("22:12");

    widge->trash_img = gdk_pixbuf_new_from_file("./img_chat/trash.png", NULL);
    widge->trash_img = gdk_pixbuf_scale_simple(widge->trash_img, 20, 20, GDK_INTERP_BILINEAR);
    widge->trash_icon = gtk_image_new_from_pixbuf(widge->trash_img);
    gtk_button_set_image (GTK_BUTTON(trash), widge->trash_icon);

    gtk_box_pack_start(GTK_BOX(box), label, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(box3), user_name, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(box4), trash, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(box4), mess_struct->message, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(box3), box4, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(box3), data_box, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(box2), box3, 1, 0, 0);

    gtk_container_add_with_properties (GTK_CONTAINER (box_in), box, "expand", TRUE, NULL);
    gtk_container_add(GTK_CONTAINER (box_in), box2);

    gtk_container_add (GTK_CONTAINER (row), box_in);

    gtk_widget_set_name(mess_struct->message, "message_to");
    gtk_widget_set_name(row, "row_to");
    gtk_widget_set_name(trash, "edit");

    gtk_widget_set_can_focus(mess_struct->message, FALSE);
    gtk_widget_set_can_focus(row, FALSE);
    gtk_widget_set_can_focus(trash, FALSE);
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
    char *id_list = strdup(data_me);
    g_object_set_data(G_OBJECT(trash), "id_list", id_list);
    g_object_set_data(G_OBJECT(mess_struct->message), "id_list", id_list);

///////////////////////////////////////////////////////////////////////////////
    gtk_list_box_insert (GTK_LIST_BOX(page->list_box), row, -1);

    widge->index_mess_to = gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(row));

    int i = widge->index_mess_to;
    g_object_set_data(G_OBJECT(trash), "index_row", (gpointer)(uintptr_t)(i));
    g_object_set_data(G_OBJECT(mess_struct->message), "index_row", (gpointer)(uintptr_t)(i));

    mx_push_front_gtk(&widge->message_list, mess_struct);

    g_signal_connect(trash, "clicked", G_CALLBACK(mx_delete_rows), widge);

    gtk_widget_show_all(page->list_box);
}


