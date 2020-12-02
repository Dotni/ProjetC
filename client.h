#include "sejour.h"

//définition du client
typedef struct client {
	char nom[30];						//nom du client
	char prenom[30];
	struct sejour sej;					//pour la liste chainée des séjours du client
	struct client *nxtClient;			//pour la liste chainée des clients
}client;
