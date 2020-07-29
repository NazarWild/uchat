#include "../inc/uchat.h"

static GtkWidget *create_s_from(t_widget_my *widge, char *name_file) {
    GdkPixbuf *sticker_img;
    GtkWidget *sticker_icon;
    
    GtkWidget *b1 = gtk_button_new();
    sticker_img = gdk_pixbuf_new_from_file(name_file, NULL);
    sticker_img = gdk_pixbuf_scale_simple(sticker_img, 150, 150, GDK_INTERP_BILINEAR);
    sticker_icon = gtk_image_new_from_pixbuf(sticker_img);
    gtk_button_set_image (GTK_BUTTON(b1), sticker_icon);
    gtk_widget_set_name(b1, "sticker");
    gtk_widget_set_can_focus(b1, FALSE);
    return b1;
}

void mx_sendsticker_from(char *file_name, t_widget_my *widge) {
    t_message *mess_struct = malloc(sizeof(t_message));
    t_row_mess *row_mess = malloc(sizeof(t_row_mess));

    row_mess->row = gtk_list_box_row_new ();
    gtk_widget_set_size_request(row_mess->row, 590, 30);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row_mess->row), FALSE);
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row_mess->row), FALSE);

    row_mess->label = gtk_label_new("");

    mess_struct->message = create_s_from(widge, file_name);

    row_mess->box_in = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    gtk_widget_set_size_request(row_mess->box_in, 590, 30);

    row_mess->box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    row_mess->box2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    row_mess->box3 = gtk_box_new (GTK_ORIENTATION_VERTICAL, TRUE);
    row_mess->box4 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);

    row_mess->nickname = mx_name_mess_from(widge->login_list);
    row_mess->data_box = mx_time_mess_from("today");
    gtk_box_pack_start(GTK_BOX(row_mess->box3), row_mess->nickname, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_mess->box4), mess_struct->message, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_mess->box3), row_mess->box4, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_mess->box3), row_mess->data_box, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_mess->box2), row_mess->box3, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_mess->box), row_mess->label, 1, 0, 0);

    gtk_container_add(GTK_CONTAINER (row_mess->box_in), row_mess->box2);
    gtk_container_add_with_properties (GTK_CONTAINER (row_mess->box_in), row_mess->box, "expand", TRUE, NULL);
    gtk_container_add (GTK_CONTAINER (row_mess->row), row_mess->box_in);

    gtk_widget_set_name(row_mess->row, "row_from");

    gtk_widget_set_can_focus(row_mess->row, FALSE);
///////////////////////////////////////////////////////////////////////////////
    t_page *page;
    t_list_gtk *list = widge->page_list;
    char *data_me;
    while (list) {
        page = (t_page *)list->data;
        data_me = (char*)g_object_get_data(G_OBJECT(page->list_box), "id");
        //printf("{%s} {%s}\n", widge->login_list, data_me);
        if (strcmp(widge->login_list, data_me) == 0) {
            break;
        }
        list = list->next;
    }
///////////////////////////////////////////////////////////////////////////////
    gtk_list_box_insert (GTK_LIST_BOX(page->list_box), row_mess->row, -1);

    mx_push_front_gtk(&widge->message_list, mess_struct);

    widge->index_mess_to = gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(row_mess->row));

    gdk_threads_add_idle ((GSourceFunc) mx_idle_showall, page->list_box);
    // gtk_widget_show_all(page->list_box);
}
