#include "../inc/uchat.h"

void mx_chats_send(use_mutex_t *mutex) {
    int usr_id = mutex->user_id;
    char *buff = NULL;

    write(mutex->cli_fd, buff, strlen(buff));
}
