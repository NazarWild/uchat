#include "../inc/sqlite.h"

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

t_list *mx_create_node(void *data, int users_id) {
    t_list *head = NULL;

    head = malloc(sizeof(t_list));
    if (head == NULL)
        return 0;
    head->data = data;
    head->users_id = users_id;
    head->next = NULL;
    return head;
}

void mx_push_front(t_list **list, void *data, int users_id) {
    t_list *tmp = *list;

    if (*list == 0) {
        *list = mx_create_node(data, users_id);
        return;
    }
    *list = mx_create_node(data, users_id);
    (*list)->next = tmp;
}


int callback_list(void *data, int argc, char **argv, char **ColName) {
    //mx_push_front((t_list **)data, (void *)strdup(argv[0]), ); // сюда надо еще добавлять юзер айди
    return 0;
}

t_list *mx_where_not_1() {
    t_list *list = 0; 

    mx_select("users_id", "sockets where socket > -1", callback_list, &list);

    // for (t_list *new = list; new != NULL; new = new->next)
    //     printf("%s\n", (char *)new->data);
    // for (t_list *new = list; new != NULL; new = new->next) {
    //     t_list *old = new;
    //     free((char *)new->data);
    //     mx_pop_front(&new);
    //     new = old;
    // }
    // for (t_list *new = list; new != NULL; new = new->next)
    //     printf("%s\n", (char *)new->data);
    //list = NULL;
    return list;
}