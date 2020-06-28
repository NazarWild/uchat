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
#include "sqlite.h"

#define PORT 6969
#define USERS 200

int main(int argc, char *argv[]);
bool mx_registr(int fd); //server
void mx_sign_in_error(int fd); //server
void mx_creating(cJSON* root, int fd); //server
bool mx_pass_connect(char *login, char *pass);
void mx_send_mess(cJSON *root, int fd);
char *mx_itoa(int number);
void mx_whoonline(int fd);
void mx_papa_bot(cJSON *FROM, cJSON *MESS, int fd);
void mx_delete(int fd, cJSON *root);



#endif
