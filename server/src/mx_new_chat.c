#include "../inc/uchat.h"

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

void mx_new_chat(cJSON* TO, cJSON* MESS, cJSON* CHAT_ID, use_mutex_t *mutex) {
    char *str1 = NULL;
    char *str2 = NULL;
    char *tmp = NULL;
    char *ita = mx_itoa(mutex->user_id);

    if (atoi(TO->valuestring) < mutex->user_id)
        asprintf(&str1, "'%s %s'", TO->valuestring, ita);
    else
        asprintf(&str1, "'%s %s'", ita, TO->valuestring);
    mx_add_to_table("chats", "chat", str1, mutex);
    write(1, "PROBLEM !\n", 10);
    asprintf(&tmp, "chats WHERE chat = %s", str1);
    mx_select("chats_id", tmp, callback_persons_id, &str2, mutex);
    write(1, "PROBLEM 1\n", 10);
    free(tmp);
    asprintf(&str1, "%d, %d", atoi(TO->valuestring), atoi(str2));
    mx_add_to_table("users_chat", "users_id, chats_id", str1, mutex);
    write(1, "PROBLEM 2\n", 10);
    free(str1);
    free(ita);
}
