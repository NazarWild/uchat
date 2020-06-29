#ifndef UCHAT_H
#define UCHAT_H 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <wchar.h>	
#include <fcntl.h>
#include <stdbool.h>
#include <malloc/malloc.h>
#include "cJSON.h"
#include <gtk/gtk.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 6969
#define USERS 200

typedef struct s_widget_my {
    GtkBuilder *builder;

    GtkWidget *window;
    GtkWidget *chat;

    GtkWidget *win_reg;
    GtkWidget *win_sign;
    
    GtkWidget *user_name; //ввод юзера
    GtkWidget *user_password; //ввод пароля

    GtkWidget *sign_in; //кнопка входа
    GtkWidget *sign_up; //кнопка регистрации

    GtkWidget *create_user_name;
    GtkWidget *create_user_password;
    GtkWidget *repeat_user_password;
    GtkWidget *registration;
    GtkWidget *return_sign_in; //кнопка назад

    GtkWidget *command_line;
    GtkWidget *com_event_box; //ввод сообщения
    GtkWidget *setting;
    GtkWidget *message; //временно

    GtkLabel *name_exists; //nd ошибка регистрации
    GtkLabel *wrong_login; // ошибка входа
    GtkFixed *message_win; //окно переписки

    GtkWidget *list_box;
    GtkWidget *sw;
    GtkWidget *profile_button;
    GtkWidget *send_button;

    GtkWidget *scroll;

    GtkWidget *friends;

    //ndykyy
    GtkLabel *fullname;
    GtkLabel *nickname;
    GtkLabel *birth;
    GtkWidget *fullname_entry;
    GtkWidget *nickname_entry;
    GtkWidget *birth_entry;
    GtkWidget *status;
    GtkWidget *profile_photo_button;
    GtkWidget *man1;
    GtkWidget *man2;
    GtkWidget *man3;
    GtkWidget *girl1;
    GtkWidget *girl2;
    GtkWidget *girl3;
    char *login;
    char *pass;
    char *to;
    int sockfd;
    char *str;
    char *res_png;
}              t_widget_my;

int mx_log_in(char *login, char *pass, t_widget_my *widge);
int mx_register(char *login, char *pass, t_widget_my *widge);
void mx_connection(t_widget_my *widge);
void mx_create_widge(t_widget_my *widge);
void mx_login_win(t_widget_my *widge);
int main (int argc, char *argv[]);
void mx_chat_win(t_widget_my *widge);
void mx_design(t_widget_my *widge);
void mx_message_from(t_widget_my *widge, const gchar *text);
void mx_message_to(t_widget_my *widge, const gchar *text);
void mx_create_friend(t_widget_my *widge, const gchar *text);

void mx_profile_gtk(t_widget_my *widge);
void mx_profile_photo_box(t_widget_my *widge);
bool mx_parse_sign_in(t_widget_my *widge, char *log, char *pass, char *rpt);
#endif
