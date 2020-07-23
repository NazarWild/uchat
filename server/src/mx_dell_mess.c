#include "../inc/uchat.h"

void mx_dell_mess(cJSON *root, t_use_mutex *mutex) {
    cJSON* DELL_MESS = cJSON_GetObjectItemCaseSensitive(root, "DELL_MESS");
    cJSON* TEXT_ID = NULL;
    char *str = NULL;

    if (cJSON_IsTrue(DELL_MESS) == 1) {
        TEXT_ID = cJSON_GetObjectItemCaseSensitive(root, "TEXT_ID");
        asprintf(&str, "text WHERE text_id = %d", atoi(TEXT_ID->valuestring));
        mx_set_value("messages", "DELETED", str, mutex);
        free(str);
        //send_new_mess(root, param);
    }

}

