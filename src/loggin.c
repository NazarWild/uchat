#include "../inc/uchat.h"

//clang `pkg-config --cflags gtk+-3.0` -o example-0 example_1.c `pkg-config --libs gtk+-3.0`

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

void to_chat(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my*)data;

    const gchar *user_name = gtk_entry_get_text(GTK_ENTRY(widge->user_name));

    const gchar *user_password = gtk_entry_get_text(GTK_ENTRY(widge->user_password));

    if (strlen(user_name) == 0 || strlen(user_password) == 0) {
        printf("Are you kidding me?\n");
    }

    else {
        mx_log_in((char *) user_name, (char *) user_password, widge);
    }
}

void create_user(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my*)data;

    const gchar *create_user_name = gtk_entry_get_text(GTK_ENTRY(widge->create_user_name));

    const gchar *create_user_password = gtk_entry_get_text(GTK_ENTRY(widge->create_user_password));

    const gchar *repeat_user_password = gtk_entry_get_text(GTK_ENTRY(widge->repeat_user_password));

    gtk_widget_hide(widge->win_reg);

    gtk_widget_show_all(widge->win_sign);

    g_print("User login : %s\nUser password : %s\nUser password again : %s\n",
            create_user_name, create_user_password, repeat_user_password);
}

void mx_create_widge(t_widget_my *widge) {

    widge->window = GTK_WIDGET(gtk_builder_get_object (widge->builder, "window"));
    widge->chat = GTK_WIDGET(gtk_builder_get_object (widge->builder, "chat"));

    widge->win_sign = GTK_WIDGET(gtk_builder_get_object (widge->builder, "win_sign"));
    widge->win_reg = GTK_WIDGET(gtk_builder_get_object (widge->builder, "win_reg"));

    widge->sign_in = GTK_WIDGET(gtk_builder_get_object (widge->builder, "sign_in"));
    widge->sign_up = GTK_WIDGET(gtk_builder_get_object (widge->builder, "sign_up"));

    widge->user_name = gtk_entry_new();
    widge->user_password = gtk_entry_new();
    widge->create_user_name = gtk_entry_new();
    widge->create_user_password = gtk_entry_new();
    widge->repeat_user_password = gtk_entry_new();

    widge->user_name = GTK_WIDGET(gtk_builder_get_object (widge->builder, "user_name"));
    widge->user_password = GTK_WIDGET(gtk_builder_get_object (widge->builder, "user_password"));

    widge->create_user_name = GTK_WIDGET(gtk_builder_get_object (widge->builder, "create_user_name"));
    widge->create_user_password = GTK_WIDGET(gtk_builder_get_object (widge->builder, "create_user_password"));
    widge->repeat_user_password = GTK_WIDGET(gtk_builder_get_object (widge->builder, "repeat_user_password"));
    widge->registration = GTK_WIDGET(gtk_builder_get_object (widge->builder, "registration"));
    widge->return_sign_in = GTK_WIDGET(gtk_builder_get_object (widge->builder, "return_sign_in"));
}

int main (int argc, char *argv[]) {
    t_widget_my *widge = (t_widget_my *)malloc(sizeof(t_widget_my));
    GError *error = NULL;

    gtk_init (&argc, &argv);

    widge->builder = gtk_builder_new ();

    if (gtk_builder_add_from_file (widge->builder, "src/login.glade", &error) == 0)
    {
        g_printerr ("Error loading file: %s\n", error->message);
        g_clear_error (&error);
        return 1;
    }
    
    mx_create_widge(widge);

    gtk_widget_show_all(widge->window);

    gtk_widget_hide(widge->win_reg);

    gtk_widget_show_all(widge->win_sign);

    g_signal_connect (widge->sign_up, "clicked", G_CALLBACK(to_reg), widge);

    g_signal_connect (widge->sign_in, "clicked", G_CALLBACK(to_chat), widge);

    g_signal_connect (widge->registration, "clicked", G_CALLBACK(create_user), widge);

    g_signal_connect (widge->return_sign_in, "clicked", G_CALLBACK(to_sign_in), widge);

    g_signal_connect (widge->window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (widge->chat, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    gtk_main ();

    return 0;
}
