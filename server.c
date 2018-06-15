#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <pthread.h>
#include "threads.h"

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


	/* Thread Listen connection create */
	pthread_t threadListenConnection;
	if (pthread_create(&threadListenConnection, NULL, thread_listen_connection, &socketId)) {
		perror("pthread_create thread_listen_connection");
		return EXIT_FAILURE;
	}

	/* Thread Listen connection wait */
	if (pthread_join(threadListenConnection, NULL)) {
		perror("pthread_join thread_listen");
		return EXIT_FAILURE;
	}

	printf("\n------------ END ------------\n");
	return EXIT_SUCCESS;
}
