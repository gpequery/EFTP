# EFTP

Lancer :
	./server [n°port]
	./client [serverIp n°port]

A SAVOIR
Gestion de paramètres optionnels pour l'adresse IP et le port d'écoute.
Serveur multi thread : Un qui écoute les connections et qui créer un thread d'écoute de message par client (Nombre thread en cours = nbClient + 1)

