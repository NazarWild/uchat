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
#include <openssl/sha.h>

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

    GtkWidget *create_user_name; //ввод логина
    GtkWidget *create_user_password; //ввод пароля
    GtkWidget *repeat_user_password; //повтор пароля
    GtkWidget *registration; //кнопка регистрации
    GtkWidget *return_sign_in; //кнопка назад

    GtkWidget *command_line; //строка ввода
    GtkWidget *com_event_box; //ввод сообщения
    GtkWidget *setting; //кнопка настройки

    GtkLabel *name_exists; //nd ошибка регистрации
    GtkLabel *wrong_login; // ошибка входа
    GtkFixed *message_win; //окно переписки

    GtkWidget *list_box; //лист бокс дпереписки
    GtkWidget *profile_button; //кнопка профиля
    GtkWidget *send_button; //кнопка отправки собщения

    GtkWidget *friends; //лист бокс для списка друзей

    GtkWidget **friend_button; //массив друзей
    int id_friend; //id друга

    GtkWidget *who_writing; //кнопка названия чата

    GtkWidget *sticker_pack; //кнопка стикеров
    GtkWidget *file_button; //кнопка отправки файлов
    GtkWidget *achiev; //хакерный режим

    GtkCssProvider *theme; //провайдер, меняем тему

    //кнопки тем
    GtkWidget *theme_1;
    GtkWidget *theme_2;
    GtkWidget *theme_3;
    GtkWidget *theme_4;
    GtkWidget *theme_5;
    GtkWidget *theme_6;
    //

    GtkWidget *back; //кнопка выхода из настроек

    GtkWidget *main_chat;

    GtkWidget *scrolled; //окно скрола для переписки

    GtkWidget *choose_user; //окно скрола для друзей

    gint window_x; //передвижение окна по х
    gint window_y; //передвижение окна по у
    GtkWidget *window_profile; //окно профиля
    GtkWidget *mini_window_profile; //окно профиля

    gint index; //индекс последней строки в списке друзей (для удаления листа)
    gint index_mess_to; //индекс последней строки в списке сообщений (для удаления листа)
    
    int on_profile; //что бы нельзя было открывать несколько профилей одновременно

    gchar *path_file;

    GtkWidget **message_send; //массив сообщений
    int message_id; //id сообщения

    GtkAdjustment *slider_adj; //adj слайдер для прокрокрутки ползунка

    GtkWidget *papa_bot; //папа бот...

    GtkWidget *search_entry;

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
    GdkPixbuf *online_img;
    GdkPixbuf *offline_img;
    GdkPixbuf *edit_img;
    GdkPixbuf *trash_img;
    GdkPixbuf *installbutt_img;

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
    GtkWidget *online_icon;
    GtkWidget *offline_icon;
    GtkWidget *edit_icon;
    GtkWidget *trash_icon;
    GtkWidget *installbutt_icon;
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
void mx_create_friend(t_widget_my *widge, const gchar *text, int online);
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

void mx_remove_friend_list(t_widget_my *widge);
void mx_remove_mess(void *data);
void *mx_realloc(void *ptr, size_t size, ssize_t from);
void mx_send_file_to(t_widget_my *widge, const gchar *text);
GtkWidget *mx_time_mess_to(char *data);
GtkWidget *mx_name_mess_to(char *user);
GtkWidget *mx_time_mess_from(char *data);
GtkWidget *mx_name_mess_from(char *user);

void mx_profile_gtk(t_widget_my *widge);
void mx_mini_profile_gtk(t_widget_my *widge);
void mx_photo_set(t_widget_my *widge);
bool mx_parse_sign_in(t_widget_my *widge, char *log, char *pass, char *rpt);

void mx_dialog_open(t_widget_my *widge);
char *mx_find_login_by_id(t_list *p, char *id);

char *mx_hash_to_string(unsigned char *hash);
char *mx_hash(char *login, char *pass);
#endif
