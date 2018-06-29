compile:
	gcc Mains/client.c Functions/fGlob.c Functions/fClient.c -o client
	gcc Mains/server.c Functions/fGlob.c Functions/fRemo.c -o server
