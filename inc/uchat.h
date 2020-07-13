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
#include <sys/stat.h>
#include <arpa/inet.h>

#define PORT 6969
#define USERS 200

typedef struct s_list {
    char *login;
    char *id;
    bool online;
    struct s_list *next;
}              t_list;

typedef struct s_widget_my {
    GtkBuilder *builder;

    GtkWidget *window;
    GtkWidget *chat;

    GtkWidget *win_reg;
    GtkWidget *win_sign;
    GtkWidget *win_sett;
    
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

    GtkWidget **friend_button;
    int id_friend;

    GtkWidget *who_writing;

    GtkWidget *sticker_pack;
    GtkWidget *file_button;
    GtkWidget *achiev;

    int color_mode;
    GtkCssProvider *dark;

    GtkWidget *theme_1;
    GtkWidget *theme_2;
    GtkWidget *theme_3;
    GtkWidget *theme_4;
    GtkWidget *theme_5;
    GtkWidget *theme_6;

    GtkWidget *back;

    GtkWidget *main_chat;

    GtkWidget *scrolled;

    GtkWidget *choose_user;

    gint window_x;
    gint window_y;
    GtkWidget *window_profile;

    gint index;
    
    int on_profile;

    gchar *te;

    GtkWidget **message_send;
    int message_id;

    //images
    GdkPixbuf *profile_img;
    GdkPixbuf *smile_img;
    GdkPixbuf *send_img;
    GdkPixbuf *file_img;
    GdkPixbuf *achiev_img;
    GdkPixbuf *setting_img;
    GdkPixbuf *wallpaper1_img;
    GdkPixbuf *wallpaper2_img;
    GdkPixbuf *wallpaper3_img;
    GdkPixbuf *wallpaper4_img;
    GdkPixbuf *wallpaper5_img;
    GdkPixbuf *wallpaper6_img;
    GdkPixbuf *wallpaper7_img;
    GdkPixbuf *wallpaper8_img;
    GdkPixbuf *install_img;

    GtkWidget *profile_icon;
    GtkWidget *smile_icon;
    GtkWidget *send_icon;
    GtkWidget *file_icon;
    GtkWidget *achiev_icon;
    GtkWidget *setting_icon;
    GtkWidget *wallpaper1_icon;
    GtkWidget *wallpaper2_icon;
    GtkWidget *wallpaper3_icon;
    GtkWidget *wallpaper4_icon;
    GtkWidget *wallpaper5_icon;
    GtkWidget *wallpaper6_icon;
    GtkWidget *wallpaper7_icon;
    GtkWidget *wallpaper8_icon;
    GtkWidget *install_icon;
    //

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
    int port;
    char *ip;
    char *filename;
    int bytes;
    int int_of_dot;
    t_list *login_id;
}              t_widget_my;

int mx_log_in(char *login, char *pass, t_widget_my *widge);
int mx_register(char *login, char *pass, t_widget_my *widge);
void mx_connection(t_widget_my *widge);
void mx_create_widge(t_widget_my *widge);
void mx_login_win(t_widget_my *widge);
int main (int argc, char *argv[]);
void mx_chat_win(t_widget_my *widge);
void mx_message_from(t_widget_my *widge, const gchar *text);
void mx_message_to(t_widget_my *widge, const gchar *text);
void mx_create_friend(t_widget_my *widge, const gchar *text);
void mx_set_images(t_widget_my *widge);
void mx_setting_win(GtkWidget* widget, void *dat);

void mx_theme_1(GtkWidget* widget, void *dat);
void mx_theme_2(GtkWidget* widget, void *dat);
void mx_theme_3(GtkWidget* widget, void *dat);
void mx_theme_4(GtkWidget* widget, void *dat);
void mx_theme_5(GtkWidget* widget, void *dat);
void mx_theme_6(GtkWidget* widget, void *dat);

// void mx_pop_front(t_message_list **head);
// t_message_list *mx_create_node(void *data);
// void mx_push_front(t_message_list **list, void *data);

void mx_remove_friend_list(GtkWidget* widget, void *dat);
void mx_send_file_to(t_widget_my *widge, const gchar *text);


void mx_profile_gtk(t_widget_my *widge);
void mx_photo_set(t_widget_my *widge);
bool mx_parse_sign_in(t_widget_my *widge, char *log, char *pass, char *rpt);

void mx_dialog_open(t_widget_my *widge);
#endif
