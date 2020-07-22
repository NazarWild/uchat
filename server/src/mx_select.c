#include "../inc/uchat.h"

t_select *mx_struct_select(char *search, char *tables,
            int (*callback)(void *, int, char **, char **), void *data) {
    t_select *select = malloc(sizeof(t_select));

    select->search = search;
    select->tables = tables;
    select->callback = callback;
    select->data = data;
    return select;
}

void mx_select(t_select *select, t_use_mutex *mutex) {
    char *sql = 0;
    t_sqlite *lite = malloc(sizeof(t_sqlite) * 1);
    t_select *new = select;

    asprintf(&sql, "SELECT %s FROM %s;", new->search, new->tables);
    lite->callback = new->callback;
    lite->data = new->data;
    lite->sql = sql;
    mx_sqlite(lite, mutex);
    free(sql);
    free(select);
    free(lite);
}
