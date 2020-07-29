#include "../inc/uchat.h"

t_mess *mx_create_node_mess(char *id) {
    t_mess *head = (t_mess *)malloc(sizeof(t_mess));
    if (head == NULL)
        return 0;
    head->id = strdup(id);
    head->get_messages = false;
    head->next = NULL;
    return head;
}

void mx_push_front_mess(t_mess **list, char *id) {
    if(*list == NULL) {
        *list = mx_create_node_mess(id);
        return;
    }
    t_mess *node = *list;

    *list = mx_create_node_mess(id);
    (*list)->next = node;
}
