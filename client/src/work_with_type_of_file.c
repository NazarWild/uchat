#include "../inc/uchat.h" 

bool mx_if_photo(char *filename, t_widget_my *widge) {
    char *type = mx_parsing_filename(filename, widge);

    if (strcmp(type, ".png") == 0
        || strcmp(type, ".jpg") == 0
        || strcmp(type, ".jpeg") == 0
        || strcmp(type, ".gif") == 0)
        return true;
    return false;
}

bool mx_if_photo_with_type(char *type, t_widget_my *widge) {

    if (strcmp(type, ".png") == 0
        || strcmp(type, ".jpg") == 0
        || strcmp(type, ".jpeg") == 0
        || strcmp(type, ".gif") == 0)
        return true;
    return false;
}
