#include "../inc/uchat.h"

static void if_registration(cJSON *root) {
    cJSON* reg = cJSON_GetObjectItemCaseSensitive(root, "Registration");

    if (cJSON_IsTrue(reg) == 1) {
        //registr
    } 
}

static bool loging(cJSON *root) {
    cJSON* log = cJSON_GetObjectItemCaseSensitive(root, "Login");
    
    if (cJSON_IsTrue(log) == 1) {
        //vhod if(voshel == true)
        //          return true;
        //      else 
        //          return false
    }
    return false;
}

bool mx_registr(int fd) {
    char buff[1024];
    cJSON* request_json = NULL;

    while(read(fd, buff, 1024) > 0) {
        request_json = cJSON_Parse(buff);
        if_registration(request_json);
        if (loging(request_json) == false) {
            bzero(buff, 1024);
            cJSON_Delete(request_json);
            return false;
        } 
        else {
            bzero(buff, 1024);
            cJSON_Delete(request_json);
            return true;
        }
    }
    return false;
}
