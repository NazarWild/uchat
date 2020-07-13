#include "../inc/uchat.h"

static void back(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    gtk_widget_hide(widge->win_sett);
    gtk_widget_show_all(widge->main_chat);
}

void mx_setting_win(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    g_signal_connect (widge->theme_1, "clicked", G_CALLBACK(mx_theme_1), widge);
    g_signal_connect (widge->theme_2, "clicked", G_CALLBACK(mx_theme_2), widge);
    g_signal_connect (widge->theme_3, "clicked", G_CALLBACK(mx_theme_3), widge);
    g_signal_connect (widge->theme_4, "clicked", G_CALLBACK(mx_theme_4), widge);
    g_signal_connect (widge->theme_5, "clicked", G_CALLBACK(mx_theme_5), widge);
    g_signal_connect (widge->theme_6, "clicked", G_CALLBACK(mx_theme_6), widge);
    g_signal_connect (widge->back, "clicked", G_CALLBACK(back), widge);
    gtk_widget_hide(widge->main_chat);
    gtk_widget_show_all(widge->win_sett);
}
