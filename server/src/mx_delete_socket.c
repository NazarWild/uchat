#include "../inc/uchat.h"

void mx_delete_socket(t_use_mutex *mutex) {
    char *new = NULL;

    asprintf(&new, "socket = %i", mutex->cli_fd);
    mx_delete_from_db("sockets", new, mutex);
    free(new);
}
