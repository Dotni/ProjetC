#include "sejour.h"

//d�finition du client
typedef struct client {
	char nom[30];						//nom du client
	char prenom[30];
	struct sejour sej;					//pour la liste chain�e des s�jours du client
	struct client *nxtClient;			//pour la liste chain�e des clients
}client;
