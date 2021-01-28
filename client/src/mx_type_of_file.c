#include "../inc/uchat.h" 

char *mx_type_of_file(char *filename, t_widget_my *widge) {
    int i = strlen(filename) - 1;
    int ret;

    for (; filename[i] != '.'; i--) {}
   	ret = i;
    return &filename[ret];
}
