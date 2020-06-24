#include "../inc/uchat.h"

int main(int argc, char *argv[]) {
    t_widget_my *widge = (t_widget_my *)malloc(sizeof(t_widget_my));

    GError *error = NULL;

    gtk_init (&argc, &argv);

    widge->builder = gtk_builder_new ();

    if (gtk_builder_add_from_file (widge->builder, "src/login_new.glade", &error) == 0)
    {
        g_printerr ("Error loading file: %s\n", error->message);
        g_clear_error (&error);
        return 1;
    }

    mx_create_widge(widge);
    mx_login_win(widge);
    

    gtk_main ();
    //system("leaks -q klient");
    return 0;
}
