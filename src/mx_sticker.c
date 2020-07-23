#include "../inc/uchat.h"


static void hide_win(void *data) {
    t_widget_my *widge = (t_widget_my *)data;

    gtk_widget_hide(widge->win_stick);
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
}

void create_sticker_1(t_widget_my *widge, GtkWidget *box) {
    create(widge->b1, "./stickers/1.png", box, widge);
    create(widge->b2, "./stickers/2.png", box, widge);
    create(widge->b3, "./stickers/3.png", box, widge);
    create(widge->b4, "./stickers/4.png", box, widge);
    create(widge->b5, "./stickers/5.png", box, widge);
    create(widge->b6, "./stickers/6.png", box, widge);
    create(widge->b7, "./stickers/7.png", box, widge);
    create(widge->b8, "./stickers/8.png", box, widge);
    create(widge->b9, "./stickers/9.png", box, widge);
    create(widge->b10, "./stickers/10.png", box, widge);
    create(widge->b11, "./stickers/11.png", box, widge);
    create(widge->b12, "./stickers/12.png", box, widge);
    create(widge->b13, "./stickers/13.png", box, widge);
    create(widge->b14, "./stickers/14.png", box, widge);
    create(widge->b15, "./stickers/15.png", box, widge);
    create(widge->b16, "./stickers/16.png", box, widge);
    create(widge->b17, "./stickers/17.png", box, widge);
    create(widge->b18, "./stickers/18.png", box, widge);
    create(widge->b19, "./stickers/19.png", box, widge);
    create(widge->b20, "./stickers/20.png", box, widge);
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

    if (widge->on_sticker == 0) {
        widge->on_sticker = 1;
        gtk_widget_show_all(widge->win_stick);
    }
    else {
        hide_win(widge);
    }
}
