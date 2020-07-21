#include "../inc/uchat.h"

static char *theme_lang(cJSON *root, t_use_mutex *mutex) {
    char *tmp = NULL;
    char *tmp1 = NULL;
    char *request = NULL;
    cJSON* USR_ID = cJSON_GetObjectItemCaseSensitive(root, "USR_ID");

    asprintf(&request, "persons_id WHERE users_id = %d", USR_ID->valueint);
    mx_select("theme", request, mx_callback_persons_id, tmp, mutex);
    mx_select("language", request, mx_callback_persons_id, tmp1, mutex);
    free(request);
    asprintf(&request, "{\"THEME\":\"%s\",\"LANGUAGE\":\"%s\",", tmp, tmp1);
    free(tmp1);
    free(tmp);
    return request;
}

static char *stat_level(cJSON *root, t_use_mutex *mutex) {
    char *tmp = NULL;
    char *tmp1 = NULL;
    char *request = NULL;
    cJSON* USR_ID = cJSON_GetObjectItemCaseSensitive(root, "USR_ID");

    asprintf(&request, "persons_id WHERE users_id = %d", USR_ID->valueint);
    mx_select("status", request, mx_callback_persons_id, tmp, mutex);
    mx_select("level", request, mx_callback_persons_id, tmp1, mutex);
    free(request);
    asprintf(&request, "\"STATUS\":\"%s\",\"LEVEL\":\"%d\",", tmp, atoi(tmp1));
    free(tmp1);
    free(tmp);
    return request;
}

static int photo_usr(cJSON *root, t_use_mutex *mutex) {
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
    return a;
}

static char *date_fullname(cJSON *root, t_use_mutex *mutex) {
    char *tmp = NULL;
    char *tmp1 = NULL;
    char *request = NULL;
    int SIZE_BYTES = photo_usr(root, mutex);
    cJSON* USR_ID = cJSON_GetObjectItemCaseSensitive(root, "USR_ID");

    asprintf(&request, "persons_id WHERE users_id = %d", USR_ID->valueint);
    mx_select("date_of_birthd", request, mx_callback_persons_id, tmp, mutex);
    mx_select("fullname", request, mx_callback_persons_id, tmp1, mutex);
    free(request);
    asprintf(&request, "\"DATE_OF_BIRTH\":%s,\"FULLNAME\":\"%s\",\"PHOTO_SIZE\":%d}\n", tmp, tmp1, SIZE_BYTES);
    free(tmp1);
    free(tmp);
    return request;
}

void mx_usr_prof(cJSON *root, t_use_mutex *mutex) {
    cJSON* USR_PROF = cJSON_GetObjectItemCaseSensitive(root, "USR_PROF");
    char *data = NULL;
    char *tmp = NULL;
    char *tmp1 = NULL;

    if (cJSON_IsTrue(USR_PROF) == 1) {
        data = theme_lang(root, mutex);
        tmp1 = stat_level(root, mutex);
        tmp = mx_strjoin(data, tmp1);
        free(data);
        free(tmp1);
        data = date_fullname(root, mutex);
        tmp1 = mx_strjoin(tmp, data);
        free(data);
        free(tmp);
        SSL_write(mutex->my_ssl, tmp1, strlen(tmp1));
        mx_prof_photo(root, mutex);
    }
}
