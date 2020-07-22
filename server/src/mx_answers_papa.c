#include "../inc/uchat.h"

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

static void level_up(t_use_mutex *mutex) {
    mutex->lvl++;
    char *mass = mx_itoa(mutex->lvl);
    char *str = NULL;

    asprintf(&str, "level WHERE users_id = %d", mutex->user_id);
    mx_set_value("persons_id", mass, str, mutex);
    free(mass);
    free(str);
    write(mutex->cli_fd, "{\"FROM\":\"PAPA_BOT\",\"MESS\":\"YEAH! RIGHT ANSWER!\",\n", 49);
}

void mx_answers_papa(t_use_mutex *mutex, char *mess) {
    char *data = NULL;
    char *new = NULL;
    t_select *select;

    asprintf(&new, "persons_id WHERE users_id = %d", mutex->user_id);
    select = mx_struct_select("level", new, callback_persons_id, &data);
    mx_select(select, mutex);
    free(new);
    mutex->lvl = atoi(data);
    // poluchaem iz db raiting 
    if (mutex->lvl == 0) { 
        char answ[] = "Hello, World! And Welcome to our chat!";
        char *new = mx_strnew(strlen(mess) - 9);
        int j = 0;

        for (int i = 9; i < strlen(mess); i++) 
            new[j] = mess[i];
        if (strcmp(new, answ) == 0) {
            level_up(mutex);
            return ;
        }
    }
    else if (mutex->lvl == 1) {
        //doing something interesting
    }
    else if (mutex->lvl == 2) {
        //doing something interesting
    }
    else if (mutex->lvl == 3) {
        //doing something interesting
    }
    SSL_write(mutex->my_ssl, "hphah you are so stuped, wrong answer!!", 39);
    // write(mutex->cli_fd, "hphah you are so stuped, wrong answer!!", 39);
}
