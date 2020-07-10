#include "../inc/uchat.h"

static void creating(cJSON* TYPE, cJSON* BYTES, cJSON* MESS, use_mutex_t *mutex) {
    char *path = mx_strjoin("new_file.", TYPE->valuestring); //пусть отправляет название с точкой в конце
    int stream = open(path, O_RDWR | O_CREAT | O_APPEND);
    printf("bytes: %d\n", BYTES->valueint);
    char *buff = (char *)malloc(sizeof(char) * BYTES->valueint);

    while(read(mutex->cli_fd, buff, BYTES->valueint) > 0)
        write(stream, buff, BYTES->valueint);
    close(stream);
    free(path);
    free(buff);
}

void mx_file_type(cJSON *root, use_mutex_t *mutex) { 
    cJSON* TO = cJSON_GetObjectItemCaseSensitive(root, "TO");
    cJSON* MESS = cJSON_GetObjectItemCaseSensitive(root, "MESS");
    cJSON* TYPE = cJSON_GetObjectItemCaseSensitive(root, "TYPE");
    cJSON* BYTES = cJSON_GetObjectItemCaseSensitive(root, "BYTES");

    if (cJSON_IsString(TO) && (TO->valuestring != NULL)
        && cJSON_IsString(MESS) && (MESS->valuestring != NULL)
        && strcmp("text", TYPE->valuestring) != 0) {
        creating(TYPE, BYTES, MESS, mutex);
    }
}

