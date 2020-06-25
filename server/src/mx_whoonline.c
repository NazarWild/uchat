#include "../inc/uchat.h"

static void send_online(cJSON *ON, int fd) {
    char *string = cJSON_Print(ON);

    write(fd, string, strlen(string));
    free(string);
}

static int count_of_struct(t_list *online) {
    int counter = 0;

    while(online) {
        counter++;
        online = online->next;
    }
    return counter;
}

void mx_whoonline(int fd) {
    t_list *online_struct = mx_where_not_1();
    cJSON *on = cJSON_CreateObject();
    cJSON *who_online = cJSON_CreateArray();
    cJSON *online = NULL;
    cJSON *str = NULL;

    cJSON_AddItemToObject(on, "who_online", who_online);
    for (int i = 0; i < count_of_struct(online_struct); i++) {
        online = cJSON_CreateObject();
        str = cJSON_CreateString((char *) online_struct->data);
        cJSON_AddItemToObject(online, "online", str);
        cJSON_AddItemToArray(who_online, online);
        online_struct = online_struct->next;
    }
    send_online(on, fd);
    cJSON_Delete(on);
}
