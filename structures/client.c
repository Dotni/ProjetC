#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sejour.h"
#include "emplacement.h"
#include "client.h"
#include "util.h"

client *premierCli, *courantCli, *suivantCli;
int tailleTitreClient=71;

void viderClient(client *first){
	// on lib�re la m�moire allou�e pour "vider" la liste des clients
	client *courant=first;
	while(courant != NULL && courant->nxtClient != NULL) {
		suivantCli = courant->nxtClient;
		free(courant); 
		courant = suivantCli;
	}
}

int lectureClient() {
	int nbClient = 1, i;

	viderClient(premierCli); // on vide la liste au cas o� ce ne serait pas la premi�re lecture
	
	FILE *fClient; // d�claration du fichier
	fClient = fopen("data/clients.dat", "r"); // ouverture du fichier
	
	courantCli = malloc(sizeof(client)); // allocation de m�moire
	premierCli = courantCli;
	
	while(!feof(fClient)) {
		// lecture des donn�es des employ�s
		fscanf(fClient, "%d %29s %29s", &courantCli->id, &courantCli->nom, &courantCli->prenom);
		nbClient++; // un employ� de plus
		suivantCli = malloc(sizeof(client)); // on alloue de la m�moire pour stocker le prochain
		courantCli->nxtClient = suivantCli;
   	  	courantCli = suivantCli;
	}
	nbClient--; // un client de trop
	
	courantCli = premierCli; // on reprend le d�but de la liste
	for(i = 1 ; i < nbClient ; i++) {
		courantCli = courantCli->nxtClient; // on parcourt la liste
	}
	courantCli->nxtClient = NULL; // le dernier client n'est pas cha�n�
	free(suivantCli); // lib�ration de la m�moire non utilis�e
	fclose(fClient); // fermeture du fichier
	return nbClient; 
}

void afficherTitresColonnesClient() {
	printf ("%s", Accent("|| ID  |             Nom               |             Pr�nom            ||\n"));
	printf("||-----|-------------------------------|-------------------------------||\n");
}

//affiche un seul client
void affichageUnClient(client *cli){
	printf("|| %03d | %-29s | %-29s ||\n", cli->id, cli->nom, cli->prenom);
	}

void afficherListeClient(){
	int nb, i;
	nb = lectureClient(); 
	client *c = premierCli;
	afficherTitresColonnesClient(); 
	for(i = 1 ; i < nb ; i++) {
		affichageUnClient(c);
		c = c->nxtClient; 
	}
	printf("||=====================================================================||\n");
}

void ajouterClient(){
	system("cls");
	int nb = lectureClient() , i;
	char nom[30],prenom[30];
	
	//cr�ation d'un nouvel employ�
	client *tmp;
	tmp = malloc(sizeof(client));
	
	//on parcourt la liste des employ�s pour r�cup�rer l'ID du dernier Client
	courantCli = premierCli;
	for(i = 1 ; i < nb-1 ; i++) {
		courantCli = courantCli->nxtClient; // on parcourt les Clients
	}
	tmp->id = courantCli->id + 1;
	
	affichageTitre(Accent("Ajout d'un client"), tailleTitreClient);
	printf ("%s", Accent(" Nom du client : "));
	lireString(nom, 30);
	strcpy(tmp->nom, nom);
	
	affichageTitre(Accent("Ajout d'un client"), tailleTitreClient);
	printf ("%s", Accent(" Prenom du client : "));
	lireString(prenom, 30);
	strcpy(tmp->prenom, prenom);	
	
	affichageTitre(Accent("Ajout d'un client"), tailleTitreClient);
	printf ("%s", Accent("Confirmez-vous l'ajout du client suivant?\n\n"));
	afficherTitresColonnesClient(); 
	affichageUnClient(tmp);
	printf("\n\n1 : Non \n");
	printf("2 : Oui \n");
	printf("Votre choix :");
	
	int choix=choixEntier(1, 2, 1);	
	
	if(choix == 2){
		tmp->nxtClient = NULL;
		courantCli->nxtClient = tmp;
		nb++;
		
		FILE *fEmploye;
		fEmploye = fopen("data/clients.dat","w");
		courantCli = premierCli;
		for(i = 1 ; i <nb ; i++){
			fprintf(fEmploye, "%03d %-29s %-29s\n", courantCli->id, courantCli->nom, courantCli->prenom);
			courantCli = courantCli->nxtClient;
		}
		fclose(fEmploye);
		
		printf ("%s", Accent("Client ajout� avec succ�s\n\n"));
		system("PAUSE");
		system("cls");
	}
	else{
		printf ("%s", Accent("Employ� non-ajout�\n\n"));
		system("PAUSE");
		system("cls");	
	}
}


