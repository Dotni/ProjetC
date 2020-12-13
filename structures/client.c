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
		printf ("%s", Accent("Client non-ajouté\n\n"));
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
	
	printf ("%s", Accent("Entrez l'id du client que vous voulez sélectionner\n\n"));
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
	
	printf ("%s", Accent("\n\nConfirmez-vous la sélection du client suivant?\n\n"));
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
		printf ("%s", Accent(" Entrez le numéro correspondant à votre choix. \n\n\n"));
		printf ("%s", Accent("  1.  Afficher la liste des séjours du client   \n"));
		printf ("%s", Accent("  2.  Effectuer une nouvelle réservation    \n"));
		printf ("%s", Accent("  3.  Modifier une réservation du client       \n"));
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
	int nb = lectureSejours(courantSej); // lecture des séjours
	int i,j=0,nbSejoursClient=0;
	
	
	courantSej=getPremierSej();
	for(i = 1 ; i < nb ; i++){
		if(courantSej->idClient==cli->id){
			if(nbSejoursClient==0){
				newCourantSej = malloc(sizeof(sejour)); // allocation de mémoire
				firstSej = newCourantSej; //on va copier les valeurs dans une nouvelle liste séparée
				copierSejour(newCourantSej,courantSej);
				newNextSej=malloc(sizeof(sejour));
				newCourantSej->nxtSej = newNextSej;
   	  			newCourantSej = newNextSej;
				nbSejoursClient=1;
			}
			
			else{
				copierSejour(newCourantSej,courantSej);
				newNextSej=malloc(sizeof(sejour));
				newCourantSej->nxtSej = newNextSej;
   	  			newCourantSej = newNextSej;
   	  			nbSejoursClient++;
			}
		}
		courantSej = courantSej->nxtSej;
	}

	courantSej = firstSej; // on reprend le début de la liste
	for(i = 1 ; i <= nbSejoursClient ; i++) {
		courantSej = courantSej->nxtSej ; // on parcourt les employés
	}
	
	courantSej->nxtSej = NULL; // le dernier employé n'est pas chaîné
	free(newNextSej); // libération de la mémoire non utilisée
	
	
	affichageTitre(Accent("Séjours du client"), tailleTitreClient);
	printf("Nom du client :      %s\n",cli->nom);
	printf("Prenom du client :   %s\n\n\n",cli->prenom);
	afficherTitresColonnesSejour();
	courantSej=firstSej; 
	for(i=1;i<=nbSejoursClient;i++){
		afficherUnSejour(courantSej);
		courantSej=courantSej->nxtSej;
	}
	system("PAUSE");
	
}

