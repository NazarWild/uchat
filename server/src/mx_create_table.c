#include "../inc/sqlite.h"

void mx_create_table(char *name_table, char *values_table) {
    char *sql;

    asprintf(&sql, "CREATE TABLE IF NOT EXISTS %s(%s);", name_table, values_table);
    mx_sqlite(sql, NULL, NULL);
    free(sql);
}

void mx_tables() {
    mx_create_table("persons_id",
                    "users_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "login TEXT, "
                    "pass TEXT ");
    mx_create_table("chats",
                    "chats_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "chat TEXT NOT NULL");
    mx_create_table("users_chat",
                    "users_id INT, "
                    "chats_id INT, "
                    "PRIMARY KEY (users_id, chats_id) "
                    "FOREIGN KEY(users_id) REFERENCES persons_id(users_id), "
                    "FOREIGN KEY (chats_id) REFERENCES chats(chats_id) "
                    "ON DELETE CASCADE ON UPDATE CASCADE");
    mx_create_table("messeges",
                    "users_id INT, "
                    "chats_id INT, "
                    "text TEXT, "
                    "type_text INT, "
                    "time TEXT, "
                    "FOREIGN KEY(users_id) REFERENCES persons_id(users_id), "
                    "FOREIGN KEY(chats_id) REFERENCES chats(chats_id) "
                    "ON DELETE CASCADE ON UPDATE CASCADE ");
    mx_create_table("sockets",
                    "users_id INT, "
                    "socket INT DEFAULT -1, "
                    "FOREIGN KEY(users_id) REFERENCES persons_id(users_id)");
}