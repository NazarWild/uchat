#ifndef UCHAT_H
#define UCHAT_H 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <wchar.h>	
#include <fcntl.h>
#include <stdbool.h>
#include <malloc/malloc.h>
#include "cJSON.h"
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 6969
#define USERS 200

int main(int argc, char *argv[]);
bool mx_registr(int fd); //server
void mx_sign_in_error(int fd); //server



#endif
