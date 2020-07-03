#include "../inc/uchat.h"

static void mylvl(int fd, cJSON *FROM) {
    //iz bd dostaem vse chto nado to est po loginu uroven
    write(fd, "Your level: ", 13);
    //mx_select("level", "persons_id", )
}

static void start(int fd, cJSON *FROM) {
    // nachinaem cacueto zagadku proveriaya na raiting i v zavisimosti ot raitinga vivodim zagadku
    // pervaya zagadka shifr cezara

}

static void command_false(int fd, cJSON *FROM) {
    // commanda ne izvestna
    write(fd, "Chto eto za slovo?", 19);
}

static void answer(int fd, cJSON *FROM) {
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
    write(fd, "hphah you are so stuped, wrong answer!!", 40);
}

void mx_papa_bot(cJSON *FROM, cJSON *MESS, int fd) { //vsegda nado budet otpravliat chto oni v etom chate ili tipa togo chtobi pisat im commands
    char *mess = strdup(MESS->valuestring);

    if (strcmp(mess, "./mylvl") == 0)
        mylvl(fd, FROM);
    else if (strcmp(mess, "./start") == 0)
        start(fd, FROM);
    else if (strncmp(mess, "./answer:", 10) == 0) 
        answer(fd, FROM);
    else 
        command_false(fd, FROM);
}


