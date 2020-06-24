#include "../inc/uchat.h"

void girl1(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;
    GtkWidget *girl1 = gtk_image_new_from_file("res/girl1.png");

    gtk_button_set_image(GTK_BUTTON(widge->profile_photo_button), girl1);
}
void girl2(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;
    GtkWidget *girl2 = gtk_image_new_from_file("res/girl2.png");

    gtk_button_set_image(GTK_BUTTON(widge->profile_photo_button), girl2);
}
void girl3(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;
    GtkWidget *girl3 = gtk_image_new_from_file("res/girl3.png");

    gtk_button_set_image(GTK_BUTTON(widge->profile_photo_button), girl3); 
}
void man1(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;
    GtkWidget *man1 = gtk_image_new_from_file("res/man1.png");

    gtk_button_set_image(GTK_BUTTON(widge->profile_photo_button), man1);
}
void man2(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;
    GtkWidget *man2 = gtk_image_new_from_file("res/man2.png");//2

    gtk_button_set_image(GTK_BUTTON(widge->profile_photo_button), man2);
}
void man3(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;
    GtkWidget *man3 = gtk_image_new_from_file("res/man3.png");

    gtk_button_set_image(GTK_BUTTON(widge->profile_photo_button), man3);
}
void mx_profile_photo_box(t_widget_my *widge) {
    GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    GtkWidget *b1 = gtk_button_new();
    GtkWidget *b2 = gtk_button_new();
    GtkWidget *b3 = gtk_button_new();
    GtkWidget *b4 = gtk_button_new();
    GtkWidget *b5 = gtk_button_new();
    GtkWidget *b6 = gtk_button_new();
    widge->man1 = gtk_image_new_from_file("res/man1.png");
    widge->man2 = gtk_image_new_from_file("res/man2.png");
    widge->man3 = gtk_image_new_from_file("res/man3.png");
    widge->girl1 = gtk_image_new_from_file("res/girl1.png");
    widge->girl2 = gtk_image_new_from_file("res/girl2.png");
    widge->girl3 = gtk_image_new_from_file("res/girl3.png");
    
    gtk_button_set_image(GTK_BUTTON(b1), widge->man1);
    gtk_button_set_image(GTK_BUTTON(b2), widge->man2);
    gtk_button_set_image(GTK_BUTTON(b3), widge->man3);
    gtk_button_set_image(GTK_BUTTON(b4), widge->girl1);
    gtk_button_set_image(GTK_BUTTON(b5), widge->girl2);
    gtk_button_set_image(GTK_BUTTON(b6), widge->girl3);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    //box
    gtk_box_pack_start(GTK_BOX(box), box1, 1, 1, 1);
    gtk_box_pack_start(GTK_BOX(box), box2, 1, 1, 1);
    //box1
    gtk_box_pack_start(GTK_BOX(box1), b1, 1, 1, 1);
    gtk_box_pack_start(GTK_BOX(box1), b2, 1, 1, 1);
    gtk_box_pack_start(GTK_BOX(box1), b3, 1, 1, 1);
    //box2
    gtk_box_pack_start(GTK_BOX(box2), b4, 1, 1, 1);
    gtk_box_pack_start(GTK_BOX(box2), b5, 1, 1, 1);
    gtk_box_pack_start(GTK_BOX(box2), b6, 1, 1, 1);


    g_signal_connect(b1, "clicked", G_CALLBACK(man1), widge);
    g_signal_connect(b2, "clicked", G_CALLBACK(man2), widge);
    g_signal_connect(b3, "clicked", G_CALLBACK(man3), widge);
    g_signal_connect(b4, "clicked", G_CALLBACK(girl1), widge);
    g_signal_connect(b5, "clicked", G_CALLBACK(girl2), widge);
    g_signal_connect(b6, "clicked", G_CALLBACK(girl3), widge);

    gtk_container_add (GTK_CONTAINER (window), box);
    gtk_widget_show_all (window);
}
