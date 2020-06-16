#include "../inc/uchat.h"

void send_message(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my*)data;

    gtk_label_set_text(widge->message, "");

    // gtk_widget_show(widge->check);

    const gchar *message = gtk_entry_get_text(GTK_ENTRY(widge->command_line));

    if (strlen(message) == 0) {
        printf("Are you kidding me?\n");
    }
    else {
        gtk_fixed_move(widge->message_win, GTK_WIDGET(widge->message), 15, 100);
        gtk_label_set_text(widge->message, message);
        gtk_entry_set_text(GTK_ENTRY(widge->command_line), "");

    }
}

void create_label(void *data) {
    t_widget_my *widge = (t_widget_my*)data;

    const gchar *message = gtk_entry_get_text(GTK_ENTRY(widge->command_line));

    gtk_label_set_text(widge->message, message);
    gtk_entry_set_text(GTK_ENTRY(widge->command_line), "");
}

void mx_chat_win(t_widget_my *widge) {
    widge->chat = GTK_WIDGET(gtk_builder_get_object (widge->builder, "chat"));

    // widge->check = gtk_label_new("lollll");

    // gtk_fixed_put(widge->message_win, widge->check, 15, 150);

    gtk_widget_hide(widge->window);
    gtk_widget_show_all(widge->chat);
    //
    g_signal_connect (widge->chat, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    // g_signal_connect (widge->setting, "clicked", G_CALLBACK (send_message), widge);

    // g_signal_connect (widge->setting, "clicked", G_CALLBACK (create_label), widge);

}
