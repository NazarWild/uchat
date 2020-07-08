#include "../inc/uchat.h"

static void mylvl(use_mutex_t *mutex) {
    //iz bd dostaem vse chto nado to est po loginu uroven
    write(mutex->cli_fd, "Your level: ", 13);
    //mx_select("level", "persons_id", )
}

static void start(use_mutex_t *mutex) {
    // nachinaem cacueto zagadku proveriaya na raiting i v zavisimosti ot raitinga vivodim zagadku
    // pervaya zagadka shifr cezara

}

static void command_false(use_mutex_t *mutex) {
    // commanda ne izvestna
    write(mutex->cli_fd, "Chto eto za slovo?", 19);
}

static void answer(use_mutex_t *mutex) {
    // poluchaem iz db raiting 
    if (0 == 0) { //left is number of raiting
        //doing something interesting
        //answers
        //if answer ok return ;
    }
    else if (1 == 1) {
        //doing something interesting
    }
    else if (2 == 2) {
        //doing something interesting
    }
    else if (3 == 3) {
        //doing something interesting
    }
    write(mutex->cli_fd, "hphah you are so stuped, wrong answer!!", 40);
}

void mx_papa_bot(cJSON *MESS, use_mutex_t *mutex) { //vsegda nado budet otpravliat chto oni v etom chate ili tipa togo chtobi pisat im commands
    char *mess = strdup(MESS->valuestring);

    if (strcmp(mess, "./mylvl") == 0)
        mylvl(mutex);
    else if (strcmp(mess, "./start") == 0)
        start(mutex);
    else if (strncmp(mess, "./answer:", 10) == 0) 
        answer(mutex);
    else 
        command_false(mutex);
}


