#include "../inc/uchat.h"

int mx_get_id_and_create_chat(int login1, int login2) {
    char *sql;
    int id;
    char *new_name;

    if (login1 < login2)
        asprintf(&new_name, "%d.%d", login1, login2);
    else
        asprintf(&new_name, "%d.%d", login2, login1);
    mx_add_to_table("chats", "chat", new_name);
    asprintf(&sql, "chats where chat = %s", new_name);
    mx_select("chats_id", sql, callback_int, &id);
    free(sql);
    free(new_name);
    return id;
}

void mx_add_users_to_chat(int login, int chats_id) {
    char *sql;

    asprintf(&sql, "%i, %i", login, chats_id);
    mx_add_to_table("users_chat", "users_id, chats_id", sql);
    free(sql);
}

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

void mx_add_message(char *login, int chats_id, char *text, int type_text) {
    char *sql;
    char *time;
    int users_id = -1;

    mx_parse_str(text);
    asprintf(&sql, "persons_id where login = '%s'", login);
    mx_select("users_id", sql, callback_int, &users_id);
    free(sql);
    mx_sqlite("SELECT time('now','localtime');", callback_persons_id, &time);
    asprintf(&sql, "%i, %i, '%s', %i, '%s'", users_id, chats_id, text, type_text, time);
    mx_add_to_table("messeges", "users_id, chats_id, text, type_text, time", sql);
    free(sql);
}

// void mx_add_mess(char *login, char *chats, char *text, int type_text) {
//     char *sql;
//     char *time;
//     int users_id = -1;
//     int chats_id = -1;

//     asprintf(&sql, "persons_id where login = '%s'", login);
//     mx_select("users_id", sql, callback_int, &users_id);
//     free(sql);
//     asprintf(&sql, "chats where chat = '%s'", chats);
//     mx_select("chats_id", sql, callback_int, &chats_id);
//     free(sql);
//     mx_sqlite("SELECT time('now','localtime');", callback_persons_id, &time);
//     asprintf(&sql, "%i, %i, '%s', %i, '%s'", users_id, chats_id, text, type_text, time);
//     mx_add_to_table("messeges", "users_id, chats_id, text, type_text, time", sql);
//     free(sql);
// }