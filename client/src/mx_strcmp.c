#include "../inc/uchat.h"

int mx_strcmp(char *s1, char *s2) {
    int i = 0;

    if (s1 != NULL || s2 != NULL) {
        while (s1[i] && s2[i] && s1[i] == s2[i])
            i++;
        return s1[i] - s2[i];
    }
    return 99999;
}
