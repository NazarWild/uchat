#include "../inc/uchat.h"

static void deleteing_request(cJSON *root, use_mutex_t *mutex) {
    cJSON *delete = cJSON_GetObjectItemCaseSensitive(root, "ACCOUNT");
    char *str2 = NULL;

    asprintf(&str2, "login = '%s'", delete->valuestring);
    mx_set_value("persons_id", "pass = 'DELETE'", str2, mutex);
    mx_set_value("persons_id", "login = 'DELETE'", str2, mutex);
    free(str2);
} 

bool mx_delete(int fd, cJSON *root) {
    cJSON *delete = cJSON_GetObjectItemCaseSensitive(root, "DELETE");
    int exit;

    if (cJSON_IsTrue(delete) == 1) {
        //zapros na udalenie danih SQL
        deleteing_request(root);
        write(fd, "Your account was succesful deleted", 35);//pishem chto account udachno udalen
        return true;
    }
    return false;
}
