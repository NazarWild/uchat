#include "../inc/uchat.h" 

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

static void send_mess(int to, char *mess, use_mutex_t *mutex) {
    char *new = NULL;

    asprintf(&new, "{\"FROM\":%d,\"MESS\":%s}\n", mutex->user_id, mess);
    write(to, new, strlen(new));
    free(new);
}

static void sockets(cJSON* TO, cJSON* MESS, use_mutex_t *mutex) {
    char *str1 = NULL;
    char *data = NULL;
    char *data2 = NULL;

    asprintf(&str1, "sockets where users_id = %d", atoi(TO->valuestring));
    mx_select("socket", str1, callback_persons_id, &data, mutex);
    free(str1);
    // надо найти у двух юзеров общий чат, если его нет, то создать чат и внести кто туда относится!
    // asprintf(&str1, "users_chat where users_id = %s AND users_id = %s", TO->valuestring, FROM->valuestring);
    // mx_select("chats_id", str1, callback_persons_id, &data, mutex);
    if (data != NULL)
        send_mess(atoi(data), MESS->valuestring, mutex);
    
    //mx_add_message(FROM->valuestring, NULL, MESS->valuestring, 0, mutex);
}

void mx_send_mess(cJSON *root, use_mutex_t *mutex) {
    cJSON* TO = cJSON_GetObjectItemCaseSensitive(root, "TO");
    cJSON* MESS = cJSON_GetObjectItemCaseSensitive(root, "MESS");
    cJSON* TYPE = cJSON_GetObjectItemCaseSensitive(root, "TYPE");
    cJSON* BYTES = cJSON_GetObjectItemCaseSensitive(root, "BYTES");

    // write(1, "He send this: ", 14);
    // write(1, MESS->valuestring, strlen(MESS->valuestring)); 
    // write(1, "\n", 1);

    if (cJSON_IsString(TO) && (TO->valuestring != NULL)
        && cJSON_IsString(MESS) && (MESS->valuestring != NULL)
        && strcmp("text", TYPE->valuestring) == 0) {
        if (strcmp(TO->valuestring, "PAPA_BOT") == 0) {
            mx_papa_bot(MESS, mutex);
            return ;
        }
        sockets(TO, MESS, mutex);
    }
    else 
        mx_file_type(root, mutex);
}
