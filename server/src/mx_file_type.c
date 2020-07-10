#include "../inc/uchat.h"

static void creating(cJSON* TYPE, cJSON* BYTES, cJSON* MESS, use_mutex_t *mutex) {
    char *new_file = mx_strjoin("new_file.", TYPE->valuestring);
    char *path = mx_strjoin(MESS->valuestring, new_file); //пусть отправляет название с точкой в конце
    int stream = open(path, O_RDWR | O_CREAT);
    char buff[BYTES->valueint];

    read(mutex->cli_fd, buff, BYTES->valueint);
    write(stream, buff, BYTES->valueint);
    //write(1, buff, BYTES->valueint);
    write(1, path, strlen(path));
    close(stream);
    //free(&path);
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

