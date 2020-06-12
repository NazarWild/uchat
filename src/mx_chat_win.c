#include "../inc/uchat.h"

void mx_chat_win(t_widget_my *widge) {
    widge->chat = GTK_WIDGET(gtk_builder_get_object (widge->builder, "chat"));

    gtk_widget_hide(widge->window);
    gtk_widget_show_all(widge->chat);

    g_signal_connect (widge->chat, "destroy", G_CALLBACK (gtk_main_quit), NULL);
}
