#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
	printf("------------ Serveur ------------\n\n");

	const int port = argc >= 2 ? atoi(argv[1]) : 5001;

	int socketId = socket(AF_INET, SOCK_STREAM, 0);
	if(socketId < 0) {
		printf("Erreur initialisation serveur");
		return EXIT_FAILURE;
	}

	struct sockaddr_in addr;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	int socketStatus = bind(socketId, (struct sockaddr*) &addr, sizeof(addr));
	if(socketStatus < 0) {
		printf("Erreur status adresse");
		return EXIT_FAILURE;
	}

	printf("Serveur initialisé sur le port : %d", port);

	printf("\n\n------------ END ------------\n");
	return EXIT_SUCCESS;
}
