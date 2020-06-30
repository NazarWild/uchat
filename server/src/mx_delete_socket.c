#include "../inc/uchat.h"

void mx_delete_socket(int fd) {
    char *new = NULL;

    asprintf(&new, "socket = %s", mx_itoa(fd));
    mx_delete_from_db("sockets", new);
    free(new);
}
