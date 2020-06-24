#include "../inc/uchat.h" 

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {

    data = strdup(argv[0]);

    return 0;
}

void adding_to_db(cJSON* FROM, cJSON* TO, cJSON* MESS) {
    //mx_add_to_table();// adding to db messeges
}

void mx_send_mess(cJSON *root, int fd) {
    cJSON* FROM = cJSON_GetObjectItemCaseSensitive(root, "FROM");
    cJSON* TO = cJSON_GetObjectItemCaseSensitive(root, "TO");
    cJSON* MESS = cJSON_GetObjectItemCaseSensitive(root, "MESS");
    char *str = NULL;
    char *data = NULL;

    if (cJSON_IsString(FROM) && (FROM->valuestring != NULL) 
        && cJSON_IsString(TO) && (TO->valuestring != NULL)
        && cJSON_IsString(MESS) && (MESS->valuestring != NULL)) {
        asprintf(&str, "persons_id where login = '%s'", TO->valuestring);
        mx_select("socket", str, callback_persons_id, &data);
        free(str);
        if (data == NULL) {
            //adding mess, to database 
            
            return ;
        }
        write(atoi(data), MESS->valuestring, strlen(MESS->valuestring));
        //adding mess to database
    }
    free(data);
}
