
/*** TCP/IP server program ***/
/* Usage: ./server HostName */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define BUFSIZE 32

void clHandler(int clSock);
void excep(char *errMsg);

int main(int argc, char *argv[])
{
struct sockaddr_in ServerAddr;
struct sockaddr_in ClientAddr;
struct hostent *HostInfo;
int ServerSessionID;
int ClientSessionID;
int clientlength;
int port = atoi(argv[1]);

	if (argc!=2){
		excep("Usage: ./server port");
		exit(1);
	}

	if ((ServerSessionID=socket(AF_INET,SOCK_STREAM,0))==-1){
		excep("Failed to make a socket!");
		exit(1);
	}

  	if ((HostInfo=gethostbyname("localhost"))==NULL){
    		excep("Failed to find host.\n");
   		exit(1);
  	}

  	ServerAddr.sin_family=AF_INET;
  	ServerAddr.sin_port=htons(port);
  	memcpy((char *)&ServerAddr.sin_addr,(char *)HostInfo->h_addr_list[0],
                                                     HostInfo->h_length);

	if (bind(ServerSessionID,(struct sockaddr *)&ServerAddr,
                                               sizeof(ServerAddr))==-1){
    		excep("Failed to assign a socketname.\n");
   		exit(1);
  	}

  	if (listen(ServerSessionID,5)==-1){
    		excep("Failed to listen.\n");
   		exit(1);
  	}


  	while(1){
    		clientlength=sizeof(ClientAddr);
    		if ((ClientSessionID=accept(ServerSessionID,
                                       (struct sockaddr *)&ClientAddr,
                                       (socklen_t *)&clientlength))==-1){
      		excep("Failed to accept.\n");
    		}

		printf("CONNECTED CLIENT: %s\n",inet_ntoa(ClientAddr.sin_addr));
		clHandler(ClientSessionID);
	}
}

void clHandler(int sock){

	char buf[BUFSIZE];

    	if(recv(sock,buf,BUFSIZE,0)==-1){
      		excep("Failed recv\n");
    	}

    	if (send(sock,buf,sizeof(buf),0)==-1){
      		excep("Failed to send a message.\n");
    	}

    	close(sock);


}

void excep(char *errMsg){
	fprintf(stderr,"%s\n",errMsg);
}
