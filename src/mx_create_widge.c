#include "../inc/uchat.h"

void mx_create_widge(t_widget_my *widge) {
    widge->window = GTK_WIDGET(gtk_builder_get_object (widge->builder, "window"));

    widge->win_sign = GTK_WIDGET(gtk_builder_get_object (widge->builder, "win_sign"));
    widge->win_reg = GTK_WIDGET(gtk_builder_get_object (widge->builder, "win_reg"));

    widge->sign_in = GTK_WIDGET(gtk_builder_get_object (widge->builder, "sign_in"));
    widge->sign_up = GTK_WIDGET(gtk_builder_get_object (widge->builder, "sign_up"));

    widge->user_name = gtk_entry_new();
    widge->user_password = gtk_entry_new();
    widge->create_user_name = gtk_entry_new();
    widge->create_user_password = gtk_entry_new();
    widge->repeat_user_password = gtk_entry_new();

    widge->command_line = gtk_entry_new();

    widge->user_name = GTK_WIDGET(gtk_builder_get_object (widge->builder, "user_name"));
    widge->user_password = GTK_WIDGET(gtk_builder_get_object (widge->builder, "user_password"));

    widge->create_user_name = GTK_WIDGET(gtk_builder_get_object (widge->builder, "create_user_name"));
    widge->create_user_password = GTK_WIDGET(gtk_builder_get_object (widge->builder, "create_user_password"));
    widge->repeat_user_password = GTK_WIDGET(gtk_builder_get_object (widge->builder, "repeat_user_password"));
    widge->registration = GTK_WIDGET(gtk_builder_get_object (widge->builder, "registration"));
    widge->return_sign_in = GTK_WIDGET(gtk_builder_get_object (widge->builder, "return_sign_in"));


    widge->command_line = GTK_WIDGET(gtk_builder_get_object (widge->builder, "command_line"));
    widge->setting = GTK_WIDGET(gtk_builder_get_object (widge->builder, "setting"));
    // widge->message = GTK_WIDGET(gtk_builder_get_object (widge->builder, "message"));

    widge->name_exists = GTK_LABEL(gtk_builder_get_object (widge->builder, "name_exists"));//nd
    widge->wrong_login = GTK_LABEL(gtk_builder_get_object (widge->builder, "wrong_login"));//nd

    widge->message_win = GTK_FIXED(gtk_builder_get_object (widge->builder, "message_win"));

    widge->list_box = GTK_WIDGET(gtk_builder_get_object(widge->builder, "list_box"));
}
