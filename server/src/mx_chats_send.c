#include "../inc/uchat.h"

static void adding(t_messeges *chat, cJSON *who_in_chat) {
    t_list *users = chat->who_is_here;
    cJSON *user_id = NULL;

    while (users) {
        user_id = cJSON_CreateString((char *) users->data);
        cJSON_AddItemToObject(who_in_chat, "user_in_chat", user_id);
        users = users->next;
    }
}

static void creating_cJSON(cJSON *users, t_messeges *chat) { // надо знать кто последний отправил сообщение и кто учавствует в этом чате
    cJSON *id = cJSON_CreateString(mx_itoa(chat->chats_id));
    cJSON *last_mess = cJSON_CreateString(chat->text);
    cJSON *who_in_chat = cJSON_CreateArray();
    char *str = mx_itoa(chat->who_write);
    cJSON *who_write = cJSON_CreateString(str);

    cJSON_AddItemToObject(users, "id", id);
    cJSON_AddItemToObject(users, "last_mess", last_mess);
    cJSON_AddItemToObject(users, "who_write", who_write);
    cJSON_AddItemToObject(users, "who_in_chat", who_in_chat);
    adding(chat, who_in_chat);
    free(str);
}

static void cjson_cycles(cJSON *users, t_list *chats, cJSON *info) {
    while(chats) {
        info = cJSON_CreateObject();
        cJSON_AddItemToArray(users, info);
        creating_cJSON(info, (t_messeges *) chats->data);
        chats = chats->next;
    }
}

static void lol_send(t_use_mutex *mutex, cJSON *root) {
    char *str = NULL;
        str = cJSON_Print(root);
    // write(mutex->cli_fd, str, strlen(str));
    SSL_write(mutex->my_ssl, str, strlen(str));
    //write(1, str, strlen(str));
    // write(mutex->cli_fd, str, strlen(str));
    free(str);
}

void mx_chats_send(t_use_mutex *mutex) {
    t_list *chats = mx_list_last_users_messeges(mutex);
    cJSON *root = cJSON_CreateObject();
    cJSON *users = NULL;
    cJSON *info = NULL;
    cJSON *if_chats = NULL;

    if (chats != NULL) {
        if_chats = cJSON_CreateTrue();
        users = cJSON_CreateArray();
        cJSON_AddItemToObject(root, "if_chats", if_chats);
        cJSON_AddItemToObject(root, "chats", users);
    }
    else {
        if_chats = cJSON_CreateTrue();
        users = cJSON_CreateFalse();
        cJSON_AddItemToObject(root, "if_chats", if_chats);
        cJSON_AddItemToObject(root, "chats", users);
        write(1, "DELETING", 8);
    }
    cjson_cycles(users, chats, info);
    lol_send(mutex, root);
    cJSON_Delete(users);
}
