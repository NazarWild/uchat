#include "../inc/uchat.h"

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char *new = (char *) data;

    new = strdup(argv[0]);
    return 0;
}

static bool same_login(char *login) {
    char *str = NULL;
    char *same_login = NULL;

    asprintf(&str, "persons_id where login = '%s'", login);
    mx_select("login", str, callback_persons_id, same_login);
    if (same_login == NULL) {
        free(str);
        return true;
    }
    free(same_login);
    free(str);
    return false;
}

void mx_creating(cJSON* root, int fd) { //bool
    cJSON* log = cJSON_GetObjectItemCaseSensitive(root, "LOGIN");
    cJSON* pass = cJSON_GetObjectItemCaseSensitive(root, "PASS");
    char *add_this = NULL;
    
    asprintf(&add_this, "'%s', '%s'", log->valuestring, pass->valuestring);
    if (same_login(log->valuestring) == false) {
        write(fd, "PROBLEM WITH LOGIN", 19);
        free(add_this);
        //return false;
    }
    else {
        mx_add_to_table("persons_id", "login, pass", add_this);
        free(add_this);
    }
    //return true;
}
