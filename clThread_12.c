/*** clThread_12.c ***/

#include "./myTCP.h"

/*** MAIN THREAD ***/
void *threadMain(void *thrArgs) {
	int clSock;	// Socket Descripter for Client
	
	pthread_detach(pthread_self());	// --> release resources
	
	/* ARGUMENT */
	clSock = ((struct ThreadArgs *)thrArgs)->clSock;
	free(thrArgs);
	
	/* HANDLE A CLIENT REQUEST */
	clHandler(clSock);
	return (NULL);
}


/*** HANDLE A CLIENT REQUEST ***/
void clHandler(int clSock)
{
	char buf[BUF_LEN];
	int bytesRcvd;
	char replyBuf[R_BUF_LEN];
	char *bufPtr;
	char *nextPtr;
	int i;
	char str[6];
	int dataSize=0;
	struct httpReqHeader head = {NULL,NULL};
	struct httpReqLine line = {NULL,NULL,NULL};
	
	pr_msg("","");	
	dataSize = recvOneLine(clSock,buf);
	line.method = strtok_re(buf," \t\r\n",&nextPtr);
	pr_msg("METHOD:",line.method);
	line.uri = strtok_re(NULL," \t\r\n",&nextPtr);
	pr_msg("URI:",line.uri);
	line.httpVer = strtok_re(NULL," \t\r\n",&nextPtr);
	pr_msg("HTTP_VER:",line.httpVer);
	
	pr_msg("","");	
	
	for(int i=0;i<HEADERS_MAX;i++){
		dataSize = recvOneLine(clSock,buf);
		numToStr((long int)i, str, 3);
		head.name = strtok_re(buf," \t\r\n",&nextPtr);
		pr_msg("HEAD No.",str);
		head.name = strtok_re(buf," \t\r\n",&nextPtr);
		pr_msg("HEAD.NAME:",head.name);
		head.val = strtok_re(NULL," \t\r\n",&nextPtr);
		pr_msg("HEAD.VAR:",head.val);
		pr_msg("","");
	}
	
	/* CLOSE SOCKET */
	if (shutdown(clSock, 2) == -1) {
		excep("FAIL:shutdown()");
	}
	pr_msg("CONNECTION CLOSED.", "\n");
	close(clSock);

	return;
}

//gcc -shared utils_12.c tcpip_12.c clThread_12.c -fPIC -o libdlink.so
// gcc -o k12s k12s.c -L. -ldlink -pthread

