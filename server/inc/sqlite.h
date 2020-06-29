#ifndef SQLITE_H
#define SQLITE_H

#include "uchat.h"
#include <sqlite3.h>

typedef struct s_login_pass {
    char *login;
    char *pass;
    // int socket;
} t_login_pass;

typedef struct s_list {
    void  *data;
    struct s_list *next;
} t_list;

void mx_sqlite(char *sql, int (*callback)(void *, int, char **, char **), void *data);
void mx_create_table(char *name_table, char *values_table);
void mx_tables();
void mx_add_to_table(char *name_table, char *values_table, char *values);
void mx_set_value(char *name_table, char *str_change, char *search_condition);
void mx_select(char *search, char *tables, int (*callback)(void *, int, char **, char **), void *data);
bool mx_path_connect(char *login, char *pass);
t_list *mx_where_not_1();
void mx_pop_front(t_list **head);
t_list *mx_create_node(void *data);
void mx_push_front(t_list **list, void *data);
void mx_add_mess(char *login, char *chats, char *text, int type_text);


#endif