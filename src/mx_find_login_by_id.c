#include "../inc/uchat.h"

char *mx_find_login_by_id(t_list *login_id, char *id) {
	t_list *p = login_id;

	while(p) {
		if (strcmp(id, p->id) == 0)
			return p->login;
		p = p->next;
	}
	return NULL;
}