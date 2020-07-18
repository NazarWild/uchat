#include "../inc/uchat.h"

static void creating(cJSON* TYPE, cJSON* BYTES, cJSON* MESS, t_use_mutex *mutex) {
    char *path = mx_strjoin("new_file.", TYPE->valuestring); //пусть отправляет название с точкой в конце
    int stream = open(path, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
    printf("bytes: %d\n", BYTES->valueint);
    char *buff = (char *)malloc(sizeof(char) * BYTES->valueint);
    // int a;

    // while (a += read(mutex->cli_fd, buff, BYTES->valueint)) {
    //     write(stream, buff, BYTES->valueint);
    //     if (a >= BYTES->valueint)
    //         break;
    // }
    recv(mutex->cli_fd, buff, BYTES->valueint, MSG_WAITALL);
    write(stream, buff, BYTES->valueint);
    
    write(1, "FILE DONE", 9);
    close(stream);
    free(path);
    free(buff);
}

void mx_file_type(cJSON *root, t_use_mutex *mutex) { 
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

