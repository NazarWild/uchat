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
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <time.h>

#define PORT 6969
#define USERS 200

typedef struct s_row_mess {
    //send message
    GtkWidget *trash;
    GtkWidget *row;
    GtkWidget *box;
    GtkWidget *box2;
    GtkWidget *label;
    GtkWidget *box_in;
    GtkWidget *box3;
    GtkWidget *nickname;
    GtkWidget *data_box;
    GtkWidget *box4;
    GtkWidget *installbutt;
}              t_row_mess;

typedef struct s_profile_list {
    char *fullname;
    char *nickname;
    char *birth;
    char *status;
    char *resource;
}              t_profile_list;

typedef struct s_message {
    GtkWidget *message;
    int chat_id;
    int message_id;
}              t_message;

typedef struct s_page {
    GtkWidget *list_box;
    GtkWidget *scroll;
    GtkAdjustment *slider_adj;
    GtkWidget *friend_butt;
}              t_page;

typedef struct s_list_gtk {
    void *data;
    struct s_list_gtk *next;
}              t_list_gtk;

typedef struct s_list {
    char *login;
    char *id;
    bool online;
    struct s_list *next;
}              t_list;

typedef struct s_widget_my {
    t_list_gtk *message_list;
    t_list_gtk *page_list;

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

    GtkWidget *profile_button; //кнопка профиля
    GtkWidget *send_button; //кнопка отправки собщения

    // GtkAdjustment **slider_adj; //массив adj слайдер для прокрокрутки ползунка
    int id_lb_sw;

    GtkWidget *friends; //лист бокс для списка друзей

    // GtkWidget **friend_button; //массив друзей
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
    //

    GtkWidget *back; //кнопка выхода из настроек

    GtkWidget *main_chat;

    GtkWidget *choose_user; //окно скрола для друзей

    gint window_x; //передвижение окна по х
    gint window_y; //передвижение окна по у
    GtkWidget *window_profile; //окно профиля
    GtkWidget *mini_window_profile; //окно профиля

    gint index_mess_to; //индекс последней строки в списке сообщений (для удаления листа)
    
    int on_profile; //что бы нельзя было открывать несколько профилей одновременно
    int on_sticker; //что бы нельзя было открывать несколько стикерпаков одновременно

    int message_id; //id сообщения

    GtkWidget *papa_bot; //папа бот...

    GtkWidget *search_entry;

    GtkWidget *sep;
    GtkWidget *notebook;
    GtkWidget *page_label;

    char *login_list;

    GtkWidget *win_stick;
    GtkWidget *box_stick;
    GtkWidget *scroll_stick;

    int sticker_to;

    //button for sticker
    GtkWidget *b1;
    GtkWidget *b2;
    GtkWidget *b3;
    GtkWidget *b4;
    GtkWidget *b5;
    GtkWidget *b6;
    GtkWidget *b7;
    GtkWidget *b8;
    GtkWidget *b9;
    GtkWidget *b10;
    GtkWidget *b11;
    GtkWidget *b12;
    GtkWidget *b13;
    GtkWidget *b14;
    GtkWidget *b15;
    GtkWidget *b16;
    GtkWidget *b17;
    GtkWidget *b18;
    GtkWidget *b19;
    GtkWidget *b20;
    //
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
    GdkPixbuf *trash_img;
    GdkPixbuf *installbutt_img;
    GdkPixbuf *b1_img;
    GdkPixbuf *b2_img;
    GdkPixbuf *b3_img;
    GdkPixbuf *b4_img;
    GdkPixbuf *b5_img;
    GdkPixbuf *b6_img;
    GdkPixbuf *b7_img;
    GdkPixbuf *b8_img;
    GdkPixbuf *b9_img;
    GdkPixbuf *b10_img;
    GdkPixbuf *b11_img;
    GdkPixbuf *b12_img;

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
    GtkWidget *trash_icon;
    GtkWidget *installbutt_icon;
    GtkWidget *b1_icon;
    GtkWidget *b2_icon;
    GtkWidget *b3_icon;
    GtkWidget *b4_icon;
    GtkWidget *b5_icon;
    GtkWidget *b6_icon;
    GtkWidget *b7_icon;
    GtkWidget *b8_icon;
    GtkWidget *b9_icon;
    GtkWidget *b10_icon;
    GtkWidget *b11_icon;
    GtkWidget *b12_icon;
    //

    //ndykyy
    GtkLabel *fullname;
    GtkLabel *nickname;
    GtkLabel *birth;
    GtkWidget *fullname_entry;
    GtkWidget *nickname_entry;
    GtkWidget *birth_entry;
    GtkWidget *level;
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
    int int_of_slesh;
    t_list *login_id;
    char *localtime;

    t_profile_list *user_profile;

    int chat_id;
    int cur_chat_id;
    int to_whom;

    SSL *ssl;
    GtkWidget *mini_level;
    GtkWidget *mini_date;
    GtkWidget *mini_name;
    GtkWidget *mini_nick;
    GtkWidget *mini_photo;
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
void mx_create_friend(t_widget_my *widge, const gchar *text, int online, t_page *page);
void mx_set_images(t_widget_my *widge);
void mx_setting_win(GtkWidget* widget, void *dat);

void mx_theme_1(GtkWidget* widget, void *dat);
void mx_theme_2(GtkWidget* widget, void *dat);
void mx_theme_3(GtkWidget* widget, void *dat);
void mx_theme_4(GtkWidget* widget, void *dat);
void mx_theme_5(GtkWidget* widget, void *dat);
void mx_theme_6(GtkWidget* widget, void *dat);

void mx_pop_front_gtk(t_list_gtk **head);
t_list_gtk *mx_create_node_gtk(void *data);
void mx_push_front_gtk(t_list_gtk **list, void *data);

void mx_remove_friend_list(t_widget_my *widge);
void mx_remove_mess(void *data);
void *mx_realloc(void *ptr, size_t size, ssize_t from);
void mx_send_file_to(t_widget_my *widge, const gchar *text);
void mx_send_file_from(t_widget_my *widge, const gchar *text);
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
char *mx_find_id_by_login(t_list *p, char *login);

char *mx_hash_to_string(unsigned char *hash);
char *mx_hash(char *login, char *pass);

void mx_create_chat(t_page *page, t_widget_my *widge, const gchar *text);
char *mx_itoa(int number);
char *mx_strnew(const int size);

void *mx_memrchr(const void *s, int c, size_t n);

void mx_delete_row(GtkWidget *list_box, gint index);
void mx_delete_rows(GtkWidget *widget, void *data);

void mx_sticker(GtkWidget* widget, void *data);
void mx_create_stick(t_widget_my *widge);
void mx_sendsticker(GtkWidget *widget, void *data);
int mx_log_in(char *login, char *pass, t_widget_my *widge);//auditor +
int mx_register(char *login, char *pass, t_widget_my *widge);//auditor -
void mx_connection(t_widget_my *widge);//auditor -
void mx_create_widge(t_widget_my *widge);//auditor +
void mx_login_win(t_widget_my *widge);//auditor +
int main (int argc, char *argv[]);//auditor +
void mx_chat_win(t_widget_my *widge);//auditor +
void mx_message_from(t_widget_my *widge, const gchar *text);//auditor -
void mx_message_to(t_widget_my *widge, const gchar *text);//auditor -
void mx_create_friend(t_widget_my *widge, const gchar *text, int online, t_page *page);//auditor -
void mx_set_images(t_widget_my *widge);//auditor +
void mx_setting_win(GtkWidget* widget, void *dat);//auditor +

void mx_theme_1(GtkWidget* widget, void *dat);//auditor +
void mx_theme_2(GtkWidget* widget, void *dat);//auditor +
void mx_theme_3(GtkWidget* widget, void *dat);//auditor +

void mx_pop_front_gtk(t_list_gtk **head);//auditor +
t_list_gtk *mx_create_node_gtk(void *data);//auditor +
void mx_push_front_gtk(t_list_gtk **list, void *data);//auditor +

void mx_remove_friend_list(t_widget_my *widge);//auditor -
void mx_remove_mess(void *data);//auditor -
void mx_send_file_to(t_widget_my *widge, const gchar *text);//auditor -
void mx_send_file_from(t_widget_my *widge, const gchar *text);//auditor -
GtkWidget *mx_time_mess_to(char *data);//auditor +
GtkWidget *mx_name_mess_to(char *user);//auditor +
GtkWidget *mx_time_mess_from(char *data);//auditor +
GtkWidget *mx_name_mess_from(char *user);//auditor +

void mx_profile_gtk(t_widget_my *widge);//auditor -
void mx_mini_profile_gtk(t_widget_my *widge);//auditor -
void mx_photo_set(t_widget_my *widge);//auditor -
bool mx_parse_sign_in(t_widget_my *widge, char *log, char *pass, char *rpt);//auditor +

void mx_dialog_open(t_widget_my *widge);//auditor -
char *mx_find_login_by_id(t_list *p, char *id);//auditor +

char *mx_hash_to_string(unsigned char *hash);//auditor +
char *mx_hash(char *login, char *pass);//auditor +

void mx_create_chat(t_page *page, t_widget_my *widge, const gchar *text);//auditor +
char *mx_itoa(int number);//auditor -
char *mx_strnew(const int size);//auditor +

void *mx_memrchr(const void *s, int c, size_t n);//auditor +

void mx_delete_row(GtkWidget *list_box, gint index);//auditor +
void mx_delete_rows(GtkWidget *widget, void *data);//auditor -

void mx_sticker(GtkWidget* widget, void *data);//auditor +
void mx_create_stick(t_widget_my *widge);//auditor +
void mx_sendsticker_to(GtkWidget *widget, void *data);//auditor -
void mx_sendsticker_from(char *file_name, t_widget_my *widge);

void mx_send_message(GtkWidget* widget, void *dat);
char *mx_create_json_mess(char *message, t_widget_my *widge);

bool mx_unique_listbox_id(t_widget_my *widge, char *login);
void mx_update_chat_id(t_widget_my *widge, char *login, int new_chat_id);
void mx_set_cur_chat_id(t_widget_my *widge);

char *mx_type_of_file(char *filename, t_widget_my *widge);
int mx_len_of_file(char *file);

SSL *mx_ssl(int fd);
#endif
