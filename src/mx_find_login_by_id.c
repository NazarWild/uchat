#include "../inc/uchat.h"

char *mx_find_login_by_id(t_list *login_id, char *id) {
    t_list *p = login_id;
    t_login *log = p->data;

    while(p) {
        if (mx_strcmp(id, log->id) == 0) {
            return log->login;
        }
        p = p->next;
        log = p->data;
    }
    printf("NULL\n");
    return NULL;
}

char *mx_find_id_by_login(t_list *login_id, char *login) {
    t_list *p = login_id;
    t_login *log = p->data;

    while(p) {
        if (mx_strcmp(login, log->login) == 0)
            return log->id;
        p = p->next;
        log = p->data;
    }
    return NULL;
}
