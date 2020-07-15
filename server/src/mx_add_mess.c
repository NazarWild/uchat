#include "../inc/uchat.h"

static int callback_persons_id(void *data, int argc, char **argv,
                                                        char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

// int callback_int(void *data, int argc, char **argv, char **ColName) {
//     int *result = (int *)data;
//     *result = atoi(argv[0]);
//     return 0;
// }

// int mx_get_id_and_create_chat(int login1, int login2, use_mutex_t *mutex) {
//     char *sql;
//     int id;
//     char *new_name;

//     if (login1 < login2)
//         asprintf(&new_name, "%d.%d", login1, login2);
//     else
//         asprintf(&new_name, "%d.%d", login2, login1);
//     mx_add_to_table("chats", "chat", new_name, mutex);
//     asprintf(&sql, "chats where chat = %s", new_name);
//     mx_select("chats_id", sql, callback_int, &id, mutex);
//     free(sql);
//     free(new_name);
//     return id;
// }

// void mx_add_users_to_chat(int login, int chats_id, use_mutex_t *mutex) {
//     char *sql;

//     asprintf(&sql, "%i, %i", login, chats_id);
//     mx_add_to_table("users_chat", "users_id, chats_id", sql, mutex);
//     free(sql);
// }

char *mx_parse_str(char *str) {
    int counter = 0;
    int str_len = strlen(str);
    char *newstr = strdup(str);
    int size;
    int i;

    for (i = 0 ; str[i] != '\0'; i++)
        if (str[i] == '\'')
            counter++;
    size = str_len + counter;
    free(newstr);
    newstr = malloc(sizeof(char *) * (size + 1));
    newstr[size] = '\0';
    counter = 0;
    for (i = 0; i < str_len; i++) {
        if (str[i] == '\'')
            newstr[counter++] = '\'';
        newstr[counter++] = str[i];
    }
    return newstr;
}

void mx_add_message(int chats_id, char *text, int type_text,
                                                use_mutex_t *mutex) {
    char *sql;
    char *time;
    t_sqlite *lite = malloc(sizeof(t_sqlite) * 1);

    text = mx_parse_str(text);
    lite->data = &time;
    lite->callback = callback_persons_id;
    lite->sql = "SELECT datetime('now','localtime');";
    mx_sqlite(lite, mutex);
    asprintf(&sql, "%i, %i, '%s', %i, '%s'", mutex->user_id, chats_id, text,
            type_text, time);
    mx_add_to_table("messeges", "users_id, chats_id, text, type_text, time",
                    sql, mutex);
    free(sql);
    free(time);
    free(text);
    free(lite);
}
