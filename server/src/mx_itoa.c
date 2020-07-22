#include "../inc/uchat.h"

// static char *cstatic(int buffer, int count, int pow, char *str) {
//     if (buffer > 0 || buffer < 0) {
//         str = mx_strnew(count + 1);
//         for (int i = 0; i < count; i++) {
//             if (buffer < 0) {
//                 str[0] = '-';
//                 buffer = buffer * -1;
//                 count = count + 1;
//                 i++;
//             }
//             str[i] = (char)(buffer / pow + 48);
//             buffer = buffer % pow;
//             pow = pow / 10;
//         }
//     }
//     return str;
// }

// static void func(int number, int count) {
//     while (number != 0) {
//         number = number / 10;
//         count++;
//     }
// }

// char *mx_itoa(int number) {
//     char *str = NULL;
//     int pow = 1;
//     int buffer = number;
//     int count = 0;

//     if (number == 0) {
//         str = "0";
//         return str;
//     }
//     if (number == -2147483648) {
//         str = mx_strnew(11);
//         str = "-2147483648";
//         return str;
//     }
//     func(number, count);
//     for (int i = 0; i < count - 1; i++)
//         pow = pow * 10; 
//     str = cstatic(buffer, count, pow, str);
//     return str;
// }

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
	char *arr = (char*) malloc(sizeof(char) * k);

	for (int i = k - 1; i >= 0; i--) {
		arr[i] = (buff % 10) + 48;
		buff = buff / 10;
		if (ifminus) {
			arr[0] = '-';
		}
	}

	return arr;
}
