#include "../inc/uchat.h"

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

bool mx_pass_connect(char *login, char *pass) {
    char *str = NULL;
    char *data = NULL;

    asprintf(&str, "persons_id where login = '%s'", login);
    mx_select("pass", str, callback_persons_id, &data);
    free(str);
    if (data == NULL)
        return false;
    if (strcmp(pass, data) == 0)
        return true;
    write(1, "NOT LOGGED", 11);
    return false;
}
