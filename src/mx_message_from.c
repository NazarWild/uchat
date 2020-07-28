#include "../inc/uchat.h"

void mx_idle_showall(void *widget) {
    gtk_widget_show_all((GtkWidget *)widget);//
}

void mx_idle_hide(void *widget) {
    gtk_widget_hide((GtkWidget *)widget);//
}

void mx_idle_show(void *widget) {
    gtk_widget_show((GtkWidget *)widget);//
}

void mx_idle_destroy(void *widget) {
    gtk_widget_destroy((GtkWidget *)widget);//
}

void mx_message_from(t_widget_my *widge, const gchar *text) {
    printf("here1\n");
    // t_message *mess_struct = malloc(sizeof(t_message));
    t_row_mess *row_s = malloc(sizeof(t_row_mess));

    row_s->row = gtk_list_box_row_new ();
    gtk_widget_set_size_request(row_s->row, 590, 30);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row_s->row), FALSE);
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row_s->row), FALSE);

    row_s->label = gtk_label_new("");

    // mess_struct->message = gtk_button_new_with_label(text);
    row_s->message = gtk_button_new_with_label(text);

    printf("here2\n");
    row_s->box_in = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    gtk_widget_set_size_request(row_s->box_in, 590, 30);

    row_s->box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    row_s->box2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    row_s->box3 = gtk_box_new (GTK_ORIENTATION_VERTICAL, TRUE);
    row_s->box4 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);

    row_s->nickname = mx_name_mess_from("opoliarenk");
    row_s->data_box = mx_time_mess_from("22:12");
    gtk_box_pack_start(GTK_BOX(row_s->box3), row_s->nickname, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_s->box3), row_s->message, 1, 0, 0);
    // gtk_box_pack_start(GTK_BOX(row_s->box3), mess_struct->message, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_s->box3), row_s->data_box, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_s->box2), row_s->box3, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(row_s->box), row_s->label, 1, 0, 0);

    printf("here3\n");
    gtk_container_add(GTK_CONTAINER (row_s->box_in), row_s->box2);
    gtk_container_add_with_properties (GTK_CONTAINER (row_s->box_in), row_s->box, "expand", TRUE, NULL);

    gtk_container_add (GTK_CONTAINER (row_s->row), row_s->box_in);

    gtk_widget_set_name(row_s->message, "message_from");
    // gtk_widget_set_name(mess_struct->message, "message_from");
    gtk_widget_set_name(row_s->row, "row_from");

    gtk_widget_set_can_focus(row_s->message, FALSE);
    // gtk_widget_set_can_focus(mess_struct->message, FALSE);
    gtk_widget_set_can_focus(row_s->row, FALSE);
///////////////////////////////////////////////////////////////////////////////
    printf("here4\n");
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
        printf("ne norm\n");
        list = list->next;
    }
    printf("here5\n");
///////////////////////////////////////////////////////////////////////////////
    gtk_list_box_insert (GTK_LIST_BOX(page->list_box), row_s->row, -1);
    // mx_push_front_gtk(&widge->message_list, mess_struct);

    printf("here6\n");
    // widge->index_mess_to = gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(row_s->row));
    printf("here7\n");
    gdk_threads_add_idle ((GSourceFunc) mx_idle_showall, page->list_box);
    //gtk_widget_show_all(page->list_box);//
    printf("here8\n");
}
