#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
	printf("------------ Client ------------\n\n");

	const char* serverIp = argc >= 2 ? argv[1] : "localhost";
	const int port = argc >= 3 ? atoi(argv[2]) : 5001;

	int serverId = socket(AF_INET, SOCK_STREAM, 0);
	if(serverId < 0) {
		printf("\nErreur initialisation serveur\n");
		return EXIT_FAILURE;
	}

	int socketId = socket(AF_INET, SOCK_STREAM, 0);
	if(socketId < 0 ) {
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

	while(true) {
		char input[100];

		printf("\nMessage : ");
		scanf("%[^\n]%*c", input);

		send(serverId, input, sizeof(input), 0);
		if(!strcmp(input, "exit")){
			printf("\nEXIT !!\n");
			break;
		} else {
			printf("\nSend : %s\n", input);
		}
		
	}

	printf("\n------------ END ------------\n");
	return EXIT_SUCCESS;
}
