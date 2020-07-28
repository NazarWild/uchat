#include "../inc/uchat.h"

char *mx_find_login_by_id(t_list *login_id, char *id) {
    t_list *p = login_id;

    while(p) {
        if (mx_strcmp(id, p->id) == 0) {
            printf("id new = %s p->id = %s\n",id, p->id);
            return p->login;
        }
        p = p->next;
    }
    printf("NULL\n");
    return NULL;
}

char *mx_find_id_by_login(t_list *login_id, char *login) {
    t_list *p = login_id;

    while(p) {
        if (mx_strcmp(login, p->login) == 0)
            return p->id;
        p = p->next;
    }
    return NULL;
}
