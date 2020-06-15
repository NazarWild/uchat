#include "../inc/uchat.h"

void mx_sign_in_error(int fd) {
    cJSON *error_object = cJSON_CreateObject();
    cJSON *error = cJSON_CreateFalse();
    char *string = NULL;

    cJSON_AddItemToObject(error_object, "error", error);
    string = cJSON_Print(error_object);
    write(fd, string, strlen(string));
    cJSON_Delete(error_object);
}
