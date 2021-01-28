#include "../inc/uchat.h"

static char *creating(cJSON* TYPE, cJSON* BYTES, cJSON* MESS, t_widget_my *widge) {
    char *path =  mx_strjoin("./client/file_client/", MESS->valuestring);//пусть отправляет название с точкой в конце
    int stream = open(path, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
    char *buff = (char *)malloc(sizeof(char) * BYTES->valueint);
    //int bytes = 0;

    recv(widge->sockfd, buff, BYTES->valueint, MSG_WAITALL);
    
    write(stream, buff, BYTES->valueint);
    close(stream);
    free(buff);
    return path;
}

void mx_file_receive(cJSON *root, t_widget_my *widge) { 
    cJSON* MESS = cJSON_GetObjectItemCaseSensitive(root, "MESS");
    cJSON* TYPE = cJSON_GetObjectItemCaseSensitive(root, "TYPE");
    cJSON* BYTES = cJSON_GetObjectItemCaseSensitive(root, "BYTES");
    cJSON* CHAT_ID = cJSON_GetObjectItemCaseSensitive(root, "CHAT_ID");
    char *path = NULL;
    char *new_strjoin = NULL;

    path = creating(TYPE, BYTES, MESS, widge);
    //write(1, "File name: ", 11);
    //write(1, path, strlen(path));
    //new_strjoin = mx_strjoin("client/img_chat/file_client/", path);
    if (mx_if_photo_with_type(TYPE->valuestring, widge))
        mx_sendphoto_from(path, widge);
    else
        mx_send_file_from(widge, path);
    free(path);
}
