#include "../inc/uchat.h"

void to_reg(GtkWidget* widget, void*data) {
    t_widget_my *widge = (t_widget_my*)data;

    gtk_entry_set_text(GTK_ENTRY(widge->user_name), "");

    gtk_entry_set_text(GTK_ENTRY(widge->user_password), "");

    gtk_widget_hide(widge->win_sign);

    gtk_widget_show_all(widge->win_reg);
}

void to_sign_in(GtkWidget* widget, void*data) {
    t_widget_my *widge = (t_widget_my*)data;

    gtk_entry_set_text(GTK_ENTRY(widge->create_user_name), "");

    gtk_entry_set_text(GTK_ENTRY(widge->create_user_password), "");

    gtk_entry_set_text(GTK_ENTRY(widge->repeat_user_password), "");

    gtk_widget_hide(widge->win_reg);

    gtk_widget_show_all(widge->win_sign);
}

void create_user(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my*)data;

    const gchar *create_user_name = gtk_entry_get_text(GTK_ENTRY(widge->create_user_name));

    const gchar *create_user_password = gtk_entry_get_text(GTK_ENTRY(widge->create_user_password));

    const gchar *repeat_user_password = gtk_entry_get_text(GTK_ENTRY(widge->repeat_user_password));

    if (strlen(create_user_name) == 0 || strlen(create_user_password) == 0|| strlen(repeat_user_password) == 0) {
        printf("Are you kidding me?\n");
    }
    if (!strcmp(create_user_password, repeat_user_password)) {
    mx_register((char *) create_user_name, (char *) create_user_password, widge);
    gtk_widget_hide(widge->win_reg);
    gtk_widget_show_all(widge->win_sign);
}

    // g_print("User login : %s\nUser password : %s\nUser password again : %s\n",
    //         create_user_name, create_user_password, repeat_user_password); //позже убрать
    // // }
    // // else {
    // //     gtk_entry_set_text(GTK_ENTRY(widge->repeat_user_password), "");
    // //     GdkRGBA red = {0, 0xffff, 0x0000, 0x0000};
    // //     gtk_widget_override_background_color(widge->repeat_user_password, GTK_STATE_FLAG_NORMAL, &red);
    // // }
}

void to_chat(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my*)data;

    const gchar *user_name = gtk_entry_get_text(GTK_ENTRY(widge->user_name));

    const gchar *user_password = gtk_entry_get_text(GTK_ENTRY(widge->user_password));

    mx_profile_gtk(widge);
    //mx_smile_box();
    // if (strlen(user_name) == 0 || strlen(user_password) == 0) {
    //    printf("Are you kidding me?\n");
    // }
    // else
    //    mx_log_in((char *) user_name, (char *) user_password, widge);
}

void mx_login_win(t_widget_my *widge) {
    gtk_widget_show_all(widge->window);

    gtk_widget_hide(widge->win_reg);

    gtk_widget_show_all(widge->win_sign);

    g_signal_connect (widge->sign_up, "clicked", G_CALLBACK(to_reg), widge);

    g_signal_connect (widge->sign_in, "clicked", G_CALLBACK(to_chat), widge);

    g_signal_connect (widge->registration, "clicked", G_CALLBACK(create_user), widge);

    g_signal_connect (widge->return_sign_in, "clicked", G_CALLBACK(to_sign_in), widge);

    g_signal_connect (widge->window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
}
