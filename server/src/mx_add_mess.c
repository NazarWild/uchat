#include "../inc/uchat.h"

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

int callback_int(void *data, int argc, char **argv, char **ColName) {
    int *result = (int *)data;
    *result = atoi(argv[0]);
    return 0;
}

void mx_add_message(char *login, char *chats, char *text, int type_text) {
    char *sql;
    char *time;
    int users_id = -1;
    int chats_id = -1;

    asprintf(&sql, "persons_id where login = '%s'", login);
    mx_select("users_id", sql, callback_int, &users_id);
    free(sql);
    asprintf(&sql, "chats where chat = '%s'", chats);
    mx_select("chats_id", sql, callback_int, &chats_id);
    free(sql);
    mx_sqlite("SELECT time('now','localtime');", callback_persons_id, &time);
    asprintf(&sql, "%i, %i, '%s', %i, '%s'", users_id, chats_id, text, type_text, time);
    mx_add_to_table("messeges", "users_id, chats_id, text, type_text, time", sql);
    free(sql);
}
