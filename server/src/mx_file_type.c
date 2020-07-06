#include "../inc/uchat.h"

static void creating(cJSON* TYPE, cJSON* BYTES, cJSON* MESS) {
    char *path = mx_strjoin("file.", TYPE->valuestring);
    int stream = open(path, O_RDWR | O_CREAT);

    printf("BYTES: %d", BYTES->valueint);
    write(stream, MESS->valuestring, BYTES->valueint);
    write(1, MESS->valuestring, BYTES->valueint);
    close(stream);
}

void mx_file_type(cJSON *root, use_mutex_t *mutex) {
    cJSON* FROM = cJSON_GetObjectItemCaseSensitive(root, "FROM");
    cJSON* TO = cJSON_GetObjectItemCaseSensitive(root, "TO");
    cJSON* MESS = cJSON_GetObjectItemCaseSensitive(root, "MESS");
    cJSON* TYPE = cJSON_GetObjectItemCaseSensitive(root, "TYPE");
    cJSON* BYTES = cJSON_GetObjectItemCaseSensitive(root, "BYTES");

    if (cJSON_IsString(FROM) && (FROM->valuestring != NULL) 
        && cJSON_IsString(TO) && (TO->valuestring != NULL)
        && cJSON_IsString(MESS) && (MESS->valuestring != NULL)
        && strcmp("text", TYPE->valuestring) != 0) {
        creating(TYPE, BYTES, MESS);
    }
}

