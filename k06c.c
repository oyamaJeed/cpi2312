/*** TCP/IP client program ***/
/* Usage: ./server ServerIP EchoWord <EchoPort> */

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
void excep(char *errMsg);

int main(int argc, char *argv[])
{
	struct sockaddr_in ServerAddr;
	struct hostent *HostInfo;
	int ServerSessionID;
	int port = 50001;

	if (argc < 3 && argc > 4){
		excep("Usage: ./server ServerIP EchoWord <EchoPort>!\n");
		exit(1);
	}
	if(argc==4){
		port = atoi(argv[3]);
	}

	if(sizeof(argv[2]) > 32){
		excep("EchoWord Buffer size is 32");
	}

	if ((ServerSessionID=socket(AF_INET,SOCK_STREAM,0))==-1){
		excep("Failed to make a socket!\n");
		exit(1);
	}

	if ((HostInfo=gethostbyname(argv[1]))==NULL){
		excep("Failed to find host.\n");
		exit(1);
	}

	ServerAddr.sin_family=AF_INET;
	ServerAddr.sin_port=htons(port);
	ServerAddr.sin_addr.s_addr = inet_addr(argv[1]);

	memcpy((char *)&ServerAddr.sin_addr,(char *)HostInfo->h_addr_list[0],
                                                     HostInfo->h_length);


	if(connect(ServerSessionID,(struct sockaddr *)&ServerAddr,sizeof(ServerAddr))==-1){
		excep("Failed connect\n");
		exit(1);
	}

	char buf[BUFSIZE];

	if(send(ServerSessionID,argv[2],BUFSIZE,0) == -1){
		excep("Failed send\n");
		exit(1);
	}

	if(recv(ServerSessionID,buf,BUFSIZE,0)==-1){
		excep("Failed recv\n");
		exit(1);
	}

	printf("RECEIVED MESSAGE: %s\n",buf);

	if(close(ServerSessionID)==-1){
		excep("Failed close");
		exit(1);
	}
}

void excep(char *errMsg){
	fprintf(stderr,"%s\n",errMsg);
}
