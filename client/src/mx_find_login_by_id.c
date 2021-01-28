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

bool mx_if_can_get_mess_by_id(t_mess *mess_id, char *id) {
    t_mess *p = mess_id;

    while(p) {
        if (mx_strcmp(id, p->id) == 0) {
            return p->get_messages;
        }
        p = p->next;
    }
    return true;
}

void mx_set_get_mess_by_id_true(t_mess *mess_id, char *id) {
    t_mess *p = mess_id;

    while(p) {
        if (mx_strcmp(id, p->id) == 0) {
            p->get_messages = true;
            break;
        }
        p = p->next;
    }
}
