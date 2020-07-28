#include "../inc/uchat.h"

static void sending(char *str, cJSON *root, t_use_mutex *param) {
    cJSON* USR_ID = cJSON_GetObjectItemCaseSensitive(root, "USR_ID");
    char *str1 = NULL;
    char *data = NULL;
    t_select *select;

    asprintf(&str1, "sockets where users_id = %d", atoi(USR_ID->valuestring));
    select = mx_struct_select("socket", str1, mx_callback_persons_id, &data);
    mx_select(select, param);
    if (data != NULL)
        SSL_write(param->my_ssl, str, strlen(str));
}

static void send_new_mess(cJSON *root, t_use_mutex *param) {
    cJSON* TEXT_ID = cJSON_GetObjectItemCaseSensitive(root, "TEXT_ID");
    cJSON* RE_MESS = cJSON_GetObjectItemCaseSensitive(root, "RE_MESS");
    cJSON* ID_MESS = cJSON_GetObjectItemCaseSensitive(root, "ID_MESS");
    cJSON* CHAT_ID = cJSON_GetObjectItemCaseSensitive(root, "CHAT_ID");
    char *str = NULL;

    asprintf(&str, "{\"CHANGE_MESS\":true,\"RE_MESS\":\"%s\",\"TEXT_ID\":%d,\"ID_MESS\":%d,\"CHAT_ID\":%d\n",
            RE_MESS->valuestring, atoi(TEXT_ID->valuestring), atoi(ID_MESS->valuestring), atoi(CHAT_ID->valuestring));
    
}

void mx_change_mess(cJSON *root, t_use_mutex *param) {
    cJSON* CHANGE_MESS = cJSON_GetObjectItemCaseSensitive(root, "CHANGE_MESS");
    cJSON* TEXT_ID = NULL;
    cJSON* RE_MESS = NULL;
    char *str = NULL;

    if (cJSON_IsTrue(CHANGE_MESS) == 1) {
        RE_MESS = cJSON_GetObjectItemCaseSensitive(root, "RE_MESS");
        TEXT_ID = cJSON_GetObjectItemCaseSensitive(root, "TEXT_ID");
        asprintf(&str, "text WHERE text_id = %d", atoi(TEXT_ID->valuestring));
        mx_set_value("messages", RE_MESS->valuestring, str, param);
        free(str);
        send_new_mess(root, param);
    }
}

