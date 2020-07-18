#include "../inc/uchat.h"
int callback_list(void *data, int argc, char **argv, char **ColName) {
    mx_push_front((t_list **)data, strdup(argv[0]));
    return 0;
}

int callback_list_last_users_messeges(void *data, int argc, char **argv, char **ColName) {
    t_sqlite *lite = malloc(sizeof(t_sqlite));
    t_messeges *send = malloc(sizeof(t_messeges));
    t_list *who_is_here = 0;

    lite->data = &who_is_here;
    lite->callback = callback_list;
    send->text = strdup(argv[1]);
    send->who_write = atoi(argv[0]);
    send->chats_id = atoi(argv[2]);
    asprintf(&lite->sql, "select distinct users_id from users_chat where chats_id = %i", send->chats_id);
    mx_sqlite(lite, NULL);
    send->who_is_here = who_is_here;
    mx_push_front((t_list **)data, send);
    free(lite->sql);
    free(lite);
    return 0;
}

t_list *return_last_list(t_list *chats, t_use_mutex *mutex) {
    t_sqlite *lite = malloc(sizeof(t_sqlite));
    t_list *list = 0;
    char *sql = 0;

    for (t_list *new = chats; new != NULL; new = new->next) {
        char *data = new->data;
        asprintf(&sql, "select users_id, text, chats_id from messeges where chats_id = %d "
                " order by text_id desc limit 1;", atoi(data));
        lite->data = &list;
        lite->callback = callback_list_last_users_messeges;
        lite->sql = sql;
        mx_sqlite(lite, mutex);
        free(sql);
    }
    free(lite);
    return list;
}

t_list *mx_list_last_users_messeges(t_use_mutex *mutex) {
    t_sqlite *lite = malloc(sizeof(t_sqlite));
    char *sql;
    t_list *chats = 0;

    asprintf(&sql, "select distinct chats_id from messeges where users_id = %d order by text_id desc;", mutex->user_id);
    lite->data = &chats;
    lite->callback = callback_list;
    lite->sql = sql;
    mx_sqlite(lite, mutex);
    free(sql);
    free(lite);
    return return_last_list(chats, mutex);
}
