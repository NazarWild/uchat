#include "../inc/uchat.h"

char *mx_strnew(const int size){
    char *new;

    if (size < 0)
        return NULL;
    new = (char *)malloc(size + 1);
    for (int i = 0; i < size; i++)
        new[i] = '\0';
    new[size] = '\0';
    return new;
}
