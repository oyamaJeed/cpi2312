/*** UDP client echo program ***/
/* Usage: ./client ServerIP EchoWord <EchoPort> */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SENDMAX 128
#define ECHOMAX 32

void excep(char *errMsg);
void cutString(char *src, int maxlen,char *dest);
int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in echoServerAddr;
	struct sockaddr_in fromAddr;
	unsigned int echoServerPort;
	unsigned int fromSize;
	char *servIP;
	char *echoString;
	char echoBuffer[ECHOMAX];
	int echoStringLen;
	int respStringLen;

	if (argc < 3 || argc > 4){
		excep("Usage: ./server ServerIP EchoWord <EchoPort>!\n");
	}
	servIP = argv[1];
	echoString = argv[2];
	echoServerPort = 7;
	if(argc==4){
		echoServerPort = atoi(argv[3]);
	}
	
	if((echoStringLen = strlen(echoString)) > SENDMAX){
		fprintf(stderr,"Send Buffer size is %d\n",SENDMAX);
		exit(1);
	}
	
	if ((sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1){
		excep("Failed to make a socket!\n");
	}

	memset(&echoServerAddr,0,sizeof(echoServerAddr));
	echoServerAddr.sin_family=AF_INET;
	echoServerAddr.sin_port=htons(echoServerPort);
	echoServerAddr.sin_addr.s_addr = inet_addr(argv[1]);

	if(sendto(sock,echoString,echoStringLen,0,(struct sockaddr *)&echoServerAddr,sizeof(echoServerAddr)) != echoStringLen){
		excep("Failed to send !\n");
	}

	fromSize = sizeof(fromAddr);
	if(echoStringLen>ECHOMAX){
		if((respStringLen = recvfrom(sock,echoBuffer,ECHOMAX,0,(struct sockaddr *)&fromAddr,&fromSize)) != ECHOMAX){
			excep("recvfrom() failed");
		}
		echoBuffer[ECHOMAX] = '\0';
	}else{
		if((respStringLen = recvfrom(sock,echoBuffer,ECHOMAX,0,(struct sockaddr *)&fromAddr,&fromSize)) != echoStringLen){
			excep("recvfrom() failed");
		}
		echoBuffer[echoStringLen] = '\0';
	}

	if(echoServerAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr){
		excep("IP mismatch:Echo server and source address differ.");
	}
	printf("echo:%s\n",echoBuffer);

	close(sock);
	exit(0);
}

void excep(char *errMsg){
	fprintf(stderr,"%s\n",errMsg);
	exit(1);
}
