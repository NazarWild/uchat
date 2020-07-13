#include "../inc/uchat.h"

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

void mx_send_group(cJSON* MESS, cJSON* USERS_GRP, cJSON* CHAT_ID, use_mutex_t *mutex) {
    cJSON *USER = NULL;
    cJSON *USER_ID = NULL;
    char *str = NULL;
    char *data = NULL;

    cJSON_ArrayForEach(USER, USERS_GRP) {
        USER_ID = cJSON_GetObjectItemCaseSensitive(USER, "USER_ID");
        asprintf(&str, "sockets WHERE users_id = %d", atoi(USER_ID->valuestring));
        mx_select("socket", str, callback_persons_id, &data, mutex);
        if (data != NULL) {
            // здесь будет функа по отправке сообщения на сокет
            free(data);
        }
        
        free(str);
    }
}
