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
    
    GtkWidget *user_name;
    GtkWidget *user_password;

    GtkWidget *sign_in;
    GtkWidget *sign_up;

    GtkWidget *create_user_name;
    GtkWidget *create_user_password;
    GtkWidget *repeat_user_password;
    GtkWidget *registration;
    GtkWidget *return_sign_in;

    GtkWidget *command_line;
    GtkWidget *setting;
    GtkLabel *message;

    GtkWidget *check;

    GtkFixed *message_win;

    //ndykyy
    char *login;
    char *pass;
    char *to;
    int sockfd;
    char *str;

}              t_widget_my;

int mx_log_in(char *login, char *pass, t_widget_my *widge);
void mx_connection(t_widget_my *widge);
void mx_create_widge(t_widget_my *widge);
void mx_login_win(t_widget_my *widge);
int main (int argc, char *argv[]);
void mx_chat_win(t_widget_my *widge);

#endif
