#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

int main(void) {
   int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   char buffer[256];
    
   portno = 6969;
   
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
    
   server = gethostbyname("10.111.8.3");
   
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(portno);
   
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      exit(1);
   }
   
    while(1){
        printf(">");
        bzero(buffer,256);
        fgets(buffer,255,stdin);
        
        n = write(sockfd, buffer, strlen(buffer));
        
        if (n < 0) {
           perror("ERROR writing to socket");
           exit(1);
        }
        
        bzero(buffer,256);
        n = read(sockfd, buffer, 255);
        
        if (n < 0) {
           perror("ERROR reading from socket");
           exit(1);
        }
        printf("%s\n",buffer);
    }
    return 0;
}


