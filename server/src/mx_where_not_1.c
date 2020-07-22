#include "../inc/uchat.h"

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

t_list *mx_where_not_1(t_use_mutex *mutex) {
    t_list *list = NULL;
    t_sqlite *lite = malloc(sizeof(t_sqlite));

    lite->data = &list;
    lite->callback = callback_list_online;
    lite->sql = "SELECT DISTINCT persons_id.login, sockets.users_id "
                "from persons_id INNER JOIN sockets on "
                "persons_id.users_id = sockets.users_id;";
    mx_sqlite(lite, mutex);
    lite->callback = callback_list_not_online;
    lite->sql = "SELECT login, users_id FROM persons_id WHERE users_id NOT IN "
                "(SELECT users_id FROM sockets);";
    mx_sqlite(lite, mutex);
    free(lite);
    return list;
}