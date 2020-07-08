#include "../inc/uchat.h" 

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

static void sockets(cJSON* TO, cJSON* FROM, cJSON* MESS, use_mutex_t *mutex) {
    char *str1 = NULL;
    char *data = NULL;
    char *data2 = NULL;

    asprintf(&str1, "sockets where users_id = %d", 2);
    mx_select("socket", str1, callback_persons_id, &data, mutex);
    free(str1);
    // надо найти у двух юзеров общий чат, если его нет, то создать чат и внести кто туда относится!
    // asprintf(&str1, "users_chat where users_id = %s AND users_id = %s", TO->valuestring, FROM->valuestring);
    // mx_select("chats_id", str1, callback_persons_id, &data, mutex);
    if (data != NULL)
        write(atoi(data), MESS->valuestring, strlen(MESS->valuestring));
    
    //mx_add_message(FROM->valuestring, NULL, MESS->valuestring, 0, mutex);
}

void mx_send_mess(cJSON *root, use_mutex_t *mutex) {
    cJSON* FROM = cJSON_GetObjectItemCaseSensitive(root, "FROM");
    cJSON* TO = cJSON_GetObjectItemCaseSensitive(root, "TO");
    cJSON* MESS = cJSON_GetObjectItemCaseSensitive(root, "MESS");
    cJSON* TYPE = cJSON_GetObjectItemCaseSensitive(root, "TYPE");
    cJSON* BYTES = cJSON_GetObjectItemCaseSensitive(root, "BYTES");

    write(1, "He send this: ", 14);
    char *path = mx_strjoin("/Users/ndykyy/Desktop/new_file.", TYPE->valuestring);
    int stream = open(path, O_RDWR | O_CREAT);
    write(stream, MESS->valuestring, BYTES->valueint);
    close(stream);
    write(1, MESS->valuestring, BYTES->valueint); 
    write(1, "\n", 1);

    if (cJSON_IsString(FROM) && (FROM->valuestring != NULL) 
        && cJSON_IsString(TO) && (TO->valuestring != NULL)
        && cJSON_IsString(MESS) && (MESS->valuestring != NULL)
        && strcmp("text", TYPE->valuestring) == 0) {
        if (strcmp(TO->valuestring, "PAPA_BOT") == 0) {
            mx_papa_bot(FROM, MESS, mutex);
            return ;
        }
        sockets(TO, FROM, MESS,mutex);
    }
    else 
        mx_file_type(root, mutex);
}
