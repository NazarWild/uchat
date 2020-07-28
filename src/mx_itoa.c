#include "../inc/uchat.h"

char *mx_itoa(int number) {
    int k = 0;
    int buff = number;
    char *nul = "0";
    int ifminus = 0;
    
    if (number == 0) {
        return nul;
    }
    while(number != 0) {
        number = number / 10;
        k++;
    }
    if (buff < 0) {
        if (buff == -2147483648) {
            return "-2147483648";
        }
        ifminus = 1;
        buff = buff * (-1);
        k++;
    }
    char *arr = mx_strnew(k);//(char*) malloc(sizeof(char) * k);

    for (int i = k - 1; i >= 0; i--) {
        arr[i] = (buff % 10) + 48;
        buff = buff / 10;
        if (ifminus) {
            arr[0] = '-';
        }
    }

    return arr;
}
