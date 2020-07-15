#include "../inc/uchat.h"

void mx_delete_socket(use_mutex_t *mutex) {
    char *new = NULL;
    char *ita = mx_itoa(mutex->cli_fd);

    asprintf(&new, "socket = %s", ita);
    mx_delete_from_db("sockets", new, mutex);
    free(new);
    free(ita);
}
