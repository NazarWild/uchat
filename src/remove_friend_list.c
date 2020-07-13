#include "../inc/uchat.h"

static void delete_list_box_row(t_widget_my *widge) {
    GtkListBoxRow *row;

    row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(widge->friends), widge->index);
    gtk_container_remove(GTK_CONTAINER(widge->friends), GTK_WIDGET(row));

}

void mx_remove_friend_list(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    while(widge->index >= 0) {
        delete_list_box_row(widge);
        widge->index--;
    }
    widge->id_friend = 0;
}
