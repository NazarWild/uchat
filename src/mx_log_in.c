#include "../inc/uchat.h"

int mx_log_in(char *login, char *pass) {
	char *arr[] = {"ndykyy", "okolevatov", "dmushynska", "opoliarenk", NULL};
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
		mx_connection();
	}
	else {
		printf("NO SUCH USER %s\n", login);
		return 0;
	}
	return 1;
}
