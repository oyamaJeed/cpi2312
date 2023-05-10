/*** TCP/IP client program ***/
/* Usage: ./client */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define PORT 50001
#define IP "127.0.0.1"

char RCSIZE=32;


int main(int argc, char *argv[])
{
  struct sockaddr_in ServerAddr;
  struct sockaddr_in ClientAddr;
  struct hostent *HostInfo;
  int ServerSessionID;
  int ClientSessionID;
  int clientlength;

  if (argc!=2){
    fprintf(stderr,"Usage: ./server HostName!\n");
    exit(1);
  }
  
  if ((ServerSessionID=socket(AF_INET,SOCK_STREAM,0))==-1){
    fprintf(stderr, "Failed to make a socket!\n");
    exit(1);
  }
  
  ServerAddr.sin_family=AF_INET;
  ServerAddr.sin_port=htons(PORT);
  ServerAddr.sin_addr.s_addr = inet_addr(IP);

  if(connect(ServerSessionID,(struct sockaddr *)&ServerAddr,sizeof(ServerAddr))==-1){
    fprintf(stderr,"Failed connect\n");
    exit(1);
  }

  char buf[RCSIZE];
  if(recv(ServerSessionID,buf,RCSIZE,0)==-1){
    fprintf(stderr,"Failed recv\n");
  }

  printf("%s",buf);

  if(close(ServerSessionID)==-1){
    fprintf(stderr,"Failed close");
  }
}

