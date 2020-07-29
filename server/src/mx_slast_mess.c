#include "../inc/uchat.h"

static int count_of_mess(t_list *p) {
    int count = 0;

    while (p) {
        count++;
        p = p->next;
    }
    return count;
}

static void send_r(cJSON *root, t_use_mutex *param) {
    char *str = cJSON_Print(root);

    SSL_write(param->my_ssl, str, strlen(str));
}

static void add_l(t_history *hstr, cJSON *obj) {
    cJSON *text = cJSON_CreateString(hstr->text);
    cJSON *user_id = cJSON_CreateNumber(hstr->user_id);
    cJSON *chats_id = cJSON_CreateNumber(hstr->chats_id);

    cJSON_AddItemToObject(obj, "text", text);
    cJSON_AddItemToObject(obj, "user_id", user_id);
    cJSON_AddItemToObject(obj, "chats_id", chats_id);
}

static void send_json_mess(t_list *list, t_use_mutex *param) {
    cJSON *last_mess = cJSON_CreateTrue();
    cJSON *root = cJSON_CreateObject();
    cJSON *mess_l = cJSON_CreateArray();
    cJSON *obj = NULL;
    int count = count_of_mess(list);
    t_history *hstr = NULL;

    cJSON_AddItemToObject(root, "LAST", last_mess);
    cJSON_AddItemToObject(root, "messages", mess_l);
    for (int i = 0; i < count; i++) {
        obj = cJSON_CreateObject();
        cJSON_AddItemToArray(mess_l, obj);
        hstr = list->data;
        add_l(hstr, obj);
        list = list->next;
    }
    send_r(root, param);
}

void mx_slast_mess(cJSON *root, t_use_mutex *param) {
    cJSON* if_mess = cJSON_GetObjectItemCaseSensitive(root, "LAST_MESS");
    cJSON* CHAT_ID = cJSON_GetObjectItemCaseSensitive(root, "CHAT_ID");
    t_list *l = NULL;

    if (cJSON_IsTrue(if_mess) == 1 && CHAT_ID->valueint != 0) {
        l = mx_history_chat(CHAT_ID->valueint, param);
        send_json_mess(l, param);
    }
}
