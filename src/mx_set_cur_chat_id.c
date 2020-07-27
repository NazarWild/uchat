#include "../inc/uchat.h"

void mx_set_cur_chat_id(t_widget_my *widge) {
	t_page *page;
    t_list_gtk *list = widge->page_list;
    char *data_me;

    while (list->next != NULL) {
        page = (t_page *)list->data;
        data_me = (char *)g_object_get_data(G_OBJECT(page->list_box), "id");
        if (strcmp(widge->login_list, data_me) == 0)
            break;
        list = list->next;
    }
    widge->cur_chat_id = (int)(uintptr_t)g_object_get_data(G_OBJECT(page->list_box), "chat_id");
}
