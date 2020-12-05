#ifndef CLIENT_H
#define CLIENT_H


//d�finition du client
typedef struct client {
	short id;							//id client
	char nom[30];						//nom du client
	char prenom[30];
	struct sejour *sej;					//pas le choix de mettre un pointeur car la structure sejour n'est pas pleinement d�fine
	struct client *nxtClient;			//pour la liste chain�e des clients
}client;

#endif
