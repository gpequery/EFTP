compile:
	gcc client.c fGlob.c fClient.c -o client
	gcc server.c fGlob.c fRemo.c -o server
