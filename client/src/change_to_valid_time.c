#include "../inc/uchat.h"

char *mx_change_to_valid_time(char *full_time) {
    full_time[19] = '\0';
    return &full_time[4];
}
