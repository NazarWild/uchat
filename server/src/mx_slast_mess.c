#include "../inc/uchat.h"

void mx_slast_mess(cJSON *root, t_use_mutex *param) {
    cJSON* if_mess = cJSON_GetObjectItemCaseSensitive(root, "LAST_MESS");
    cJSON* CHAT_ID = cJSON_GetObjectItemCaseSensitive(root, "CHAT_ID");

    if (cJSON_IsTrue(if_mess) == 1)
        //mx_history_chat()
}
