#include "../inc/sqlite.h"

void mx_sqlite(char *sql, int (*callback)(void *, int, char **, char **), void *data) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("data_base.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    rc = sqlite3_exec(db, sql, callback, data, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return;
    }
    sqlite3_close(db);
}

void mx_add_to_table(char *name_table, char *values_table, char *values) {
    char *sql;

    asprintf(&sql, "INSERT INTO %s (%s) VALUES (%s);", name_table,
                    values_table, values);
    mx_sqlite(sql, 0, 0);
    free(sql);
}

void mx_set_value(char *name_table, char *str_change, char *search_condition) {
    char *sql;

    asprintf(&sql, "UPDATE %s SET %s WHERE %s;", name_table, str_change,
            search_condition);
    mx_sqlite(sql, 0, 0);
    free(sql);
}

void mx_select(char *search, char *tables, int (*callback)(void *, int, char **, char **), void *data) {
    char *sql;

    asprintf(&sql, "SELECT %s FROM %s", search, tables);
    mx_sqlite(sql, callback, data);
    free(sql);
}
