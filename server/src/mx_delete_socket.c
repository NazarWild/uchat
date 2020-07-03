#include "../inc/uchat.h"

void mx_delete_socket(int fd, use_mutex_t *mutex) {
    char *new = NULL;

    asprintf(&new, "socket = %s", mx_itoa(fd));
    mx_delete_from_db("sockets", new, mutex);
    free(new);
}
