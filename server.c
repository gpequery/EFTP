#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "fGlob.h"
#include "fRemo.h"

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

	printf("\nServeur initialisé : en attente de client\n");

	struct sockaddr_in newSockAddr;
        socklen_t newSockAddrSize = sizeof(newSockAddr);

        int newClientId = true;
        newClientId = accept(socketId, (struct sockaddr *)&newSockAddr, &newSockAddrSize);
	if(newClientId < 0){
                printf("\nErreur tentative de connexion !\n");
		return EXIT_SUCCESS;
        }

	printf("\nClient connecté : %d\n", newClientId);
	char input[100];
	waitMessage(newClientId, input);

	if(!strcmp(input, "BONJ")) {
		if(connection_server(newClientId)) {
			printf("\nClient identifié\n");
			
			char waitInput[100];
			while(1) {
				waitMessage(newClientId, waitInput);
				if(!strcmp(waitInput, "exit")) {
					break;
				} else if(is_remote_cmd(waitInput)) {
					exec_remote_cmd(newClientId, waitInput);
				}
			}
		} else {
			printf("\nClient refusé\n");
		}
	}
	
	printf("\n------------ END ------------\n");

	close(socketId);
	return EXIT_SUCCESS;

	
}
