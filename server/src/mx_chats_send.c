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
    cJSON *users = NULL;
    char *str = NULL;

    if (chats != NULL) {
        users = cJSON_CreateArray();
        cJSON_AddItemToObject(root, "chats", users);
    }
    else {
        users = cJSON_CreateFalse();
        cJSON_AddItemToObject(root, "chats", users);
        write(1, "DELETING", 8);
    }
    while(chats) {
        creating_cJSON(users, (t_messeges *) chats->data);
        chats = chats->next;
    }
    str = cJSON_Print(root);
    write(mutex->cli_fd, str, strlen(str));
    cJSON_Delete(users);
}
