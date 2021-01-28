#include "../inc/uchat.h"

static void update1(cJSON *root, t_use_mutex *param) {
    cJSON* theme = cJSON_GetObjectItemCaseSensitive(root, "THEME");
    cJSON* full_name = cJSON_GetObjectItemCaseSensitive(root, "FULLNAME");
    cJSON* date_of_birthd = cJSON_GetObjectItemCaseSensitive(root, "DATE_OF_BIRTHD");
    char *str = NULL;

    asprintf(&str, "full_name WHERE users_id = %d", param->user_id);
    mx_set_value("persons_id", full_name->valuestring, str, param);
    free(str);
    asprintf(&str, "theme WHERE users_id = %d", param->user_id);
    mx_set_value("persons_id", theme->valuestring, str, param);
    asprintf(&str, "date_of_birthd WHERE users_id = %d", param->user_id);
    mx_set_value("persons_id", date_of_birthd->valuestring, str, param);
    free(str);
}

static void photo_upload(int fd, int bytes, t_use_mutex *param) {
    int len = 0;
    char *buff = (char*)malloc(sizeof(char) * bytes);

    while ((len += SSL_read(param->my_ssl, buff, bytes)) < bytes)
        write(fd, buff, bytes);
    free(buff);
} 


static void update_photo(cJSON *root, t_use_mutex *param) {
    cJSON* photo = cJSON_GetObjectItemCaseSensitive(root, "PHOTO");
    cJSON* type = cJSON_GetObjectItemCaseSensitive(root, "TYPE");
    cJSON* bytes = cJSON_GetObjectItemCaseSensitive(root, "BYTES");
    char *str = NULL;
    char *data = mx_itoa(param->user_id);
    int fd;

    asprintf(&str, "photo WHERE users_id = %d", param->user_id);
    mx_set_value("persons_id", data, str, param);
    free(str);
    str = mx_strjoin(data, type->valuestring);
    free(data);
    data = mx_strjoin("server/profile_users/", str);
    fd = open(data, O_RDWR);
    if (fd > 0)
        photo_upload(fd, atoi(bytes->valuestring), param);
    else {
        close(fd);
        fd = open(data, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
        photo_upload(fd, atoi(bytes->valuestring), param);
    }
}

void mx_change_prof(cJSON *root, t_use_mutex *param) {
    cJSON* change_prof = cJSON_GetObjectItemCaseSensitive(root, "CHANGE_PROF");

    if (cJSON_IsTrue(change_prof) == 1) {
        update1(root, param);
        update_photo(root, param);
    }
}
