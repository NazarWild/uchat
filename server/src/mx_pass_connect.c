#include "../inc/uchat.h"

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    t_login_pass *new_data = (t_login_pass *)data;

    new_data->login = strdup(argv[0]);
    new_data->pass= strdup(argv[1]);
    // new_data->socket = argv[2];
    return 0;
}

bool mx_pass_connect(char *login, char *pass) {
    t_login_pass *data = malloc(sizeof(t_login_pass));
    char *str;

    asprintf(&str, "persons_id where login = '%s'", login);
    mx_select("login, pass, socket", str, callback_persons_id, data);
    free(str);
    if (strcmp(login, data->login) == 0 && strcmp(pass, data->pass) == 0)
        return true;
    return false;
}
