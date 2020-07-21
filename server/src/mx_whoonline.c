#include "../inc/uchat.h"

static void send_online(cJSON *ON, t_use_mutex *mutex) {
    char *string = cJSON_Print(ON);

    // write(fd, string, 2048); //nd
    SSL_write(mutex->my_ssl, string, 2048);
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

    user_id = cJSON_CreateString( mx_itoa(arr_users->id));
    cJSON_AddItemToObject(online, "user_id", user_id);
    if (arr_users->online == 1) 
        online_bool = cJSON_CreateTrue();
    else 
        online_bool = cJSON_CreateFalse();
    cJSON_AddItemToObject(online, "online", online_bool);
}

void mx_whoonline(t_use_mutex *mutex) {
    t_list *tmp = mx_where_not_1(mutex);
    t_list *online_struct = tmp;
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
        adding_param(online, struco);
        online_struct = online_struct->next;
    }
    send_online(on, mutex);
    mx_free_online(tmp);
    cJSON_Delete(on);
}
