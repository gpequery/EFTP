#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
	printf("------------ Client ------------\n\n");

	const char* serverIp = argc >= 2 ? argv[1] : "localhost";
	const int port = argc >= 3 ? atoi(argv[2]) : 5001;

	int serverId = socket(AF_INET, SOCK_STREAM, 0);
	if(serverId < 0) {
		printf("Erreur initialisation serveur");
		return EXIT_FAILURE;
	}

	int socketId = socket(AF_INET, SOCK_STREAM, 0 );
	if(socketId < 0 ) {
		printf("Erreur status adresse");
		return EXIT_FAILURE;
	} 

	struct sockaddr_in addr;
	int len = sizeof(addr); 
	addr.sin_family = AF_INET ;
	addr.sin_addr.s_addr = htonl (INADDR_ANY);
	addr.sin_port = htons ((unsigned short)port );

	int socketStatus = bind( socketId, (struct sockaddr *)&addr, sizeof(addr));
	if (socketStatus < 0) {
		printf("Erreur status adresse");
		return EXIT_FAILURE;
	}

	printf("Client initialisé sur %s:%d", serverIp, port);


	printf("\n\n------------ END ------------\n");
	return 1;
}
