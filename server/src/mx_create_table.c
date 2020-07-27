#include "../inc/uchat.h"

void mx_create_table(char *name_table, char *values_table) {
    char *sql;
    t_sqlite *lite = malloc(sizeof(t_sqlite));

    asprintf(&sql, "CREATE TABLE IF NOT EXISTS %s(%s);", name_table, values_table);
    lite->callback = NULL;
    lite->data = NULL;
    lite->sql = sql;
    mx_sqlite(lite, NULL);
    free(sql);
}

static void tables () {
    mx_create_table("chats",
                    "chats_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "chat TEXT NOT NULL"); 
    mx_create_table("messeges",
                    "text_id INTEGER PRIMARY KEY AUTOINCREMENT, " 
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
                    "FOREIGN KEY(users_id) REFERENCES persons_id(users_id)"
                    "ON DELETE CASCADE ON UPDATE CASCADE ");
}

void mx_tables() {
    mx_create_table("persons_id",
                    "users_id INTEGER PRIMARY KEY AUTOINCREMENT, " 
                    "login TEXT, "
                    "pass TEXT,"
                    "theme TEXT,"
                    "language INT,"
                    "status TEXT,"
                    "level INT, "
                    "photo TEXT,"
                    "fullname TEXT,"
                    "nickname TEXT,"
                    "date_of_birthd TEXT");
    mx_create_table("users_chat",
                    "users_id INT, "
                    "chats_id INT, "
                    "PRIMARY KEY (users_id, chats_id) "
                    "FOREIGN KEY(users_id) REFERENCES persons_id(users_id), "
                    "FOREIGN KEY (chats_id) REFERENCES chats(chats_id) "
                    "ON DELETE CASCADE ON UPDATE CASCADE");
    tables();
}