#include "../inc/uchat.h"

// int mx_callback_persons_id(void *data, int argc, char **argv, char **ColName) {
//     if (argc < 1)
//         return 0;
//     char **new = (char **)data;

//     *new = strdup(argv[0]);
//     return 0;
// }

// void mx_new_chat(cJSON* TO, cJSON* MESS, cJSON* CHAT_ID, t_use_mutex *mutex) {
//     char *str1 = NULL;
//     char *str2 = NULL;
//     char *tmp = NULL;
//     char *ita = mx_itoa(mutex->user_id); 
//     t_select *select;

//     if (atoi(TO->valuestring) < mutex->user_id)
//         asprintf(&str1, "'%s %s'", TO->valuestring, ita);
//     else
//         asprintf(&str1, "'%s %s'", ita, TO->valuestring);
//     mx_add_to_table("chats", "chat", str1, mutex);
//     asprintf(&tmp, "chats WHERE chat = %s", str1);
//     select = mx_struct_select("chats_id", tmp, mx_callback_persons_id, &str2);
//     mx_select(select, mutex);
//     free(tmp);
//     free(str1);
//     asprintf(&str1, "%d, %d", atoi(TO->valuestring), atoi(str2));
//     mx_add_to_table("users_chat", "users_id, chats_id", str1, mutex);
//     free(str1);
//     if (atoi(TO->valuestring) != mutex->user_id) {
//         asprintf(&str1, "%d, %d", mutex->user_id, atoi(str2));
//         mx_add_to_table("users_chat", "users_id, chats_id", str1, mutex);
//         free(str1);
//     }
//     mx_add_message(atoi(str2), MESS->valuestring, 0, mutex);
//     free(str2);
//     free(ita);
// }

int mx_callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

static bool check_if_chat_is(cJSON* TO, t_use_mutex *mutex, char *ita, cJSON* MESS) {
    char *str1 = 0;
    char *str2 = 0;
    char *str3 = 0;
    t_sqlite *lite = malloc(sizeof(t_sqlite));

    if (atoi(TO->valuestring) < mutex->user_id)
        asprintf(&str1, "'%s %s'", TO->valuestring, ita);
    else
        asprintf(&str1, "'%s %s'", ita, TO->valuestring);
    asprintf(&lite->sql, "select chats_id from chats where chat = %s", str1);
    lite->callback = mx_callback_persons_id;
    lite->data = &str2;
    mx_sqlite(lite, mutex);
    free(lite->sql);
    free(lite);
    free(str1);
    if (str2 == NULL)
        return true;
    mx_add_message(atoi(str2), MESS->valuestring, 0, mutex);
    free(str2);
    return false;
}

void mx_new_chat(cJSON* TO, cJSON* MESS, cJSON* CHAT_ID, t_use_mutex *mutex) {
    char *str1 = NULL;
    char *str2 = NULL;
    char *tmp = NULL;
    char *ita = mx_itoa(mutex->user_id);
    t_select *select;

    if(check_if_chat_is(TO, mutex, ita, MESS) == false)
        return;
    if (atoi(TO->valuestring) < mutex->user_id)
        asprintf(&str1, "'%s %s'", TO->valuestring, ita);
    else
        asprintf(&str1, "'%s %s'", ita, TO->valuestring);
    mx_add_to_table("chats", "chat", str1, mutex);
    asprintf(&tmp, "chats WHERE chat = %s", str1);
    select = mx_struct_select("chats_id", tmp, mx_callback_persons_id, &str2);
    mx_select(select, mutex);
    free(tmp);
    free(str1);
    asprintf(&str1, "%d, %d", atoi(TO->valuestring), atoi(str2));
    mx_add_to_table("users_chat", "users_id, chats_id", str1, mutex);
    free(str1);
    if (atoi(TO->valuestring) != mutex->user_id) {
        asprintf(&str1, "%d, %d", mutex->user_id, atoi(str2));
        mx_add_to_table("users_chat", "users_id, chats_id", str1, mutex);
        free(str1);
    }
    mx_add_message(atoi(str2), MESS->valuestring, 0, mutex);
    free(str2);
    free(ita);
}
