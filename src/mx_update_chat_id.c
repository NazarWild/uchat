#include "../inc/uchat.h"

void mx_update_chat_id(t_widget_my *widge, char *login, int new_chat_id) {
	t_page *page;
    t_list_gtk *list = widge->page_list;
    char *data_me;
    int chat_id;
    int new = new_chat_id;

    while (list->next != NULL) { 
        page = (t_page *)list->data;
        data_me = (char *)g_object_get_data(G_OBJECT(page->list_box), "id");
        if (mx_strcmp(login, data_me) == 0)
            break;
        list = list->next;
    }
    chat_id = (int)(uintptr_t)g_object_get_data(G_OBJECT(page->list_box), "chat_id");
    if (chat_id == 0)
        g_object_set_data(G_OBJECT(page->list_box), "chat_id", (gpointer)(uintptr_t)(new));
}
