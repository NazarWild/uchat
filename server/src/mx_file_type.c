#include "../inc/uchat.h"

static char *creating(cJSON* TYPE, cJSON* BYTES, char *mess, t_use_mutex *mutex) {
    char *path =  mx_strjoin("file_serv/", mess);//пусть отправляет название с точкой в конце
    int stream = open(path, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
    char *buff = (char *)malloc(sizeof(char) * BYTES->valueint);
    //int bytes = 0;

    write(1, "File name: ", 11);
    write(1, path, strlen(path));
    recv(mutex->cli_fd, buff, BYTES->valueint, MSG_WAITALL);

    //new added ---------------------------
    // while (bytes += SSL_read(mutex->my_ssl, buff, BYTES->valueint) < BYTES->valueint) {
    //     write(stream, buff, BYTES->valueint);
    // }
    //maybe del ---------------------------
    
    write(stream, buff, BYTES->valueint);
    close(stream);
    free(buff);
    return path;
}

static int on_wich_socket(int to, t_use_mutex *mutex) {
    char *str = NULL;
    char *data = NULL;
    t_select *select;
    int a;

    asprintf(&str, "sockets where users_id = %d", to);
    select = mx_struct_select("socket", str, mx_callback_persons_id, &data);
    mx_select(select, mutex);
    free(str);
    if (data == NULL)
        return -1;
    a = atoi(data);
    return a;
}

static void send_cj(cJSON *root, t_use_mutex *mutex, char *path) {
    char *str = NULL;
    int fd = open(path, O_RDWR);
    cJSON* CHAT_ID = cJSON_GetObjectItemCaseSensitive(root, "CHAT_ID");
    cJSON* TO = cJSON_GetObjectItemCaseSensitive(root, "TO");
    cJSON* BYTES = cJSON_GetObjectItemCaseSensitive(root, "BYTES");
    cJSON* MESS = cJSON_GetObjectItemCaseSensitive(root, "MESS");
    cJSON* TYPE = cJSON_GetObjectItemCaseSensitive(root, "TYPE");
    int sock;

    if ((sock = on_wich_socket(atoi(TO->valuestring), mutex)) == -1)
        return ;
    asprintf(&str, "{\"FROM\":%d,\"MESS\":%s,\"TYPE\":%s,\"CHAT_ID\":%s}\n", mutex->user_id, MESS->valuestring, TYPE->valuestring, CHAT_ID->valuestring);
    mx_send_user_with_dif_sock(mutex, atoi(TO->valuestring), str, strlen(str));
    free(str);
    str = (char *) malloc(sizeof(char) * BYTES->valueint);
    read(fd, str, BYTES->valueint);
    write(sock, str, BYTES->valueint);
    free(str);
}

static char *name_add_file(cJSON* CHAT_ID, cJSON* MESS, cJSON* TYPE, t_use_mutex *mutex) {
    char *name = NULL;
    char *data = NULL;
    t_select *select;

    mx_add_message(atoi(CHAT_ID->valuestring), MESS->valuestring, 1, mutex);
    asprintf(&name, "messeges where text = '%s' and chats_id = %d", MESS->valuestring, atoi(CHAT_ID->valuestring));
    select = mx_struct_select("max(text_id)", name, mx_callback_persons_id, &data);
    mx_select(select, mutex);
    free(name);
    name = mx_strjoin(data, TYPE->valuestring);
    free(data);
    return name;
}

void mx_file_type(cJSON *root, t_use_mutex *mutex) { 
    cJSON* MESS = cJSON_GetObjectItemCaseSensitive(root, "MESS");
    cJSON* TYPE = cJSON_GetObjectItemCaseSensitive(root, "TYPE");
    cJSON* BYTES = cJSON_GetObjectItemCaseSensitive(root, "BYTES");
    cJSON* CHAT_ID = cJSON_GetObjectItemCaseSensitive(root, "CHAT_ID");
    char *path = NULL;

    if (strcmp("text", TYPE->valuestring) != 0) {
        path = creating(TYPE, BYTES, name_add_file(CHAT_ID, MESS, TYPE, mutex), mutex);
        send_cj(root, mutex, path);
    }
    free(path);
}