void nouvelleReservation(client *cli){
	//on récup d'id de choix cli,
	int id = cli->id;
	
	//Récupération de la date 
	char date[11] = {0};
	int first = 0, ok = 0;
	
	affichageTitre(Accent("Ajout d'un séjour"), tailleTitreClient);
	printf("Nom du client :      %s\n",cli->nom);
			printf("Prenom du client :   %s\n\n\n",cli->prenom);
	printf("Entrez la date pour laquelle vous rechercher un emplacement (jj/mm/aaaa) : ");
	ok=1;
	do {
		if(ok == 0) {
			printf("\nVeuillez entrer une date valide ! format : (jj/mm/aaaa)\n");
			printf("Votre date : ");
		}
		ok = lireDate(date, 11);
	} while(ok == 0);

	
	//verification que le client a pas déja réservé a cette date
	
		
	sejour *courantSej, *firstSej, *newCourantSej, *newNextSej;
	int nb = lectureSejours(courantSej); // lecture des séjours
	int i,j=0,nbSejoursClient=0;
	
	
	courantSej=getPremierSej();
	for(i = 1 ; i < nb ; i++){
		if(courantSej->idClient==cli->id){
			if(nbSejoursClient==0){
				newCourantSej = malloc(sizeof(sejour)); // allocation de mémoire
				firstSej = newCourantSej; //on va copier les valeurs dans une nouvelle liste séparée
				copierSejour(newCourantSej,courantSej);
				newNextSej=malloc(sizeof(sejour));
				newCourantSej->nxtSej = newNextSej;
   	  			newCourantSej = newNextSej;
				nbSejoursClient=1;
			}
			
			else{
				copierSejour(newCourantSej,courantSej);
				newNextSej=malloc(sizeof(sejour));
				newCourantSej->nxtSej = newNextSej;
   	  			newCourantSej = newNextSej;
   	  			nbSejoursClient++;
			}
		}
		courantSej = courantSej->nxtSej;
	}
	
	//libération de la mémoire
	courantSej = firstSej; // on reprend le début de la liste
	for(i = 1 ; i <= nbSejoursClient ; i++) {
		courantSej = courantSej->nxtSej ; // on parcourt les employés
	}
	courantSej->nxtSej = NULL; // le dernier employé n'est pas chaîné
	free(newNextSej); // libération de la mémoire non utilisée
	
	
	
	//on parcourt le vecteur pour vérifier si on a pas déja un séjour avec la meme date
	ok=1;
	courantSej = firstSej; // on reprend le début de la liste
	for(i = 1 ; i <= nbSejoursClient ; i++) {
		if(strcmp(courantSej->date,date)==0){
			ok=0;
			break;
		}
		courantSej = courantSej->nxtSej ; // on parcourt les employés
	}

	//pas de séjour réservé a cette date
	if(ok==1){
		//afficher les emplacement dispos a cette date,
		affichageTitre(Accent("Ajout d'un séjour"), tailleTitreClient);
		printf ("%s", Accent("Date sélectionnée : "));
		printf("%s\n",date);
		printf ("%s", Accent("\n\nListe des emplacement disponibles a cette date\n\n"));
		afficherEmplacementsLibres(date,0);
		//choix d'un emplacement
		
		printf ("%s", Accent("\n\nEntrez l'ID de l'emplacement que le client a choisi :\n"));
		
		//récupération de l'ID le plus élevé des emplacements
		int idMax = idMaxEmplacement();
		char tmp[3];		
		i = 0;
		int j,ok,choix;
		do{
			ok=0;
			if(i != 0){
				printf("Veuillez entrer un ID valide! Votre choix : ");
			}
			choix = lire(tmp, 3);
			i++;
			for(j=1;j<=nb;j++){
				if(getEmplacement(j)->id==choix){
					ok=1;
				}
			}
		}while(choix < 1 || choix > idMax || ok==0);
		
		system("cls");
		affichageTitre(Accent("Ajout d'un séjour"), tailleTitreClient);
		printf ("%s", Accent("\nConfirmez-vous la sélection de l'emplacement suivant?\n\n"));
		affichageTitreColonnes();
		affichageUnEmplacement(*getEmplacementId(choix));
		printf("\n\n1 : Non \n");
		printf("2 : Oui \n");
		printf("Votre choix :");
		
		int choix2=choixEntier(1,2,1);
		
		
		
		if(choix2==2){
			//puis entrer les parametres spécifiques
			//nb personnes
			system("cls");
			affichageTitre(Accent("Ajout d'un séjour"), tailleTitreClient);
			printf ("%s", Accent("Indiquez le nombre de personnes pour la réservation\n\n"));
			printf("Votre choix : ");
			
			int nbPersonnes = choixEntier(1,99,2);
			
			sejour *sej,*sejCourant;
			sej = malloc(sizeof(sejour));
			strcpy(sej->date,date);
			sej->id=lectureSejours(sejCourant)+1;
			sej->nxtSej=NULL;
			sej->idClient=cli->id;
			sej->nbPersonnes=nbPersonnes;
			sej->place=getEmplacementId(choix);
			//float x = calculerPrixSejour(sej);
			sej->prix=0.0;
			sej->formule=getEmplacementId(choix)->type;
		
			//puis demande de validation
			
			system("cls");
			affichageTitre(Accent("Ajout d'un séjour"), tailleTitreClient);
			printf ("%s", Accent("\nConfirmez-vous l'ajout du séjour suivant pour "));
			printf("%s %s\n\n",cli->nom,cli->prenom);
			afficherTitresColonnesSejour();
			afficherUnSejour(sej);
			printf("\n\n1 : Non \n");
			printf("2 : Oui \n");
			printf("Votre choix :");
			
			int choix2=choixEntier(1,2,1);
			if(choix2==2){
				
				sejour *courantSej=getPremierSej();

				FILE *fSejour;
				fSejour = fopen("data/sejour.dat", "w");
				
				while(courantSej->nxtSej != NULL){
					// extraction des jours mois et années
					char cJour[3] = {0}, cMois[3] = {0}, cAnnee[5] = {0};
					extraire(0, 1, courantSej->date, cJour);
					extraire(3, 4, courantSej->date, cMois);
					extraire(6, 9, courantSej->date, cAnnee);
					// convertion en entiers pour récupérer les valeurs
					int jour = atoi(cJour);
					int mois = atoi(cMois);
					int annee = atoi(cAnnee);
					
					fprintf(fSejour,"%03d %1d %1d %2d%2d%4d %06.2f %03d %02d\n",
					courantSej->id,courantSej->formule,courantSej->nbPersonnes, 
					jour, mois, annee, 
					courantSej->prix, courantSej->idClient, courantSej->place->id);
					courantSej = courantSej->nxtSej;
				}
				courantSej->nxtSej=sej;
				fclose(fSejour);
				
				
				system("cls");
				affichageTitre(Accent("Ajout d'un séjour"), tailleTitreClient);
				printf ("%s", Accent("Ajout effectué!\n"));
				system("PAUSE");
				system("cls");	
			}
			else{
				system("cls");
				affichageTitre(Accent("Ajout d'un séjour"), tailleTitreClient);
				printf ("%s", Accent("Annulation!\n"));
				system("PAUSE");
				system("cls");
			}
			
		}
		else{
			system("cls");
			affichageTitre(Accent("Ajout d'un séjour"), tailleTitreClient);
			printf ("%s", Accent("Annulation!\n"));
			system("PAUSE");
			system("cls");
		}
	}
	else{//déja un séjour réservé a cette date
		system("cls");
		affichageTitre(Accent("Ajout d'un séjour"), tailleTitreClient);
		printf ("%s", Accent("Ce client a déjà réservé un séjour a cette date!\n"));
		afficherTitresColonnesSejour();
		afficherUnSejour(courantSej);
		system("PAUSE");
		system("cls");
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
						//afficher les réservations du client
						afficherReservation(choixCli);
						break;
					case 2 :
						//effectuer une nouvelle réservation
						nouvelleReservation(choixCli);
						break;
					case 3 :
						//modifier une réservation
						break;
					case 4 :
						//payer soit une soit toutes les réservations
						break;
				}
			}while(choix2!=5);
			break;	
	}
}
