#include "../inc/uchat.h"

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

void mx_answers_papa(t_use_mutex *mutex) {
    char *data = NULL;
    char *new = NULL; 

    asprintf(&new, "persons_id WHERE users_id = %d", mutex->user_id);
    mx_select("level", new, callback_persons_id, &data, mutex);
    free(new);
    mutex->lvl = atoi(data);
    // poluchaem iz db raiting 
    if (mutex->lvl == 0) { //left is number of raiting
        //doing something interesting
        //answers
        //if answer ok return ;
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
    write(mutex->cli_fd, "hphah you are so stuped, wrong answer!!", 39);
}
