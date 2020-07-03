#include "../inc/uchat.h" 

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

static char *sockets(cJSON* TO, cJSON* FROM, use_mutex_t *mutex) {
    char *str1 = NULL;
    char *str2 = NULL;
    char *data1 = NULL;
    char *data2 = NULL;

    asprintf(&str1, "persons_id where login = '%s'", TO->valuestring);
    mx_select("users_id", str1, callback_persons_id, &data1, mutex);
    asprintf(&str2, "persons_id where login = '%s'", FROM->valuestring);
    mx_select("users_id", str2, callback_persons_id, &data2, mutex);
    free(str1);
    free(str2);
    return data1;
}

void mx_send_mess(cJSON *root, int fd, use_mutex_t *mutex) {
    cJSON* FROM = cJSON_GetObjectItemCaseSensitive(root, "FROM");
    cJSON* TO = cJSON_GetObjectItemCaseSensitive(root, "TO");
    cJSON* MESS = cJSON_GetObjectItemCaseSensitive(root, "MESS");

    write(1, "He send this: ", 16);
    write(1, MESS->valuestring, strlen(MESS->valuestring)); 

    if (cJSON_IsString(FROM) && (FROM->valuestring != NULL) 
        && cJSON_IsString(TO) && (TO->valuestring != NULL)
        && cJSON_IsString(MESS) && (MESS->valuestring != NULL)) {
        if (strcmp(TO->valuestring, "PAPA_BOT") == 0) {
            mx_papa_bot(FROM, MESS, fd);
            return ;
        }
        sockets(TO, FROM, mutex);
    //     if (data == NULL) {
    //         //adding mess, to database 
    //         //mx_add_mess(FROM->valuestring, ,MESS->valuestring, 1);
            
    //         return ;
    //     }
    //     write(atoi(data), MESS->valuestring, strlen(MESS->valuestring));
    //     //adding mess to database
    //     //mx_add_mess(FROM->valuestring, , MESS->valuestring, 1);
    // }
    // free(data);
        }
}
