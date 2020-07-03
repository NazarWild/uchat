#ifndef SQLITE_H
#define SQLITE_H

#include "uchat.h"
#include <sqlite3.h>

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

typedef struct use_mutex_tag {
    pthread_mutex_t mutex;
    int cli_fd;
} use_mutex_t;

typedef struct s_list {
    void *data;
    int users_id;
    struct s_list *next;
} t_list;

void mx_sqlite(char *sql, int (*callback)(void *, int, char **, char **), void *data, use_mutex_t *mutex);
void mx_create_table(char *name_table, char *values_table, use_mutex_t *mutex);
void mx_tables();
void mx_add_to_table(char *name_table, char *values_table, char *values, use_mutex_t *mutex);
void mx_set_value(char *name_table, char *str_change, char *search_condition, use_mutex_t *mutex);
void mx_select(char *search, char *tables, int (*callback)(void *, int, char **, char **), void *data, use_mutex_t *mutex);
bool mx_path_connect(char *login, char *pass, use_mutex_t *mutex);
t_list *mx_where_not_1(use_mutex_t *mutex);
void mx_pop_front(t_list **head);
t_list *mx_create_node(void *data, int users_id);
void mx_push_front(t_list **list, void *data, int users_id);
void mx_add_mess(char *login, char *chats, char *text, int type_text, use_mutex_t *mutex);
void mx_delete_from_db(char *name_table, char *condition, use_mutex_t *mutex);


#endif