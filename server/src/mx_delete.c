#include "../inc/uchat.h"

static void deleteing_request(cJSON *root, t_use_mutex *mutex) {
    cJSON *delete = cJSON_GetObjectItemCaseSensitive(root, "LOGIN");
    char *str2 = NULL;

    asprintf(&str2, "login = '%s'", delete->valuestring);
    mx_set_value("persons_id", "pass = 'DELETE'", str2, mutex);
    mx_set_value("persons_id", "login = 'DELETE'", str2, mutex);
    write(mutex->fd_log, "LOGIN: ", 8);
    write(mutex->fd_log, delete->valuestring, strlen(delete->valuestring));
    free(str2);
} 

bool mx_delete(t_use_mutex *param, cJSON *root) {
    char *str = cJSON_Print(root);
    cJSON *delete = cJSON_GetObjectItemCaseSensitive(root, "DELETE");
    int exit;

    if (cJSON_IsTrue(delete) == 1) {
        deleteing_request(root, param);
        return true;
    }
    return false;
}
