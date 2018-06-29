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

void sendMessage(int idToSend, char* message) {
	send(idToSend, message, sizeof(message), 0);
}

int waitMessage(int idFrom, char* var) {
	memset(var, 0, sizeof(var));

	int result = read(idFrom, var, sizeof(var));
	printf("%s", var);

	return result;
}

void writeMessage(char* message) {
	scanf("%[^\n]%*c", message);
}

bool is_remote_cmd(char* cmd) {
	return !strcmp(cmd, "rls") || !strcmp(cmd, "rpwd") || !strcmp(cmd, "rcd") || !strcmp(cmd, "upld") || !strcmp(cmd, "downl");
}
