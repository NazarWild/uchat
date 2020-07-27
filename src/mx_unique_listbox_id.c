#include "../inc/uchat.h"

bool mx_unique_listbox_id(t_widget_my *widge, char *login) {
	t_page *page;
    t_list_gtk *list = widge->page_list;
    char *data_me;
    while (list->next != NULL) {
        page = (t_page *)list->data;
        data_me = (char *)g_object_get_data(G_OBJECT(page->list_box), "id");
        if (strcmp(login, data_me) == 0)
            return false;
        list = list->next;
    }
    return true;
}
