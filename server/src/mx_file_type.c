#include "../inc/uchat.h"

static char *creating(cJSON* TYPE, cJSON* BYTES, char *mess, t_use_mutex *mutex) {
    char *path =  mx_strjoin("file_serv/", MESS->valuestring);//пусть отправляет название с точкой в конце
    int stream = open(path, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
    char *buff = (char *)malloc(sizeof(char) * BYTES->valueint);

    recv(mutex->cli_fd, buff, BYTES->valueint, MSG_WAITALL);
    write(stream, buff, BYTES->valueint);
    close(stream);
    free(buff);
    return path;
}

static void send_cj(cJSON *root, t_use_mutex *mutex, char *path) {
    char *str = NULL;
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

static char *name_add_file(cJSON* CHAT_ID, cJSON* MESS, t_use_mutex *mutex) {
    char *name = NULL;
    char *data = NULL;

    mx_add_message(atoi(CHAT_ID->valuestring), name, 1, mutex);
    asprintf(&name, "messeges where text = '%s'", MESS->valuestring);
    mx_select("max(text_id)", name, mx_callback_persons_id, data, mutex);
    return data;
}

void mx_file_type(cJSON *root, t_use_mutex *mutex) { 
    cJSON* MESS = cJSON_GetObjectItemCaseSensitive(root, "MESS");
    cJSON* TYPE = cJSON_GetObjectItemCaseSensitive(root, "TYPE");
    cJSON* BYTES = cJSON_GetObjectItemCaseSensitive(root, "BYTES");
    cJSON* CHAT_ID = cJSON_GetObjectItemCaseSensitive(root, "CHAT_ID");
    char *path = NULL;

    if (strcmp("text", TYPE->valuestring) != 0) {
        path = creating(TYPE, BYTES, name_add_file(CHAT_ID, MESS, mutex), mutex);
        send_cj(root, mutex, path);
    }
    free(path);
}

