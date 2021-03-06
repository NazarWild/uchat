#include "../inc/uchat.h"


static void hide_win(void *data) {
    t_widget_my *widge = (t_widget_my *)data;

    gdk_threads_add_idle ((GSourceFunc) mx_idle_hide, widge->win_stick);
    // gtk_widget_hide(widge->win_stick);
    widge->on_sticker = 0;
}

static void create(GtkWidget *b1, char *name_file, GtkWidget *box, t_widget_my *widge) {
    b1 = gtk_button_new();
    widge->b1_img = gdk_pixbuf_new_from_file(name_file, NULL);
    widge->b1_img = gdk_pixbuf_scale_simple(widge->b1_img, 150, 150, GDK_INTERP_BILINEAR);
    widge->b1_icon = gtk_image_new_from_pixbuf(widge->b1_img);
    gtk_button_set_image (GTK_BUTTON(b1), widge->b1_icon);
    gtk_box_pack_start(GTK_BOX(box), b1, 0, 0, 10);
    gtk_widget_set_name(b1, "sticker");
    gtk_widget_set_can_focus(b1, FALSE);
    g_object_set_data(G_OBJECT(b1), "sticker_path", name_file);
    widge->sticker_to = 1;
    g_signal_connect (b1, "clicked", G_CALLBACK(mx_sendsticker_to), widge);
}

static void create_sticker_1(t_widget_my *widge, GtkWidget *box) {
    create(widge->b1, "./client/stickers/1.png", box, widge);
    create(widge->b2, "./client/stickers/2.png", box, widge);
    create(widge->b3, "./client/stickers/3.png", box, widge);
    create(widge->b4, "./client/stickers/4.png", box, widge);
    create(widge->b5, "./client/stickers/5.png", box, widge);
    create(widge->b6, "./client/stickers/6.png", box, widge);
    create(widge->b7, "./client/stickers/7.png", box, widge);
    create(widge->b8, "./client/stickers/8.png", box, widge);
    create(widge->b9, "./client/stickers/9.png", box, widge);
    create(widge->b10, "./client/stickers/10.png", box, widge);
    create(widge->b11, "./client/stickers/11.png", box, widge);
    create(widge->b12, "./client/stickers/12.png", box, widge);
    create(widge->b13, "./client/stickers/13.png", box, widge);
    create(widge->b14, "./client/stickers/14.png", box, widge);
    create(widge->b15, "./client/stickers/15.png", box, widge);
    create(widge->b16, "./client/stickers/16.png", box, widge);
    create(widge->b17, "./client/stickers/17.png", box, widge);
    create(widge->b18, "./client/stickers/18.png", box, widge);
    create(widge->b19, "./client/stickers/19.png", box, widge);
    create(widge->b20, "./client/stickers/20.png", box, widge);
}

void mx_create_stick(t_widget_my *widge) {
    widge->win_stick = gtk_window_new(GTK_WINDOW_POPUP);
    gtk_window_set_default_size(GTK_WINDOW(widge->win_stick), 805, 160);
    gtk_window_get_position(GTK_WINDOW(widge->chat), &widge->window_x, &widge->window_y);
    gtk_window_move(GTK_WINDOW(widge->win_stick), widge->window_x, widge->window_y + 520);
    widge->scroll_stick = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(widge->scroll_stick), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    widge->box_stick = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    create_sticker_1(widge, widge->box_stick);
    gtk_container_add(GTK_CONTAINER(widge->scroll_stick), widge->box_stick);
    gtk_container_add(GTK_CONTAINER(widge->win_stick), widge->scroll_stick);
    gtk_widget_set_name(widge->win_stick, "sticker_win");
}


void mx_sticker(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;

    gtk_window_get_position(GTK_WINDOW(widge->chat), &widge->window_x, &widge->window_y);
    gtk_window_move(GTK_WINDOW(widge->win_stick), widge->window_x, widge->window_y + 520);
    if (widge->on_sticker == 0) {
        widge->on_sticker = 1;
        gdk_threads_add_idle ((GSourceFunc) mx_idle_showall, widge->win_stick);
        // (widge->win_stick);
    }
    else {
        hide_win(widge);
    }
}
