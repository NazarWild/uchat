#include "../inc/uchat.h" 

int stickers = 0;

static void send_mess(int to, char *mess, int chat_id, t_use_mutex *mutex) {
    char *new = NULL;
    char *type = NULL;

    if (stickers == 1)
        type = strdup("sticker");
    else 
        type = strdup("text");
    asprintf(&new, "{\"IF_MESS\":true,\"FROM\":%d,\"MESS\":\"%s\",\"CHAT_ID\":%d,\"TYPE\":\"%s\"}\n", mutex->user_id, mess, chat_id, type);
    mx_send_user_with_dif_sock(mutex, to, new, strlen(new));
    stickers = 0;
    free(new);
    free(type);
}

static void sockets(cJSON* TO, cJSON* MESS, cJSON* CHAT_ID, t_use_mutex *mutex) {
    char *str1 = NULL;
    char *data = NULL;
    int chat_id = atoi(CHAT_ID->valuestring);  
    t_select *select;

    asprintf(&str1, "sockets where users_id = %d", atoi(TO->valuestring));
    select = mx_struct_select("socket", str1, mx_callback_persons_id, &data);
    mx_select(select, mutex);
    free(str1);
    if (chat_id == 0) //если чата не сущевствует и это новое сообщение, то создаем такой чат
        chat_id = atoi(mx_new_chat(TO, MESS, data, mutex));
    else // в другом случае добавляем сообщение в чат 
        mx_add_message(chat_id, MESS->valuestring, 0, mutex);
    if (data != NULL && chat_id != 0) 
        send_mess(atoi(TO->valuestring), MESS->valuestring, chat_id, mutex);//atoi(TO->valuestring) //atoi(data)
    free(data); 
}

void mx_send_mess(cJSON *root, t_use_mutex *mutex) { //надо отправлять чат айди тоже
    cJSON* if_mess = cJSON_GetObjectItemCaseSensitive(root, "IF_MESS");

    if(cJSON_IsTrue(if_mess) == 1) {
        cJSON* TO = cJSON_GetObjectItemCaseSensitive(root, "TO");
        cJSON* MESS = cJSON_GetObjectItemCaseSensitive(root, "MESS");
        cJSON* TYPE = cJSON_GetObjectItemCaseSensitive(root, "TYPE");
        cJSON* BYTES = cJSON_GetObjectItemCaseSensitive(root, "BYTES");
        cJSON* CHAT_ID = cJSON_GetObjectItemCaseSensitive(root, "CHAT_ID");

        if (strcmp("text", TYPE->valuestring) == 0 || strcmp("sticker", TYPE->valuestring) == 0) {
            if (strcmp("sticker", TYPE->valuestring) == 0)
                stickers = 1;
            if (strcmp(TO->valuestring, "PAPA_BOT") == 0) {
                mx_papa_bot(MESS, mutex);
                return ;
            }
            sockets(TO, MESS, CHAT_ID, mutex);
        }
        else if (strcmp("group_text", TYPE->valuestring) == 0 
            || strcmp("group_text_file", TYPE->valuestring) == 0)
            mx_group_chat(root, mutex);
        else
            mx_file_type(root, mutex);
    }
}
