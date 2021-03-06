#include "../inc/uchat.h"

static void mylvl(t_use_mutex *mutex) {
    //iz bd dostaem vse chto nado to est po loginu uroven
    cJSON *root = cJSON_CreateObject();
    char *str = NULL;

    asprintf(&str, "{\"FROM\":\"PAPA_BOT\",\"MESS\":\"Your level: %d\",\"TYPE\":\"text\"\n}", mutex->lvl); 
    SSL_write(mutex->my_ssl, str, strlen(str));
    free(str);
    cJSON_Delete(root);
}

static void start(t_use_mutex *mutex) {
    // nachinaem cacueto zagadku proveriaya na raiting i v zavisimosti ot raitinga vivodim zagadku
    // pervaya zagadka shifr cezara
    if (mutex->lvl == 0) {
        SSL_write(mutex->my_ssl, "{\"FROM\":\"PAPA_BOT\",\"MESS\":\"TASK C.: Khoor, Zruog! Dqg Zhofrph wr rxu fkdw!\",\"TYPE\":\"text\"\n}", 77);
    }

}

static void command_false(t_use_mutex *mutex) {
    // commanda ne izvestna
    // write(mutex->cli_fd, "Chto eto za slovo?", 18);
    SSL_write(mutex->my_ssl, "{\"FROM\":\"PAPA_BOT\",\"MESS\":\"Chto eto za slovo?\",\"TYPE\":\"text\"\n}", 49);
}

void mx_papa_bot(cJSON *MESS, t_use_mutex *mutex) { //vsegda nado budet otpravliat chto oni v etom chate ili tipa togo chtobi pisat im commands
    char *mess = strdup(MESS->valuestring);

    if (strcmp(mess, "./mylvl") == 0)
        mylvl(mutex);
    else if (strcmp(mess, "./start") == 0)
        start(mutex);
    else if (strncmp(mess, "./answer:", 9) == 0) 
        mx_answers_papa(mutex, mess);
    else if (strcmp(mess, "./random_user") == 0)
        mx_random_user(mutex);
    else 
        command_false(mutex);
}


