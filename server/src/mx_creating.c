#include "../inc/uchat.h"

static bool same_login(char *login, t_use_mutex *mutex) {
    char *str = NULL;
    char *data = NULL;
    t_select *select;

    asprintf(&str, "persons_id where login = '%s'", login);
    select = mx_struct_select("login", str, mx_callback_persons_id, &data);
    mx_select(select, mutex);
    free(str);
    if (data != NULL && strcmp(login, data) == 0)
        return false;
    return true;
}

void mx_creating(cJSON* root, t_use_mutex *mutex) {      
    cJSON* log = cJSON_GetObjectItemCaseSensitive(root, "LOGIN");
    cJSON* pass = cJSON_GetObjectItemCaseSensitive(root, "PASS");
    char *add_this = NULL;
    char *login = mx_parse_str(log->valuestring);

    asprintf(&add_this, "'%s', '%s', %d, 'standart'", login, pass->valuestring, 0);
    if (same_login(login, mutex) == false) {
        // write(mutex->cli_fd, "-2", 2);
        SSL_write(mutex->my_ssl, "-2", 2);
        free(add_this);
    }
    else {
        mx_add_to_table("persons_id", "login, pass, level, theme", add_this, mutex);
        // write(mutex->cli_fd, "2", 1);
        SSL_write(mutex->my_ssl, "2", 1);
        free(add_this);
    }
    free(login);
}
