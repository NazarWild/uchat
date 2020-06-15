#include "../inc/uchat.h"

static void parse_object(cJSON *root) {
    cJSON* FROM = cJSON_GetObjectItemCaseSensitive(root, "FROM");
    cJSON* TO = cJSON_GetObjectItemCaseSensitive(root, "TO");
    cJSON* MESS = cJSON_GetObjectItemCaseSensitive(root, "MESS");

    if (cJSON_IsString(FROM) && (FROM->valuestring != NULL))
        write(1, FROM->valuestring, strlen(FROM->valuestring));
    write(1," ",1);
    if (cJSON_IsString(TO) && (TO->valuestring != NULL))
        write(1, TO->valuestring, strlen(TO->valuestring));
    write(1," ",1);
    if (cJSON_IsString(MESS) && (MESS->valuestring != NULL))
        write(1,  MESS->valuestring,strlen(MESS->valuestring));
    write(1," ",1);
    cJSON_Delete(root);
}

static void *mx_some_sending(void *cli_fd) {
    int fd = *((int *) cli_fd);
    char buff[1024];
    int ret = 0;
    cJSON* request_json = NULL;

    if (mx_registr(fd) == false) {
        mx_sign_in_error(fd);
        pthread_exit(&ret);
        //otpravliaem cJSON chto ne poluchilos voiti i zacrivaem potok
    }
    while(read(fd, buff, 1024) > 0) { 
        //tut budu parsit info from JSON file
        write(1, "THIS SHIT WRITED THIS: ", 24);
        write(1, buff, strlen(buff));
        request_json = cJSON_Parse(buff);
        parse_object(request_json);
        bzero(buff, 1024);
    }
    printf("EXIT FROM THREAD\n");
    pthread_exit(&ret);
}

int main(int argc, char *argv[]) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    int cli_fd;
    int clen = sizeof(cli_addr);
    pthread_t thread;

    if (argc > 1)
        inet_aton(argv[1], &serv_addr.sin_addr);
    else {
        printf("ENTER IP OF SERVER");
        exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("BINDING ERROR");
        exit(2);
    }
    listen(server_fd, USERS);

    while (1) {
        if ((cli_fd = accept(server_fd, (struct sockaddr *) &cli_addr, (socklen_t *) &clen)) < 0) {
            perror("ACCEPTING ERROR");
            exit(3);
        }
        printf("THIS SHIT CONNECTED: %s\n", inet_ntoa(cli_addr.sin_addr));
        if (pthread_create(&thread, NULL, mx_some_sending, (void *) &cli_fd) < 0) {
            perror("CREATING THREAD ERROR");
            exit(2);
        }
    }
    return 0;
}