client * selectionClient(){
	//on affiche les clients puis on demande a l'utilisateur d'en choisir un 
	
	int nb=lectureClient();
	int i,idMax,ok,j,choix,choix2;
	char tmp[4];
	
	affichageTitre(Accent("Choix du client"), tailleTitreClient);
	afficherListeClient();
	
	courantCli = premierCli;
	for(i = 1 ; i < nb-1 ; i++) {
		courantCli = courantCli->nxtClient; // on parcourt les clients
	}	
	idMax=courantCli->id;
	
	printf ("%s", Accent("Entrez l'id du client que vous voulez s�lectionner\n\n"));
	printf("Votre choix : ");

	i = 0;	
	do{
		ok = 0;
		if(i != 0){
			printf("Veuillez entrer un ID valide! Votre choix : ");
		}
		choix = lire(tmp, 4);
		i++;
		
		courantCli = premierCli;
		for(j = 1 ; j < nb ; j++){
			if(courantCli->id == choix){
				ok = 1;
			}
			courantCli = courantCli->nxtClient;
		}
	}while(choix < 1 || choix > idMax || ok == 0);
	
	affichageTitre(Accent("Choix du client"), tailleTitreClient);
	afficherTitresColonnesClient();
	
	courantCli = premierCli;
	for(i = 1 ; i < nb ; i++) {
		if(courantCli->id == choix){
			affichageUnClient(courantCli);
			break;
		}
		courantCli = courantCli->nxtClient; 
	}	
	
	printf ("%s", Accent("\n\nConfirmez-vous la s�lection du client suivant?\n\n"));
	printf("\n1 : Non \n");
	printf("2 : Oui \n");
	printf("Votre choix :");
	
	choix2=choixEntier(1, 2, 1);

	if(choix2==2){
		return courantCli;
	}
	return NULL;
}


//menu d'action a effectuer sur un client existant
int menuClient2(client *cli){
	int choix = 0;
	short first = 0;
	char tmp[2];
	
	do{
		if(first == 0){
			affichageTitre(Accent("Menu du client"), tailleTitreClient);
			printf("Nom du client :      %s\n",cli->nom);
			printf("Prenom du client :   %s\n\n\n",cli->prenom);
			first=1;	
		}
		else{
			system("cls");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||                              Veuillez entrer un nombre valide!                             ||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
		}
		printf ("%s", Accent(" Entrez le num�ro correspondant � votre choix. \n\n\n"));
		printf ("%s", Accent("  1.  Afficher la liste des s�jours du client   \n"));
		printf ("%s", Accent("  2.  Effectuer une nouvelle r�servation    \n"));
		printf ("%s", Accent("  3.  Modifier une r�servation du client       \n"));
		printf ("%s", Accent("  4.  Paiement du client  \n"));
		printf("  5.  Retour   \n\n");
		printf("  Votre choix :  ");
		choix = lire(tmp, 2);
		
	}while(choix < 1 || choix > 5);
	system("cls");
	return choix;
}	

void afficherReservation(client *cli){
	
	sejour *courantSej, *firstSej, *newCourantSej, *newNextSej;
	int nb = lectureSejours(courantSej); // lecture des s�jours
	int i,j=0,nbSejoursClient=0;
	
	
	courantSej=getPremierSej();
	for(i = 1 ; i < nb ; i++){
		if(courantSej->idClient==cli->id){
			if(nbSejoursClient==0){
				firstSej=courantSej;
				firstSej->nxtSej=newCourantSej;
				nbSejoursClient=1;
			}
			else{
				newCourantSej=courantSej;
				newCourantSej->nxtSej=newNextSej;
				newCourantSej=newNextSej;
			}
		}
		courantSej = courantSej->nxtSej;
	}
	newCourantSej->nxtSej=NULL;
	
	for(i=1;i<nbSejoursClient;i++){
		
	}
	
}



void switchMenuClient(int choix){
	int choix2;
	client *choixCli;
	
	switch(choix){
		case 1 :
			affichageTitre(Accent("Liste des clients"), tailleTitreClient);
			afficherListeClient();
			system("PAUSE");
			system("cls");
			break;
		case 2 : 
			ajouterClient();
			break;
		case 3 :
			choixCli = selectionClient();
			if(choixCli==NULL){
				system("cls");
				break;
			}
			do{
				choix2 =  menuClient2(choixCli);
				switch(choix2){
					case 1 :
						//afficher les r�servations du client
						afficherReservation(choixCli);
						break;
					case 2 :
						//effectuer une nouvelle r�servation
						break;
					case 3 :
						
						break;
					case 4 :
						break;
				}
			}while(choix2!=5);
			break;	
	}
}
