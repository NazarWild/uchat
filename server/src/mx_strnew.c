#include "../inc/uchat.h"

char *mx_strnew(const int size) {
	char *buffer = (char*) malloc(size + 1);
	if (buffer == NULL) {
		return NULL;
	}
	for (int i = 0;i < size; i++) {
		buffer[i] = '\0';
	}
	buffer[size] = '\0';

	return buffer;
}
