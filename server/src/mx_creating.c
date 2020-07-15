#include "../inc/uchat.h"

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

static bool same_login(char *login, use_mutex_t *mutex) {
    char *str = NULL;
    char *data = NULL;

    asprintf(&str, "persons_id where login = '%s'", login);
    mx_select("login", str, callback_persons_id, &data, mutex);
    free(str);
    if (data != NULL && strcmp(login, data) == 0)
        return false;
    return true;
}

void mx_creating(cJSON* root, use_mutex_t *mutex) {      
    cJSON* log = cJSON_GetObjectItemCaseSensitive(root, "LOGIN");
    cJSON* pass = cJSON_GetObjectItemCaseSensitive(root, "PASS");
    char *add_this = NULL;
    char *login = mx_parse_str(log->valuestring);

    asprintf(&add_this, "'%s', '%s', %d", login, pass->valuestring, 0);
    if (same_login(login, mutex) == false) {
        write(mutex->cli_fd, "-2", 2);
        free(add_this);
    }
    else {
        mx_add_to_table("persons_id", "login, pass, level", add_this, mutex);
        write(mutex->cli_fd, "2", 1);
        free(add_this);
    }
    free(login);
}
