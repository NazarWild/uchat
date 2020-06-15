#include "../inc/sqlite.h"

void mx_create_table(char *name_table, char *values_table) {
    char *sql;

    asprintf(&sql, "DROP TABLE IF EXISTS %s; CREATE TABLE %s(%s);", name_table,
                    name_table, values_table);
    mx_sqlite(sql, NULL, NULL);
    free(sql);
}

void mx_tables() {
    mx_create_table("persons_id",
                    "users_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "login TEXT, "
                    "pass TEXT, "
                    "socket INT DEFAULT -1");
    mx_create_table("chats",
                    "chats_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "chat TEXT DEFAULT 'chat'");
    mx_create_table("users_chat",
                    "users_id INT, "
                    "chats_id INT, "
                    "PRIMARY KEY (users_id, chats_id) "
                    "FOREIGN KEY(users_id) REFERENCES persons_id(users_id), "
                    "FOREIGN KEY (chats_id) REFERENCES chats(chats_id) "
                    "ON DELETE CASCADE ON UPDATE CASCADE");
    mx_create_table("messeges",
                    "chats_id INT, "
                    "text TEXT, "
                    "type_text INT, "
                    "FOREIGN KEY(chats_id) REFERENCES chats(chats_id) "
                    "ON DELETE CASCADE ON UPDATE CASCADE ");
}