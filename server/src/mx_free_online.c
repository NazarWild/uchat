#include "../inc/uchat.h"

void mx_free_online(t_list *online_struct) {
    t_online *struco = NULL;
    t_list *tmp = online_struct;

    while (tmp != NULL) {
        struco = (t_online*) tmp->data;
        free(struco->login);
        free(online_struct->data);
        tmp = online_struct->next;
        free(online_struct);
        online_struct = tmp;
    }
}

