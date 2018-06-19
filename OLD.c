#include <stdio.h>
#include <netdb.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "functions_global.h"
#include "fClient.h"

void exec_local_cmd(char* cmd) {
	if (!strcmp(cmd, "cd")) {
		char path[20];

		printf("Répertoire où se déplacer : ");
		writeMessage(path);

		chdir(path);
	} else if (!strcmp(cmd, "rm")) {
		printf("nom du fichier à supprimer : ");
		writeMessage(cmd);

		if(unlink(cmd) == 0) {
			printf("Fichier %s supprimé !\n", cmd);
		} else {
			printf("Fichier %s non supprimé !\n", cmd);
		}
	} else {
		if (fork() == 0){
			execlp(cmd, cmd, NULL);
		} else{
		    wait(NULL);
		}
	}
}

bool is_locale_cmd(char* cmd) {
	return !strcmp(cmd, "ls") || !strcmp(cmd, "pwd") || !strcmp(cmd, "cd") || !strcmp(cmd, "rm");
}

bool connection_client(int idServeur) {
	int i;
	char waitInput[100];
	char sendInput[100];

	for(i = 0; i < 3; i++) {
		waitMessage(idServeur, waitInput);

		scanf("%[^\n]%*c", sendInput);
		sendMessage(idServeur, sendInput);

		waitMessage(idServeur, waitInput);

		scanf("%[^\n]%*c", sendInput);
		sendMessage(idServeur, sendInput);

		waitMessage(idServeur, waitInput);
		if(!strcmp(waitInput, "\nWELC\n\n")) {
			return true;
		}
	}
	
	return false;
}

