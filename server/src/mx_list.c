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

int callback_list_online(void *data, int argc, char **argv, char **ColName) {
    t_online *online = malloc(sizeof(t_online));

    online->login = strdup(argv[0]);
    online->id = atoi(argv[1]);
    online->online = 1;
    mx_push_front((t_list **)data, online);
    return 0;
}

int callback_list_not_online(void *data, int argc, char **argv, char **ColName) {
    t_online *online = malloc(sizeof(t_online));

    online->login = strdup(argv[0]);
    online->id = atoi(argv[1]);
    online->online = 0;
    mx_push_front((t_list **)data, online);
    return 0;
}

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

t_list *mx_where_not_1(use_mutex_t *mutex) {
    t_list *list = NULL;
    t_sqlite *lite = malloc(sizeof(t_sqlite));

    lite->data = &list;
    lite->callback = callback_list_online;
    lite->sql = "SELECT DISTINCT persons_id.login, sockets.users_id "
                "from persons_id INNER JOIN sockets on "
                "persons_id.users_id = sockets.users_id";
    mx_sqlite(lite, mutex);
    lite->callback = callback_list_not_online;
    lite->sql = "SELECT login, users_id FROM persons_id WHERE users_id NOT IN "
                "(SELECT users_id FROM sockets);";
    mx_sqlite(lite, mutex);
    free(lite);
    return list;
}