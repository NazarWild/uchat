#include "../inc/uchat.h"

void mx_chat_win(t_widget_my *widge) {
    widge->chat = GTK_WIDGET(gtk_builder_get_object (widge->builder, "chat"));

    gtk_widget_hide(widge->window);
    // gdk_threads_add_idle ((GSourceFunc) mx_idle_hide, widge->window);
    // gdk_threads_add_idle ((GSourceFunc) mx_idle_showall, widge->chat);
    gtk_widget_show_all(widge->chat);
    gtk_widget_hide(widge->win_sett);
    // gdk_threads_add_idle ((GSourceFunc) mx_idle_hide, widge->win_sett);
    g_signal_connect (widge->chat, "destroy", G_CALLBACK (gtk_main_quit), NULL);
}
