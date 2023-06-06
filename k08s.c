#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <signal.h>
#include <errno.h>

#define ECHOMAX 255

void excep(char *errMsg);
void UseIdleTime();
void SIGIOHandler(int signalType);

int sock;

int main(int argc, char *argv[])
{
	struct sockaddr_in echoServerAddr;
	unsigned short echoServPort;
	struct sigaction handler;
	if (argc!=2){
		excep("Usage: ./server port");
	}
	
	echoServPort = atoi(argv[1]);
	
	if ((sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1){
		excep("Failed to make a socket!");
	}

	memset(&echoServerAddr,0,sizeof(echoServerAddr));
  	echoServerAddr.sin_family = AF_INET;
	echoServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	echoServerAddr.sin_port = htons(echoServPort);

	if (bind(sock,(struct sockaddr *)&echoServerAddr,sizeof(echoServerAddr)) <　0){
    		excep("bind failed");
  	}

	handler.sa_handler = SIGIOHandler;
	
	if(sigfillset(&handler.sa_mask) < 0){
		excep("sigfillset() failed");
	}
	
	handler.sa_flags = 0;
	
	if(sigaction(SIGIO,&handler,0) < 0){
		excep("sigaction() failed for SIGIO");
	}
	
	if(fcntl(sock,F_SETOWN,getpid()) < 0){
		excep("Unable to put set process owner to us");
	}
	if(fcntl(sock,F_SETFL,O_NONBLOCK | FASYNC) < 0){
		excep("Unable to put client sock into nonblocking/async mode");
	}

	for(;;)
		UseIdleTime();
}

void UseIdleTime(){
	printf(".\n");
	sleep(3);
}

void SIGIOHandler(int signalType)
{
	struct sockaddr_in echoClntAddr;
	unsigned int clntLen;
	int recvMsgSize;
	char echoBuffer[ECHOMAX];
	
  	do
	{
		clntLen = sizeof(echoClntAddr);

		if((recvMsgSize = recvfrom(sock,echoBuffer,ECHOMAX,0,(struct sockaddr *)&echoClntAddr,&clntLen)) < 0){
			if(errno != EWOULDBLOCK){
				excep("recvfrom() failed");
			}
		}else{
			printf("Handling client %s \n",inet_ntoa(echoClntAddr.sin_addr));
		
			if(sendto(sock,echoBuffer,recvMsgSize,0,(struct sockaddr *)&echoClntAddr,sizeof(echoClntAddr))!=recvMsgSize){
				excep("sendto() failed");
			}
		}
	}while(recvMsgSize >= 0);
}

void excep(char *errMsg){
	fprintf(stderr,"%s\n",errMsg);
	exit(1);
}
