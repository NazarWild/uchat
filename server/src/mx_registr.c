#include "../inc/uchat.h"

static void if_registration(cJSON *root, t_use_mutex *mutex) {
    cJSON* reg = cJSON_GetObjectItemCaseSensitive(root, "REG");
    int ret;

    if (cJSON_IsTrue(reg) == 1) {
        mx_creating(root, mutex);
        pthread_exit(&ret);
    } 
}

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

static void set_socket(int fd, char *log, t_use_mutex *mutex) {
    char *ita = NULL;
    char *new = NULL;
    char *users_id = NULL;
    char *level = NULL;
    t_ssl *ssl = (t_ssl *) malloc(sizeof(t_ssl));

    ita = mx_itoa(fd);
    asprintf(&new, "persons_id WHERE login = '%s'", log);
    mx_select("users_id", new, callback_persons_id, &users_id, mutex);
    free(new);
    asprintf(&new, "%s, %i", users_id, mutex->user_id);
    mx_add_to_table("sockets", "users_id, socket", new, mutex);
    mutex->user_id = atoi(users_id);
    free(new);
    asprintf(&new, "persons_id WHERE login = '%s'", log);
    mx_select("level", new, callback_persons_id, &level, mutex);
    mutex->lvl = atoi(level);
    free(new);
    free(ita);
    free(users_id);
    ssl->ssl = mutex->my_ssl;
    ssl->user_id = mutex->user_id;
    pthread_mutex_lock(mutex->mutex);
    mx_push_front(mutex->ssl_list, ssl);
    pthread_mutex_unlock(mutex->mutex);
}

static bool loging(cJSON *root, int fd, t_use_mutex *mutex) {
    cJSON* log = cJSON_GetObjectItemCaseSensitive(root, "LOGIN");
    cJSON* pass = cJSON_GetObjectItemCaseSensitive(root, "PASS");
    char *loggin;

    if (cJSON_IsString(log) && log->valuestring != NULL 
        && cJSON_IsString(pass) && pass->valuestring != NULL) { 
        if(mx_pass_connect(log->valuestring, pass->valuestring, mutex) == true) {
            loggin = mx_parse_str(log->valuestring);
            write(1, "LOGIN\n" , 7);
            set_socket(fd, loggin, mutex);
            free(loggin);
            return true; 
        }
        else
            return false;
    }
    return false;
}

bool mx_registr(t_use_mutex *mutex) {
    char buff[2048];
    cJSON* request_json = NULL;

    if (read(mutex->cli_fd, buff, 2048) > 0) { 
        request_json = cJSON_Parse(buff);
        if_registration(request_json, mutex);
        if (loging(request_json, mutex->cli_fd, mutex) == false) {
            bzero(buff, 2048);
            write(mutex->cli_fd, "-1", 2);
            cJSON_Delete(request_json);
            return false;
        } 
        else {
            bzero(buff, 2048);
            mx_whoonline(mutex);
            cJSON_Delete(request_json);
            return true;
        }
    }
    return false;
}
