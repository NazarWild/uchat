#include "../inc/uchat.h"

int mx_log_in(char *login, char *pass, t_widget_my *widge) {
	t_userdata *data = (t_userdata *)malloc(sizeof(t_userdata));

	data->login = strdup(login);
	data->pass = strdup(pass);
	data->to = strdup("okolevatov");
	mx_connection(widge, data);
	return 1;
}
