#include "../inc/uchat.h"

int mx_log_in(char *login, char *pass, t_widget_my *widge) {
    widge->login = strdup(login);
    widge->pass = strdup(pass);
    widge->to = "PAPA_BOT";
    
    mx_connection(widge);
    return 1;
}
