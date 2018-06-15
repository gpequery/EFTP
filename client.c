#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdbool.h>
#include <pthread.h>
#include "threads.h"
#include "functions.h"
#include <unistd.h>

/*void *recvmg(void *sock)
{
	int their_sock = *((int *)sock);
	char msg[500];
	int len;
	while((len = recv(their_sock,msg,500,0)) > 0) {
		msg[len] = '\0';
		fputs(msg,stdout);
		memset(msg,'\0',sizeof(msg));
	}
}*/


int main(int argc, char *argv[]) {
	printf("------------ Client ------------\n\n");

	const char* serverIp = argc >= 2 ? argv[1] : "localhost";
	const int port = argc >= 3 ? atoi(argv[2]) : 5001;
	pthread_t recvt;

	int socketId = socket(AF_INET, SOCK_STREAM, 0);
	if(socketId < 0) {
		printf("\nErreur initialisation serveur\n");
		return EXIT_FAILURE;
	}

	int serverId = socket(AF_INET, SOCK_STREAM, 0);
	if(serverId < 0 ) {
		printf("\nErreur status adresse 1\n");
		return EXIT_FAILURE;
	} 

	struct sockaddr_in addr;
	addr.sin_family = AF_INET ;
	addr.sin_addr.s_addr = htonl (INADDR_ANY);
	addr.sin_port = htons ((unsigned short)port);

	printf("Client initialisé sur %s:%d", serverIp, port);
	
	int connectionStatus = connect(serverId, (struct sockaddr*) &addr, sizeof(addr));
	if(connectionStatus < 0) {
		printf("\nErreur tentative de connexion !\n");
		return EXIT_FAILURE;
	}

	printf("\nConnexion avec le serveur réussis !\n");
	
	char input[100];
	scanf("%[^\n]%*c", input);
	sendMessage(serverId, input);

	if(!strcmp(input, "BONJ")){
		if(connection_client(serverId)) {
			printf("WELC\n");
		} else {
			printf("BYE\n");
		}
	} else if (!strcmp(input, "exit")) {
		printf("\nGOOD BYE\n");
	} else {
		printf("\nServer wait BONJ \n");
	}
	/*char msg[500];
	while(fgets(msg,500,stdin) > 0) {
		printf("MESSAGE : %s", msg);
		sendMessage(socketId, msg);
	}*/

	/* Thread Listen message create */
	/*pthread_t threadListenMessage;
	if (pthread_create(&threadListenMessage, NULL, thread_listen_message, &serverId)) {
		printf("pthread_create thread_listen_message");
	}*/

	//pthread_create(&recvt,NULL,recvmg,&socketId);
	//pthread_join(recvt,NULL);
	

	printf("\n------------ END ------------\n");

	close(socketId);
	return EXIT_SUCCESS;
}
