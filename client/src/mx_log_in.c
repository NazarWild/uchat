#include "../inc/uchat.h"

int mx_log_in(char *login, char *pass, t_widget_my *widge) {
    widge->login = strdup(login);
    widge->pass = strdup(pass);
    widge->cur_chat_id = 0;
    widge->chat_id = 0;
    widge->to = strdup("PAPA_BOT");
    widge->res_png = strdup("client/img_chat/anonym.png");
    widge->user_profile = (t_profile_list *)malloc(sizeof(t_profile_list));
    widge->login_id = NULL;

	memset(widge->user_profile, 0, sizeof(t_profile_list));
    widge->user_profile->fullname = strdup("set this field");
    widge->user_profile->nickname = strdup("set this field");
    mx_connection(widge);
    return 1;
}
