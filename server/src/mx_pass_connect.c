#include "../inc/uchat.h"

static int callback_persons_id(void *data, int argc, char **argv,
                                                        char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

bool mx_pass_connect(char *login, char *pass, t_use_mutex *mutex) {
    char *str = NULL;
    char *data = NULL;
    char *log = mx_parse_str(login);

    asprintf(&str, "persons_id where login = '%s'", log);
    mx_select("pass", str, callback_persons_id, &data, mutex);
    free(str);
    free(log);
    if (data == NULL)
        return false;
    if (strcmp(pass, data) == 0)
        return true;
    printf("pass - %s data - %s\n\n\n\n", pass, data);
    write(1, "NOT LOGGED", 11);
    return false;
}
