#include "../inc/uchat.h"

// static void delete_list_box_row(t_widget_my *widge) {
//     GtkListBoxRow *row;

//     row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(widge->list_box), widge->index_mess_to);
//     gtk_container_remove(GTK_CONTAINER(widge->list_box), GTK_WIDGET(row));

// }

// void mx_remove_mess(void *data) {
//     t_widget_my *widge = (t_widget_my *)data;

//     while(widge->index_mess_to >= 0) {
//         delete_list_box_row(widge);
//         widge->index_mess_to--;
//     }
//     widge->message_id = 0;
// }
