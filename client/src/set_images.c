#include "../inc/uchat.h"

static void set_images_1(t_widget_my *widge) {
    widge->profile_img = gdk_pixbuf_new_from_file("./client/img_chat/profile.png", NULL);
    widge->profile_img = gdk_pixbuf_scale_simple(widge->profile_img, 20, 20, GDK_INTERP_BILINEAR);
    widge->profile_icon = gtk_image_new_from_pixbuf(widge->profile_img);
    gtk_button_set_image (GTK_BUTTON(widge->profile_button), widge->profile_icon);
//image for profile button
    widge->send_img = gdk_pixbuf_new_from_file("./client/img_chat/send_icon_4.png", NULL);
    widge->send_img = gdk_pixbuf_scale_simple(widge->send_img, 20, 20, GDK_INTERP_BILINEAR);
    widge->send_icon = gtk_image_new_from_pixbuf(widge->send_img);
    gtk_button_set_image (GTK_BUTTON(widge->send_button), widge->send_icon);
//image for send button
    widge->smile_img = gdk_pixbuf_new_from_file("./client/img_chat/sticker.jpg", NULL);
    widge->smile_img = gdk_pixbuf_scale_simple(widge->smile_img, 20, 20, GDK_INTERP_BILINEAR);
    widge->smile_icon = gtk_image_new_from_pixbuf(widge->smile_img);
    gtk_button_set_image (GTK_BUTTON(widge->sticker_pack), widge->smile_icon);
//image for sticker button
}

static void set_images_2(t_widget_my *widge) {
    widge->file_img = gdk_pixbuf_new_from_file("./client/img_chat/file.png", NULL);
    widge->file_img = gdk_pixbuf_scale_simple(widge->file_img, 20, 20, GDK_INTERP_BILINEAR);
    widge->file_icon = gtk_image_new_from_pixbuf(widge->file_img);
    gtk_button_set_image (GTK_BUTTON(widge->file_button), widge->file_icon);
//image for file button
    widge->achiev_img = gdk_pixbuf_new_from_file("./client/img_chat/achive.png", NULL);
    widge->achiev_img = gdk_pixbuf_scale_simple(widge->achiev_img, 20, 20, GDK_INTERP_BILINEAR);
    widge->achiev_icon = gtk_image_new_from_pixbuf(widge->achiev_img);
    gtk_button_set_image (GTK_BUTTON(widge->achiev), widge->achiev_icon);
//image for hazker button
    widge->setting_img = gdk_pixbuf_new_from_file("./client/img_chat/setting.png", NULL);
    widge->setting_img = gdk_pixbuf_scale_simple(widge->setting_img, 20, 20, GDK_INTERP_BILINEAR);
    widge->setting_icon = gtk_image_new_from_pixbuf(widge->setting_img);
    gtk_button_set_image (GTK_BUTTON(widge->setting), widge->setting_icon);
//image for setting button
}

void mx_set_images(t_widget_my *widge) {
    set_images_1(widge);
    set_images_2(widge);
}
