#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "Headers/fGlob.h"
#include "Headers/fRemo.h"

bool connection_server(int idClient) {
	int i;
	for(i = 0; i < 3; i++) {
		sendMessage(idClient, "\nWHO : ");

		char pseudo[100];
		waitMessage(idClient, pseudo);

		sendMessage(idClient, "PWD : ");

		char pwd[100];
		waitMessage(idClient, pwd);

		if(verify_identifiant(pseudo, pwd)) {
			sendMessage(idClient, "\nWELC\n\n");
			return true;
		} else {
			sendMessage(idClient, "false");
		}
	}

	return false;
}

bool verify_identifiant(char* loginSearch, char* pwdSearch) {
	FILE* file = fopen("account", "r");

	if (file != NULL) {
		char row[100];
		while(fgets(row, 100, file) != NULL) {
			char *login = strtok(row, " ");
			char *pwd = strtok(NULL, "\n");

			if(!strcmp(pwdSearch, pwd)){
				return true;
			}
		}
		fclose(file);
    	}

	return false;
}

void exec_remote_cmd(int clientId, char* cmd) {
	if (!strcmp(cmd, "rls") || !strcmp(cmd, "rpwd")) {
		/* STOCK in FILE */
		int old_stdout = dup(STDOUT_FILENO);
		int file = open("tmp", O_CREAT | O_TRUNC | O_WRONLY, 0644);

		dup2(file, STDOUT_FILENO);

		if (fork() == 0){
			execlp("ls", "ls", NULL);
		} else{
		    wait(NULL);
		}

		dup2(old_stdout, STDOUT_FILENO);

		close(old_stdout);
		close(file);

		/* READ FILE */
		FILE* file_tmp = fopen("tmp", "r");
		char result[1000];
		if (file_tmp != NULL) {
			char row[30];
			char* result;

sendMessage(clientId, "COUCOU COUCOU");
			while(fgets(row, 30, file_tmp) != NULL) {
				char *tmp = strtok(row, "\n");
				if(strcmp(tmp, "tmp")){
						sendMessage(clientId, tmp);
				}
			}

			sendMessage(clientId, "\n");
			fclose(file_tmp);
  	}
		remove("tmp");
	} else if (!strcmp(cmd, "rcd")) {
		char path[20];

		sendMessage(clientId, "PATH : ");
		waitMessage(clientId, path);

		chdir(path);
	} else {
		printf("ELSE");
	}
}
