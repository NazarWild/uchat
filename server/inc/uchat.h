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
//#include "sqlite.h"

#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/evp.h>

#define PORT 6969
#define USERS 200

typedef struct s_login_pass {
    char *login;
    char *pass;
    // int socket;
} t_login_pass;

typedef struct s_sqlite {
    char *sql;
    int (*callback)(void *, int, char **, char **);
    void *data;
} t_sqlite;

typedef struct s_online {
    char *login;
    int id;
    bool online;
} t_online;

typedef struct use_mutex_tag {
    pthread_mutex_t mutex;
    int cli_fd;
} use_mutex_t;

typedef struct s_list {
    void *data;
    int users_id;
    struct s_list *next;
} t_list;

void mx_sqlite(t_sqlite *lite, use_mutex_t *mutex);
void mx_create_table(char *name_table, char *values_table);
void mx_tables();
void mx_add_to_table(char *name_table, char *values_table, char *values, use_mutex_t *mutex);
void mx_set_value(char *name_table, char *str_change, char *search_condition, use_mutex_t *mutex);
void mx_select(char *search, char *tables, int (*callback)(void *, int, char **, char **), void *data, use_mutex_t *mutex);
bool mx_path_connect(char *login, char *pass, use_mutex_t *mutex);
t_list *mx_where_not_1(use_mutex_t *mutex);
void mx_pop_front(t_list **head);
t_list *mx_create_node(void *data);
void mx_push_front(t_list **list, void *data);
void mx_add_message(char *login, int chats_id, char *text, int type_text, use_mutex_t *mutex);
void mx_delete_from_db(char *name_table, char *condition, use_mutex_t *mutex);

int main(int argc, char *argv[]);
bool mx_registr(use_mutex_t *mutex); //server
void mx_sign_in_error(int fd); //server
void mx_creating(cJSON* root, use_mutex_t *mutex); //server
bool mx_pass_connect(char *login, char *pass, use_mutex_t *mutex);
void mx_send_mess(cJSON *root, use_mutex_t *mutex);
char *mx_itoa(int number);
void mx_whoonline(use_mutex_t *param); 
void mx_papa_bot(cJSON *FROM, cJSON *MESS, use_mutex_t *mutex);
bool mx_delete(use_mutex_t *param, cJSON *root);
void mx_delete_socket(use_mutex_t *param);
void mx_free_online(t_list *online_struct);
void mx_file_type(cJSON *root, use_mutex_t *mutex);
char *mx_strjoin(const char *s1, const char *s2);
char *mx_strnew(const int size);



#endif
