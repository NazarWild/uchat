#include "../inc/uchat.h"

static void creating_cJSON(cJSON *users, t_messeges *chat) {
    cJSON *id = cJSON_CreateString(mx_itoa(chat->id));
    cJSON *last_mess = cJSON_CreateString(chat->text);

    cJSON_AddItemToObject(users, "id", id);
    cJSON_AddItemToObject(users, "last_mess", last_mess);
}

void mx_chats_send(use_mutex_t *mutex) {
    t_list *chats = mx_list_last_users_messeges(mutex);
    cJSON *root = cJSON_CreateObject();
    cJSON *users = cJSON_CreateArray();

    cJSON_AddItemToObject(root, "chats", users);
    while(chats) {
        creating_cJSON(users, (t_messeges *) chats->data);
        chats = chats->next;
    }
    cJSON_Print(root);
    exit(0);
}
