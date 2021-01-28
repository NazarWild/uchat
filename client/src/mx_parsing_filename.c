#include "../inc/uchat.h" 

char *mx_parsing_filename(char *filename, t_widget_my *widge) {
    int i = strlen(filename) - 1;

    for (; filename[i] != '.'; i--) {}
    widge->int_of_dot = i;
    for (; filename[i] != '/'; i--) {}
    widge->int_of_slesh = i;
    return &filename[widge->int_of_dot];
}
