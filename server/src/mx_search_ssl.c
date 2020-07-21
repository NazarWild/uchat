#include "../inc/uchat.h"
int callback_int(void *data, int argc, char **argv, char **ColName) {
    int *result = (int *)data;

    *result = atoi(argv[0]);
    return 0;
}

t_list *mx_search_ssl(t_use_mutex *mutex, int id) {
    t_ssl *ssl;
    t_list *list = 0;
    int users_id;
    char *sql = 0;

    asprintf(&sql, "sockets where socket = %i", id);
    mx_select("users_id", sql, callback_int, &users_id, mutex);
    for (t_list *new = (t_list *)mutex->ssl_list; new != 0; new = new->next) {
        ssl = new->data;
        if (ssl->user_id == id)
            mx_push_front(&list, ssl->ssl);
    }
    free(sql);
    return list;
}

void mx_send_user_with_dif_sock(t_use_mutex *mutex, int who, char *str, int bytes) {
    for (t_list *list = mx_search_ssl(mutex, who); list; list = list->next) {
        SSL_write((SSL *)list->data, str, bytes);
    }
}
