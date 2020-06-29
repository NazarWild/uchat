#include "../inc/uchat.h" 

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

void mx_send_mess(cJSON *root, int fd) {
    cJSON* FROM = cJSON_GetObjectItemCaseSensitive(root, "FROM");
    cJSON* TO = cJSON_GetObjectItemCaseSensitive(root, "TO");
    cJSON* MESS = cJSON_GetObjectItemCaseSensitive(root, "MESS");

    write(1, "HE thend this: ", 16);
    write(1, MESS->valuestring, strlen(MESS->valuestring));



    char *str = NULL;
    char *data = NULL; 

    if (cJSON_IsString(FROM) && (FROM->valuestring != NULL) 
        && cJSON_IsString(TO) && (TO->valuestring != NULL)
        && cJSON_IsString(MESS) && (MESS->valuestring != NULL)) {
        if (strcmp(TO->valuestring, "PAPA_BOT") == 0) {
            mx_papa_bot(FROM, MESS, fd);
            return ;
        }
        asprintf(&str, "persons_id where login = '%s'", TO->valuestring);
        mx_select("socket", str, callback_persons_id, &data);
        free(str);
        if (data == NULL) {
            //adding mess, to database 
            //mx_add_mess(FROM->valuestring, , MESS->valuestring, 1);
            
            return ;
        }
        write(atoi(data), MESS->valuestring, strlen(MESS->valuestring));
        //adding mess to database
        //mx_add_mess(FROM->valuestring, , MESS->valuestring, 1);
    }
    free(data);
}
