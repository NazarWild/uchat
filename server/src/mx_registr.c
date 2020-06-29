#include "../inc/uchat.h"

static void if_registration(cJSON *root, int fd) {
    cJSON* reg = cJSON_GetObjectItemCaseSensitive(root, "REG");
    int ret;

    if (cJSON_IsTrue(reg) == 1) {
        mx_creating(root, fd);
        pthread_exit(&ret);
    } 
}

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

static void set_socket(int fd) {
    char *ita = NULL;
    char *new = NULL;
    char *forb_new = NULL;
    char *users_id = NULL;

    ita = mx_itoa(fd);
    mx_select("users_id", "persons_id", callback_persons_id, users_id);
    mx_add_to_table("sockets", "users_id", users_id);
    asprintf(&new, "socket = %s", ita);
    asprintf(&forb_new, "users_id = '%s'", users_id);
    free(users_id);
    mx_set_value("sockets", new, forb_new);
    free(new);
    free(forb_new);
    free(ita);
}

static bool loging(cJSON *root, int fd) {
    cJSON* log = cJSON_GetObjectItemCaseSensitive(root, "LOGIN");
    cJSON* pass = cJSON_GetObjectItemCaseSensitive(root, "PASS");
    
    if (cJSON_IsString(log) && log->valuestring != NULL 
        && cJSON_IsString(pass) && pass->valuestring != NULL) { 

        write(1, "LOGIN\n" , 7);
        
        if(mx_pass_connect(log->valuestring, pass->valuestring) == true) {
            //set_socket(fd);
            return true; 
        } 
        else  
            return false;
    }
    return false; 
}

bool mx_registr(int fd) {
    char buff[2048];
    cJSON* request_json = NULL;

    if (read(fd, buff, 2048) > 0) { //this while or if i don't know
        request_json = cJSON_Parse(buff);
        if_registration(request_json, fd);
        if (loging(request_json, fd) == false) {
            bzero(buff, 1024);
            write(fd, "-1", 2);
            cJSON_Delete(request_json);
            return false;
        } 
        else {
            bzero(buff, 1024);
            write(fd, "+1", 2);
            cJSON_Delete(request_json);
            return true;
        }
    }
    return false;
}
