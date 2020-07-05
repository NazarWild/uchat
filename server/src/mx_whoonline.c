#include "../inc/uchat.h"

static void send_online(cJSON *ON, int fd) {
    char *string = cJSON_Print(ON);

    write(1, string, strlen(string));
    exit(0);
    write(fd, string, strlen(string));
    free(string);
}

static int count_of_struct(t_list *online) {
    int counter = 0;
    t_list *list = online;

    while(list) {
        counter++;
        list = list->next;
    }
    return counter;
}

static void adding_sys(cJSON *root) {
    cJSON *is_online = NULL;

    is_online = cJSON_CreateTrue();

    cJSON_AddItemToObject(root,"USERS", is_online);
}

static void adding_param(cJSON *online, t_online *arr_users) {
    cJSON *user_id = NULL;
    cJSON *online_bool = NULL;

    user_id = cJSON_CreateString( arr_users->id);
    cJSON_AddItemToObject(online, "user_id", user_id);
    if (arr_users->online == true) 
        online_bool = cJSON_CreateTrue();
    else 
        online_bool = cJSON_CreateFalse();
    cJSON_AddItemToObject(online, "online", online_bool);
}

void mx_whoonline(use_mutex_t *mutex) {
    t_list *online_struct = mx_where_not_1(mutex);
    cJSON *on = cJSON_CreateObject();
    cJSON *users = cJSON_CreateArray();
    cJSON *online = NULL;
    cJSON *str = NULL;

    t_online *struco = NULL;

    int count_of = count_of_struct(online_struct);
    adding_sys(on);

    cJSON_AddItemToObject(on, "user", users);
    for (int i = 0; i < count_of; i++) {
        struco = (t_online*) online_struct->data;
        online = cJSON_CreateObject();
        cJSON_AddItemToArray(users, online);
        str = cJSON_CreateString( struco->login);
        cJSON_AddItemToObject(online, "login", str);
        
        online_struct = online_struct->next;
    }
    send_online(on, mutex->cli_fd);
    cJSON_Delete(on);
}
