#include "../inc/uchat.h"

void mx_mini_profile_gtk(t_widget_my *widge) {
    GtkWidget *date;//label
    GtkWidget *nick;//label
    GtkWidget *name;//label
    GtkWidget *status;//label
    GdkPixbuf *anon_pix;
    GtkWidget *photo;

    anon_pix = gdk_pixbuf_new_from_file("img_chat/anonym.png", NULL);
    anon_pix = gdk_pixbuf_scale_simple(anon_pix, 100, 100, GDK_INTERP_BILINEAR);
    photo = gtk_image_new_from_pixbuf(anon_pix);

    GtkWidget *sep_h = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    GtkWidget *sep_v = gtk_separator_new(GTK_ORIENTATION_VERTICAL);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);

    widge->mini_window_profile = gtk_window_new (GTK_WINDOW_POPUP);

    gtk_window_set_default_size(GTK_WINDOW(widge->mini_window_profile), 350, 120);
    // gtk_window_get_position(GTK_WINDOW(widge->chat), &widge->window_x, &widge->window_y);
    // gtk_window_move(GTK_WINDOW(widge->mini_window_profile), widge->window_x + 100, widge->window_y + 72);

    status = gtk_label_new("IN LOVE");
    date = gtk_label_new("27.10.1999");
    name = gtk_label_new("Дикий Назар");
    nick = gtk_label_new("wildscorpi");

    //box2
    gtk_box_pack_start(GTK_BOX(box2), name, 0, 0, 20);
    gtk_box_pack_start(GTK_BOX(box2), status, 0, 0, 20);
    gtk_box_pack_start(GTK_BOX(box2), date, 0, 0, 20);
    //box1
    gtk_box_pack_start(GTK_BOX(box1), photo, 0, 0, 1);
    gtk_box_pack_start(GTK_BOX(box1), sep_h, 0, 0, 1);//sep-h
    gtk_box_pack_start(GTK_BOX(box1), nick, 1, 0, 1);
    //box
    gtk_box_pack_start(GTK_BOX(box), box2, 1, 0, 1);
    gtk_box_pack_start(GTK_BOX(box), sep_v, 0, 0, 1);//sep-v
    gtk_box_pack_start(GTK_BOX(box), box1, 1, 0, 1);

    gtk_container_add (GTK_CONTAINER (widge->mini_window_profile), box);
    gtk_widget_show_all (widge->mini_window_profile);
    gtk_widget_hide (widge->mini_window_profile);
}