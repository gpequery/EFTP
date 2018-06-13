#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <pthread.h>
#include <stdbool.h>

void *thread_listen_message(void *argument) {
	int *newClientId = argument;

	while(true) {
		char input[100];
		int bytesRead, bytesWritten = 0;

		memset(&input, 0, sizeof(input));
	        bytesRead += recv(*newClientId, (char*)&input, sizeof(input), 0);

		/*close current thread if client exit */
		if(!strcmp(input, "exit")){
			printf("\nEXIT Client : %d\n", *newClientId);
			break;
		} else if (strcmp(input, "")) {
			printf("\nInput : %s\n", input);
		}
	}

	pthread_exit(NULL);
}

void *thread_listen(void *argument) {
	int *socketId = argument;

	while(true) {
        	struct sockaddr_in newSockAddr;
                socklen_t newSockAddrSize = sizeof(newSockAddr);

                int newClientId = accept(*socketId, (struct sockaddr *)&newSockAddr, &newSockAddrSize);

		/* If connection, add one client and save clientId. Add new thread for each new client to listen his message */
                if(newClientId < 0){
                        printf("\nErreur tentative de connexion !\n");
                } else {
			printf("\nTentative de connexion clientId %d : \n", newClientId);

			/* Thread Listen connection create */
			pthread_t threadListenMessage;
			if (pthread_create(&threadListenMessage, NULL, thread_listen_message, &newClientId)) {
				printf("pthread_create thread_listen_message");
			}
		}
	}

	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	printf("------------ Serveur ------------\n\n");

	const int port = argc >= 2 ? atoi(argv[1]) : 5001;

	int socketId = socket(AF_INET, SOCK_STREAM, 0);
	if(socketId < 0) {
		printf("\nErreur initialisation serveur\n");
		return EXIT_FAILURE;
	}

	struct sockaddr_in addr;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	int socketStatus = bind(socketId, (struct sockaddr*)&addr, sizeof(addr));
	if(socketStatus < 0) {
		printf("\nErreur status adresse\n");
		return EXIT_FAILURE;
	}

	if (listen(socketId, 100) < 0) {
        	printf("\nErreur d'écoute\n");
        	return EXIT_FAILURE;
    	}

	printf("Serveur initialisé sur le port : %d", port);

	/* Thread Listen connection create */
	pthread_t threadListen;
	if (pthread_create(&threadListen, NULL, thread_listen, &socketId)) {
		perror("pthread_create thread_listen");
		return EXIT_FAILURE;
	}

	/* Thread Listen connection wait */
	if (pthread_join(threadListen, NULL)) {
		perror("pthread_join thread_listen");
		return EXIT_FAILURE;
	}

	printf("\n------------ END ------------\n");
	return EXIT_SUCCESS;
}
