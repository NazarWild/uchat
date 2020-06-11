#include "../inc/uchat.h"

int mx_log_in(char *login, char *pass, t_widget_my *widge) {
	char *arr[] = {"ndykyy", "okolevatov", "dmushynska", "opoliarenk", NULL};
	t_userdata *data = (t_userdata *)malloc(sizeof(t_userdata));
	data->login = strdup(login);
	data->to = strdup("okolevatov");
	bool connect = false;
	int i = 0;
	pass = "lol";
	while (arr[i]) {
		if(strcmp(arr[i], login) == 0) {
			connect = true;
			break;
		}
		i++;
	}
	if (connect) {
		printf("%s connected\n", login);
		mx_connection(widge, data);
	}
	else {
		printf("NO SUCH USER %s\n", login);
		return 0;
	}
	return 1;
}
