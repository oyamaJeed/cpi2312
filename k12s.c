/*** k12s.c ***/
/* HTTP SERVER PART 1                 */
/*     Usage: ./k12s <server port> */

//#include </home/meit2312/cpi2312/TCPEchoServer.h>
#include </home/meit2312/cpi2312/myTCP.h>
#include <pthread.h>

int main(int argc,char *argv[]){
	int servSock;
	int clntSock;
	unsigned short echoServerPort;
	pthread_t threadID;
	struct ThreadArgs *threadArgs;
	
	if(argc != 2){
		fprintf(stderr,"Usage: %s<SERVER PORT> \n",argv[0]);
		exit(1);
	}
	
	echoServerPort = atoi(argv[1]);
	
	servSock = createTCPSvSock(echoServerPort);
	
	for(;;){
		clntSock = acceptTCPConn(servSock);
		
		if((threadArgs = (struct ThreadArgs *)malloc(sizeof(struct ThreadArgs))) == NULL){
			excep("malloc() failed");
		}
		threadArgs -> clSock = clntSock;
		if(pthread_create(&threadID,NULL,threadMain,(void *)threadArgs) != 0){
			excep("pthread_create() failed");
		}
		/*
		char threadIDStr[16];
		numToStr((long int)threadID,threadIDStr,15);
		pr_msg("THREAD ID:",threadIDStr);
		*/
	
	}
	
}

//gcc -shared createTCPSvSock.c acceptTCPConn.c excep.c clHandler.c -fPIC -o libdlink.so
//gcc -o k10s k10s.c -L. -ldlink -pthread

