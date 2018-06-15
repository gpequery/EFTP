compile:
	gcc client.c threads.c functions.c -o client -lpthread -g
	gcc server.c threads.c functions.c -o server -lpthread -g
