#include "../inc/uchat.h"
#include <stdio.h>
#include <stdlib.h>

char *find_id(t_list *list, char *login) {
    t_list *p = list;

    while (p) {
        if (strcmp(p->login, login) == 0)
            break;
        p = p->next;
    }
    return p->id;
}

static void change_pos(GtkWidget *widget, void *data) {
    static gdouble uper = 0;

    if (uper != gtk_adjustment_get_upper(GTK_ADJUSTMENT(widget))) {
        gtk_adjustment_set_value(GTK_ADJUSTMENT(widget), gtk_adjustment_get_upper(GTK_ADJUSTMENT(widget)));
        uper = gtk_adjustment_get_upper(GTK_ADJUSTMENT(widget));
    }
}

void p(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;
    widge->login_list = (char *) gtk_button_get_label(GTK_BUTTON(widget));
    t_list *p = widge->login_id;

    gtk_button_set_label (GTK_BUTTON(widge->who_writing), widge->login_list);
    // mx_remove_mess(widge);
    widge->to = find_id(p, widge->login_list);
            // write(1, widge->to, strlen(widge->to));
            // write(1,"\n", strlen("\n"));
            // write(1, widge->login_list, strlen(widge->login_list));
            // write(1,"\n", strlen("\n"));
    int i = (int)(uintptr_t)g_object_get_data(G_OBJECT(widget), "id");
    printf("*%i*\n", i);
    gtk_notebook_set_current_page(GTK_NOTEBOOK(widge->notebook), i);
}


void mx_online_img(t_widget_my *widge, int online, GtkWidget *button) {
    if (online == 1) {
        widge->online_img = gdk_pixbuf_new_from_file("./img_chat/plus.png", NULL);
        widge->online_img = gdk_pixbuf_scale_simple(widge->online_img, 15, 15, GDK_INTERP_BILINEAR);
        widge->online_icon = gtk_image_new_from_pixbuf(widge->online_img);
        gtk_button_set_image (GTK_BUTTON(button), widge->online_icon);
    }
    else {
        widge->offline_img = gdk_pixbuf_new_from_file("./img_chat/minus.png", NULL);
        widge->offline_img = gdk_pixbuf_scale_simple(widge->offline_img, 20, 20, GDK_INTERP_BILINEAR);
        widge->offline_icon = gtk_image_new_from_pixbuf(widge->offline_img);
        gtk_button_set_image (GTK_BUTTON(button), widge->offline_icon);
    }
}

void mx_create_friend(t_widget_my *widge, const gchar *text, int online, t_page *page) {
    GtkWidget *row, *box, *box_in, *online_button;

    row = gtk_list_box_row_new ();
    gtk_widget_set_size_request(row, 180, 40);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), FALSE);
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

    online_button = gtk_button_new();
    mx_online_img(widge, online, online_button);

    page->friend_butt = gtk_button_new_with_label(text);

    box_in = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    gtk_widget_set_size_request(box_in, 170, 25);

    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    gtk_widget_set_size_request(box, 170, 35);

    gtk_box_pack_start(GTK_BOX(box), online_button, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(box), page->friend_butt, 1, 1, 0);

    gtk_container_add(GTK_CONTAINER (box_in), box);

    gtk_container_add (GTK_CONTAINER (row), box_in);

    gtk_widget_set_name(page->friend_butt, "chat_button");
    gtk_widget_set_name(online_button, "online_butt");

    gtk_widget_set_can_focus(online_button, FALSE);
    gtk_widget_set_can_focus(row, FALSE);
    gtk_widget_set_can_focus(page->friend_butt, FALSE);

    gtk_list_box_insert (GTK_LIST_BOX(widge->friends), row, -1);

    int id = widge->id_lb_sw;
    g_object_set_data(G_OBJECT(page->friend_butt), "id", (gpointer)(uintptr_t)(id));
///////////////////////////////////////////////////////////////////////////////
    mx_create_chat(page, widge, text);
    g_signal_connect (page->friend_butt, "clicked", G_CALLBACK(p), widge);

    mx_push_front_gtk(&widge->page_list, page);
///////////////////////////////////////////////////////////////////////////////

    widge->id_lb_sw++;

    // widge->index = gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(row));

    gtk_widget_show_all (widge->friends);
}
