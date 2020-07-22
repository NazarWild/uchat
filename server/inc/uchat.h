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
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sqlite3.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sys/stat.h>

#define PORT 6969
#define USERS 200
typedef struct s_list {
    void *data;
    struct s_list *next;
}              t_list;
typedef struct s_login_pass {
    char *login;
    char *pass;
    // int socket;
}              t_login_pass;

typedef struct s_sqlite {
    char *sql;
    int (*callback)(void *, int, char **, char **);
    void *data;
}              t_sqlite;

typedef struct s_history {
    char *text;
    int text_id;
    int chats_id;
}              t_history;

typedef struct s_online {
    char *login;
    int id;
    bool online;
}              t_online;

typedef struct s_ssl {
    int user_id;
    SSL *ssl;
}              t_ssl;

typedef struct s_use_mutex {
    pthread_mutex_t *mutex;
    int cli_fd;
    int user_id;
    short int lvl;
    SSL * my_ssl;
    t_list **ssl_list;
}              t_use_mutex;

typedef struct s_messeges {
    char *text;
    int chats_id;
    t_list *who_is_here;
    int who_write;
}              t_messeges;

typedef struct s_select {
    char *search;
    char *tables;
    int (*callback)(void *, int, char **, char **);
    void *data;
}              t_select;


char *mx_parse_str(char *str);
void mx_sqlite(t_sqlite *lite, t_use_mutex *mutex);
void mx_create_table(char *name_table, char *values_table);
void mx_tables();
void mx_add_to_table(char *name_table, char *values_table, char *values,
                                                        t_use_mutex *mutex);
void mx_set_value(char *name_table, char *str_change, char *search_condition,
                                                        t_use_mutex *mutex);
void mx_select(t_select *select, t_use_mutex *mutex);
bool mx_path_connect(char *login, char *pass, t_use_mutex *mutex);
t_list *mx_where_not_1(t_use_mutex *mutex);
void mx_pop_front(t_list **head);
t_list *mx_create_node(void *data);
void mx_push_front(t_list **list, void *data);
void mx_add_message(int chats_id, char *text, int type_text,
                                                t_use_mutex *mutex);
void mx_delete_from_db(char *name_table, char *condition, t_use_mutex *mutex);
t_list *mx_history_chat(int chats_id, t_use_mutex *mutex);
t_list *mx_list_last_users_messeges(t_use_mutex *mutex);
void mx_answers_papa(t_use_mutex *mutex, char *mess);

int main(int argc, char *argv[]);
bool mx_registr(t_use_mutex *mutex); //server
void mx_sign_in_error(int fd); //server
void mx_creating(cJSON* root, t_use_mutex *mutex); //server
bool mx_pass_connect(char *login, char *pass, t_use_mutex *mutex);
void mx_send_mess(cJSON *root, t_use_mutex *mutex);
char *mx_itoa(int number);
void mx_whoonline(t_use_mutex *param); 
void mx_papa_bot(cJSON *MESS, t_use_mutex *mutex);
bool mx_delete(t_use_mutex *param, cJSON *root);
void mx_delete_socket(t_use_mutex *param);
void mx_free_online(t_list *online_struct);
void mx_file_type(cJSON *root, t_use_mutex *mutex);
char *mx_strjoin(const char *s1, const char *s2);
char *mx_strnew(const int size);
void mx_chats_send(t_use_mutex *mutex);
void mx_new_chat(cJSON* TO, cJSON* MESS, cJSON* CHAT_ID, t_use_mutex *mutex);
void mx_group_chat(cJSON* root, t_use_mutex *mutex);
void mx_send_group(cJSON* MESS, cJSON* USERS_GRP, cJSON* CHAT_ID,
                                                    t_use_mutex *mutex);
int mx_callback_persons_id(void *data, int argc, char **argv,
                                                        char **ColName);
int mx_len_of_file(char *file);
void mx_prof_photo(cJSON *root, t_use_mutex *mutex);
void mx_usr_prof(cJSON *root, t_use_mutex *mutex);

// SSL_TLS
SSL_CTX* mx_initserverctx(void);
t_list *mx_search_ssl(t_use_mutex *mutex, int id);
void mx_loadcertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile);
void mx_send_user_with_dif_sock(t_use_mutex *mutex, int who, char *str,
                                                                int bytes);
t_select *mx_struct_select(char *search, char *tables,
            int (*callback)(void *, int, char **, char **), void *data);
void mx_slast_mess(cJSON *root, t_use_mutex *param);
void mx_change_mess(cJSON *root, t_use_mutex *param);

#endif
