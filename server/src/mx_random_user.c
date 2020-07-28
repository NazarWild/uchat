#include "../inc/uchat.h"

void mx_random_user(t_use_mutex *mutex) {
    char *str = NULL;
    t_select *select = NULL;
    char *data = 0;
    int a;

    srand ( time(NULL) );
    select = mx_struct_select("max(users_id)", "persons_id", mx_callback_persons_id, &data);
    mx_select(select, mutex);
    a = rand() % atoi(data) + 1;
    free(data);
    free(select);
    asprintf(&str, "persons_id WHERE users_id = %d", a);
    select = mx_struct_select("login", str, mx_callback_persons_id, &data);
    mx_select(select, mutex);
    free(str);
    asprintf(&str, "{\"FROM\":\"PAPA_BOT\",\"MESS\":\"%s\",\n", data);
    SSL_write(mutex->my_ssl, str, strlen(str));
    free(str);
    free(data);
}

