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
	// on libère la mémoire allouée pour "vider" la liste des clients
	client *courant=first;
	while(courant != NULL && courant->nxtClient != NULL) {
		suivantCli = courant->nxtClient;
		free(courant); 
		courant = suivantCli;
	}
}

int lectureClient() {
	int nbClient = 1, i;

	viderClient(premierCli); // on vide la liste au cas où ce ne serait pas la première lecture
	
	FILE *fClient; // déclaration du fichier
	fClient = fopen("data/clients.dat", "r"); // ouverture du fichier
	
	courantCli = malloc(sizeof(client)); // allocation de mémoire
	premierCli = courantCli;
	
	while(!feof(fClient)) {
		// lecture des données des employés
		fscanf(fClient, "%d %29s %29s", &courantCli->id, &courantCli->nom, &courantCli->prenom);
		nbClient++; // un employé de plus
		suivantCli = malloc(sizeof(client)); // on alloue de la mémoire pour stocker le prochain
		courantCli->nxtClient = suivantCli;
   	  	courantCli = suivantCli;
	}
	nbClient--; // un client de trop
	
	courantCli = premierCli; // on reprend le début de la liste
	for(i = 1 ; i < nbClient ; i++) {
		courantCli = courantCli->nxtClient; // on parcourt la liste
	}
	courantCli->nxtClient = NULL; // le dernier client n'est pas chaîné
	free(suivantCli); // libération de la mémoire non utilisée
	fclose(fClient); // fermeture du fichier
	return nbClient; 
}

void afficherTitresColonnesClient() {
	printf ("%s", Accent("|| ID  |             Nom               |             Prénom            ||\n"));
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
	
	//création d'un nouvel employé
	client *tmp;
	tmp = malloc(sizeof(client));
	
	//on parcourt la liste des employés pour récupérer l'ID du dernier Client
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
		
		printf ("%s", Accent("Client ajouté avec succès\n\n"));
		system("PAUSE");
		system("cls");
	}
	else{
		printf ("%s", Accent("Employé non-ajouté\n\n"));
		system("PAUSE");
		system("cls");	
	}
}


int selectionClient(){
	
	//on affiche les clients puis on demande a l'utilisateur d'en choisir un 
	int choix = 0;
	return choix;
}


//menu d'action a effectuer sur un client existant
int menuClient2(){
	
	//on affiche les clients puis on demande a l'utilisateur d'en choisir un 
	int choix = 0;
	return choix;
}	





void switchMenuClient(int choix){
	int choixCli,choix2;
	
	switch(choix){
		case 1 :
			affichageTitre(Accent("Liste des clients"), tailleTitreClient);
			afficherListeClient();
			system("PAUSE");
			system("cls");
			break;
		case 2 : 
			//ajout d'un client
			ajouterClient();
			break;
		case 3 :
			choixCli = selectionClient();
			choix2 =  menuClient2();
			switch(choix2){
				case 1 :
					//afficher les réservations du client
					break;
				case 2 :
					//effectuer une nouvelle réservation
					break;
				case 3 :
					
					break;
				case 4 :
					break;
			}
			break;
	}
}
