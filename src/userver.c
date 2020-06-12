#include <stdio.h>  
#include <string.h>   //strlen  
#include <stdlib.h>  
#include <errno.h>  
#include <unistd.h>   //close  
#include <arpa/inet.h>    //close  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <sys/select.h>  

#include <string.h>

void doprocessing (int sock, char *ip);

int main( int argc, char *argv[] ) {
   int sockfd, newsockfd, portno, clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int n, pid;
   
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 6969;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
   
   /* Now start listening for the clients, here
      * process will go in sleep mode and will wait
      * for the incoming connection
   */
   
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   
   while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
        printf("New Connection:%s\n", inet_ntoa(cli_addr.sin_addr));
      if (newsockfd < 0) {
         perror("ERROR on accept");
         exit(1);
      }
      
      /* Create child process */
      pid = fork();
    
      if (pid < 0) {
         perror("ERROR on fork");
         exit(1);
      }
      
      if (pid == 0) {
         /* This is the client process */
         close(sockfd);
         doprocessing(newsockfd, inet_ntoa(cli_addr.sin_addr));
         exit(0);
      }
      else {
         close(newsockfd);
      }
    
   } /* end of while */
}

void doprocessing (int sock, char *ip) {
  int n;
  char buffer[256];
  while(sock > 0) {
      bzero(buffer, 256);
      n = read(sock,buffer,255);
      
      if (n < 0) {
         perror("ERROR reading from socket");
         exit(1);
      }
      char happy[] = { 0xE2, 0x9C, 0x93 };
      printf("socket: %d, ip: %s send: %s\n",sock,ip,buffer);
      n = write(sock,happy,strlen(happy) - 1);
      write(sock,"\n",1);
      
      if (n < 0) {
         perror("ERROR writing to socket");
         exit(1);
      }
  }
}
