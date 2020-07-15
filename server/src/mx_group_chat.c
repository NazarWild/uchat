#include "../inc/uchat.h"

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

static int creating_chat(cJSON* MESS, use_mutex_t *mutex) {
    char *str1 = NULL;
    char *str2 = NULL;
    char *ita = mx_itoa(mutex->user_id);
    char *tmp = NULL;

    asprintf(&str1, "'%s %s'", ita, MESS->valuestring);
    mx_add_to_table("chats", "chat", str1, mutex);
    asprintf(&tmp, "chats WHERE chat = %s", str1);
    mx_select("chats_id", tmp, callback_persons_id, &str2, mutex);
    free(tmp);
    free(str1);
    return atoi(str2);
}

static void new_group_chat(use_mutex_t *mutex, cJSON* USERS_GRP, cJSON* MESS) {
    cJSON *USER = NULL;
    cJSON *USER_ID = NULL;
    int chat_id = creating_chat(MESS, mutex);
    char *str = NULL;

    cJSON_ArrayForEach(USER, USERS_GRP) {
        USER_ID = cJSON_GetObjectItemCaseSensitive(USER, "USER_ID");
        asprintf(&str, "%d, %d", atoi(USER_ID->valuestring), chat_id);
        mx_add_to_table("users_chat", "users_id, chats_id", str, mutex);
        free(str);
    }
}

void mx_group_chat(cJSON* root, use_mutex_t *mutex) {
    cJSON* CHAT_ID = cJSON_GetObjectItemCaseSensitive(root, "CHAT_ID");
    cJSON* MESS = cJSON_GetObjectItemCaseSensitive(root, "MESS");
    cJSON* USERS_GRP = cJSON_GetObjectItemCaseSensitive(root, "USERS");

    if (atoi(CHAT_ID->valuestring) == 0) { // просто создается чат
        new_group_chat(mutex, USERS_GRP, MESS);
        return ;
    }
    // else //тут будут уже отправляться сообщения и тд.
        

    
}
