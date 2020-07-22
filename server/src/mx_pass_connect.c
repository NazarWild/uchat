#include "../inc/uchat.h"

bool mx_pass_connect(char *login, char *pass, t_use_mutex *mutex) {
    char *str = NULL;
    char *data = NULL;
    char *log = mx_parse_str(login);
    t_select *select;

    asprintf(&str, "persons_id where login = '%s'", log);
    select = mx_struct_select("pass", str, mx_callback_persons_id, &data);
    mx_select(select, mutex);
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
