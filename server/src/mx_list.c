#include "../inc/uchat.h"

void mx_pop_front(t_list **head) {
    t_list *cur = *head;

    if (cur->next == NULL) {
        free(*head);
        *head = NULL;
    }
    cur = cur->next;
    free(*head);
    *head = cur;
    cur = NULL;
}

t_list *mx_create_node(void *data) {
    t_list *head = NULL;

    head = malloc(sizeof(t_list));
    if (head == NULL)
        return 0;
    head->data = data;
    head->next = NULL;
    return head;
}

void mx_push_front(t_list **list, void *data) {
    t_list *tmp = *list;

    if (*list == 0) {
        *list = mx_create_node(data);
        return;
    }
    *list = mx_create_node(data);
    (*list)->next = tmp;
}

// int callback_list(void *data, int argc, char **argv, char **ColName) {
//     mx_push_front((t_list **)data, (void *)strdup(argv[0])); // сюда надо еще добавлять юзер айди
//     return 0;
// }

void mx_delete_who_online_list(t_list *list) {
    t_list* old;
    t_online *online;

    for (t_list* new = list; new != NULL; new = old) {
        old = new->next;
        online = new->data;
        free(online->login);
        free(online);
        mx_pop_front(&new);
        new = old;
    }
}
