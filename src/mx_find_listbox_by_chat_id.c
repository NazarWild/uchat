#include "../inc/uchat.h"

void mx_find_listbox_by_chat_id(t_widget_my *widge, int chat_id, int user_which_write, char *mess) {
	t_page *page;
    t_list_gtk *list = widge->page_list;
    int data_me;
    char *user_id;

    while (list->next != NULL) {
        page = (t_page *)list->data;
        data_me = (int)(uintptr_t)g_object_get_data(G_OBJECT(page->list_box), "chat_id");
        if (chat_id == data_me)
            break;
        list = list->next;
    }
    user_id = (char *)g_object_get_data(G_OBJECT(page->list_box), "id");
    widge->login_list = strdup(user_id);
    if (strcmp(widge->login, mx_find_login_by_id(widge->login_id, mx_itoa(user_which_write))) == 0)
        mx_message_to(widge, mess);
    else
        mx_message_from(widge, mess);
}
