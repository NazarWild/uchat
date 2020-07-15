#include "../inc/uchat.h"

void mx_sqlite(t_sqlite *lite, use_mutex_t *mutex) {
    sqlite3 *db = 0;
    char *err_msg = 0;
    int rc = 0;

    if (mutex != NULL)
        pthread_mutex_lock(mutex->mutex);
    rc = sqlite3_open("data_base.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        if (mutex != NULL)
            pthread_mutex_unlock(mutex->mutex);
        return;
    }
    rc = sqlite3_exec(db, lite->sql, lite->callback, lite->data, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        if (mutex != NULL)
            pthread_mutex_unlock(mutex->mutex);
        return;
    }
    sqlite3_close(db);
    if (mutex != NULL)
        pthread_mutex_unlock(mutex->mutex);
}

void mx_add_to_table(char *name_table, char *values_table, char *values, use_mutex_t *mutex) {
    char *sql = 0;
    t_sqlite *lite = malloc(sizeof(t_sqlite) * 1);

    asprintf(&sql, "INSERT INTO %s (%s) VALUES (%s);", name_table,
                    values_table, values);
    lite->callback = NULL;
    lite->data = NULL;
    lite->sql = sql;
    mx_sqlite(lite, mutex);
    free(sql);
    free(lite);
}

void mx_set_value(char *name_table, char *str_change, char *search_condition, use_mutex_t *mutex) {
    char *sql = 0;
    t_sqlite *lite = malloc(sizeof(t_sqlite) * 1);

    asprintf(&sql, "UPDATE %s SET %s WHERE %s;", name_table, str_change,
            search_condition);
    lite->callback = NULL;
    lite->data = NULL;
    lite->sql = sql;
    mx_sqlite(lite, mutex);
    free(sql);
    free(lite);
}

void mx_select(char *search, char *tables, int (*callback)(void *, int, char **, char **), void *data, use_mutex_t *mutex) { // структура
    char *sql = 0;
    t_sqlite *lite = malloc(sizeof(t_sqlite) * 1);

    asprintf(&sql, "SELECT %s FROM %s;", search, tables);
    lite->callback = callback;
    lite->data = data;
    lite->sql = sql;
    mx_sqlite(lite, mutex);
    free(sql);
    free(lite);
}

void mx_delete_from_db(char *name_table, char *condition, use_mutex_t *mutex) {
    char *sql = 0;
    t_sqlite *lite = malloc(sizeof(t_sqlite) * 1);

    asprintf(&sql, "DELETE FROM %s WHERE %s;", name_table, condition);
    lite->callback = NULL;
    lite->data = NULL;
    lite->sql = sql;
    mx_sqlite(lite, mutex);
    free(lite);
    free(sql);
}
