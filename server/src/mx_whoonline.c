#include "../inc/uchat.h"

void online_show(int fd) {
    
}

void mx_whoonline(cJSON *root, int fd) {
    cJSON *WHOONLINE = cJSON_GetObjectItemCaseSensitive(root, "ONLINE");

    if (cJSON_IsTrue(WHOONLINE) == 1) {
        online_show(fd);
    }
}
