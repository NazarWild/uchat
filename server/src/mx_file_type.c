#include "../inc/uchat.h"

static char *creating(cJSON* TYPE, cJSON* BYTES, cJSON* MESS, t_use_mutex *mutex) {
    char *tmp = mx_strjoin(MESS->valuestring, TYPE->valuestring);
    char *path =  mx_strjoin("file_serv/", tmp);//пусть отправляет название с точкой в конце
    int stream = open(path, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
    char *buff = (char *)malloc(sizeof(char) * BYTES->valueint);

    recv(mutex->cli_fd, buff, BYTES->valueint, MSG_WAITALL);
    write(stream, buff, BYTES->valueint);
    close(stream);
    free(buff);
    free(tmp);
    return path;
}

static void send_cj(cJSON *root, t_use_mutex *mutex, char *name) {
    char *str = NULL;
    char *path = mx_strjoin("file_serv/", name);
    int fd = open(path, O_RDWR);
    cJSON* CHAT_ID = cJSON_GetObjectItemCaseSensitive(root, "CHAT_ID");
    cJSON* TO = cJSON_GetObjectItemCaseSensitive(root, "TO");
    cJSON* BYTES = cJSON_GetObjectItemCaseSensitive(root, "BYTES");

    asprintf(&str, "{\"FROM\":%d,\"MESS\":%s,\"TYPE\":%s,\"CHAT_ID\":%s}\n", mutex->user_id, path, "file",CHAT_ID->valuestring);
    write(atoi(TO->valuestring), str, strlen(str));
    free(str);
    str = (char *) malloc(sizeof(char) * BYTES->valueint);
    read(fd, str, BYTES->valueint);
    write(atoi(TO->valuestring), str, BYTES->valueint);
    free(str);
}

void mx_file_type(cJSON *root, t_use_mutex *mutex) { 
    cJSON* MESS = cJSON_GetObjectItemCaseSensitive(root, "MESS");
    cJSON* TYPE = cJSON_GetObjectItemCaseSensitive(root, "TYPE");
    cJSON* BYTES = cJSON_GetObjectItemCaseSensitive(root, "BYTES");
    cJSON* CHAT_ID = cJSON_GetObjectItemCaseSensitive(root, "CHAT_ID");
    char *path = NULL;

    if (strcmp("file", TYPE->valuestring) == 0) {
        path = creating(TYPE, BYTES, MESS, mutex);
        //mx_add_message(atoi(CHAT_ID->valuestring), path, 1, mutex);
        send_cj(root, mutex, path);
    }
    free(path);
}

