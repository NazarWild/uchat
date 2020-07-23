#include "../inc/uchat.h"

void mx_delete_row(GtkWidget *list_box, gint index) {
    GtkListBoxRow *row;

    row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(list_box), index);
    gtk_container_remove(GTK_CONTAINER(list_box), GTK_WIDGET(row));
}
