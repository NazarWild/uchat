#include "../inc/uchat.h"

int mx_len_of_file(char *file) {
    struct stat lt;
    int file_size = 0;

    stat(file, &lt);
    file_size = lt.st_size;
    return file_size;
}

static int size_of_file(cJSON *root, t_use_mutex *mutex) {
    cJSON* USR_ID = cJSON_GetObjectItemCaseSensitive(root, "USR_ID");
    char *request = NULL;
    char *tmp = NULL;
    int a;

    asprintf(&request, "persons_id WHERE users_id = %d", USR_ID->valueint);
    mx_select("photo", request, mx_callback_persons_id, tmp, mutex);
    free(request);
    request = mx_strjoin("file_serv/", tmp);
    free(tmp);
    a = mx_len_of_file(request);
    free(request);
    return a;
}

void mx_prof_photo(cJSON *root, t_use_mutex *mutex) { // перессылка фоток чата
    exit(0);


}
