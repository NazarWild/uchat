#include "../inc/uchat.h"

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

void mx_add_messege(int users_id, int chats_id, char *text, int type_text) {
    char *sql;
    char *time;

    mx_sqlite("SELECT time('now','localtime');", callback_persons_id, &time);
    asprintf(&sql, "%i, %i, '%s', %i, '%s'", users_id, chats_id, text, type_text, time);
    mx_add_to_table("messeges", "users_id, chats_id, text, type_text, time", sql);
    free(sql);
}
