compile:
	gcc client.c -o client
	gcc server.c thread.c -o server -lpthread -g
