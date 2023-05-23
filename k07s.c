/*** UDP server program ***/
/* Usage: ./server Port */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define ECHOMAX 32
#define RECVMAX 256

void excep(char *errMsg);
void cutString(char *src, int maxlen,char *dest);

int main(int argc, char *argv[])
{
int sock;
struct sockaddr_in echoServerAddr;
struct sockaddr_in echoClntAddr;
struct hostent *HostInfo;
unsigned int cliAddrLen;
char echoBuffer[ECHOMAX];
char receivBuffer[RECVMAX];
unsigned short echoServerPort;
int recvMsgSize;

	if (argc!=2){
		excep("Usage: ./server port");
	}
	echoServerPort = atoi(argv[1]);
	if ((sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1){
		excep("Failed to make a socket!");
	}

  	if ((HostInfo=gethostbyname("localhost"))==NULL){
    	excep("Failed to find host.\n");
  	}

	memset(&echoServerAddr,0,sizeof(echoServerAddr));
  	echoServerAddr.sin_family = AF_INET;
	echoServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	echoServerAddr.sin_port = htons(echoServerPort);

	if (bind(sock,(struct sockaddr *)&echoServerAddr,sizeof(echoServerAddr)) < 0){
    		excep("bind failed");
  	}

  	for(;;)
	{
		cliAddrLen = sizeof(echoClntAddr);

		if((recvMsgSize = recvfrom(sock,receivBuffer,RECVMAX,0,(struct sockaddr *)&echoClntAddr,&cliAddrLen)) < 0){
			excep("recvfrom(), failed");
		}
		printf("Handling client %s \n",inet_ntoa(echoClntAddr.sin_addr));
		if(recvMsgSize > ECHOMAX){
			cutString(receivBuffer,ECHOMAX,echoBuffer);
			if(sendto(sock,echoBuffer,ECHOMAX,0,(struct sockaddr *)&echoClntAddr,sizeof(echoClntAddr))!=ECHOMAX){
				excep("sendto() failed");
			}
		}else{
			if(sendto(sock,receivBuffer,recvMsgSize,0,(struct sockaddr *)&echoClntAddr,sizeof(echoClntAddr))!=recvMsgSize){
				excep("sendto() failed");
			}
		}
		strcpy(echoBuffer,"");

	}
}

void cutString(char *src, int maxlen,char *dest){
	int len = strlen(src);
	
	if(len > maxlen){
			strncpy(dest,src,maxlen);
	}else{
		strcpy(dest,src);
	}
}

void excep(char *errMsg){
	fprintf(stderr,"%s\n",errMsg);
	exit(1);
}
