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

int callback_list(void *data, int argc, char **argv, char **ColName) {
    t_online *online = malloc(sizeof(t_online));
    online->login = strdup(argv[0]);
    online->id = atoi(argv[1]);
    online->online = atoi(argv[2]);

    mx_push_front((t_list **)data, online);
    return 0;
}

t_list *mx_where_not_1(use_mutex_t *mutex) {
    t_list *list = 0;
    // t_online *online = malloc(sizeof(t_online));
    t_sqlite *lite = malloc(sizeof(t_sqlite));

    lite->data = &list;
    lite->callback = callback_list;
    lite->sql = "SELECT DISTINCT persons_id.login, sockets.users_id, "
                "sockets.online from persons_id INNER JOIN sockets on "
                "persons_id.users_id = sockets.users_id";
    mx_sqlite(lite, NULL);
    free(lite);
    return list;
}