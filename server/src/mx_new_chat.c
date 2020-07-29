#include "../inc/uchat.h"

int mx_callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

// static void send_mess(int to, char *mess, int chat_id, t_use_mutex *mutex) {
//     char *new = NULL;
//     char *type = NULL;

//     if (stickers == 1)
//         type = strdup("sticker");
//     else 
//         type = strdup("text");
//     asprintf(&new, "{\"IF_MESS\":true,\"FROM\":%d,\"MESS\":\"%s\",\"CHAT_ID\":%d,\"TYPE\":\"%s\"}\n", mutex->user_id, mess, chat_id, type);
//     mx_send_user_with_dif_sock(mutex, to, new, strlen(new));
//     free(new);
//     free(type);
// }

char *mx_new_chat(cJSON* TO, cJSON* MESS, char *data, t_use_mutex *mutex) {
    char *str1 = NULL;
    char *str2 = NULL;
    char *tmp = NULL;
    char *ita = mx_itoa(mutex->user_id);
    t_select *select;

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
    free(ita);
    return str2;
}

