#include "../inc/uchat.h"

void mx_delete_socket(t_use_mutex *mutex) {
    char *new = NULL;
    char *ita = mx_itoa(mutex->cli_fd);

    asprintf(&new, "socket = %s", ita);
    mx_delete_from_db("sockets", new, mutex);
    free(new);
    free(ita);
}
