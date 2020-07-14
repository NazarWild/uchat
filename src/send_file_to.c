#include "../inc/uchat.h"

void install(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    printf("%s\n", widge->te);
}

void mx_send_file_to(t_widget_my *widge, const gchar *text) {
    GtkWidget *row, *file_to, *fixed,
    *box, *box2, *grid, *label, *box_in, *grid2, *grid3, *install_button;

    row = gtk_list_box_row_new ();
    gtk_widget_set_size_request(row, 590, 30);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row), FALSE);
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row), FALSE);

    widge->te = strdup(text);
    label = gtk_label_new("");

    install_button = gtk_button_new();
    file_to = gtk_button_new_with_label(text);

    widge->install_img = gdk_pixbuf_new_from_file("./img_chat/install.png", NULL);
    widge->install_img = gdk_pixbuf_scale_simple(widge->install_img, 20, 20, GDK_INTERP_BILINEAR);
    widge->install_icon = gtk_image_new_from_pixbuf(widge->install_img);
    gtk_button_set_image (GTK_BUTTON(install_button), widge->install_icon);

    box_in = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    gtk_widget_set_size_request(box_in, 590, 30);

    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);
    box2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, TRUE);

    gtk_box_pack_start(GTK_BOX(box), label, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(box2), install_button, 1, 0, 0);
    gtk_box_pack_start(GTK_BOX(box2), file_to, 1, 0, 0);

    gtk_container_add_with_properties (GTK_CONTAINER (box_in), box, "expand", TRUE, NULL);
    gtk_container_add(GTK_CONTAINER (box_in), box2);

    gtk_container_add (GTK_CONTAINER (row), box_in);

    gtk_widget_set_name(file_to, "message_to");
    gtk_widget_set_name(install_button, "install_button");
    gtk_widget_set_name(row, "row");

    gtk_list_box_insert (GTK_LIST_BOX(widge->list_box), row, -1);

    g_signal_connect (install_button, "clicked", G_CALLBACK(install), widge);

    gtk_widget_show_all (widge->list_box);
}
