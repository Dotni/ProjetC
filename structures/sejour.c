#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sejour.h"
#include "emplacement.h"
#include "util.h"

sejour *premierSejour, *sejourCourant, *sejourSuivant;
char date[11];
int tailleTitreSejour = 50;

void viderSejours(sejour *first){
	// on lib�re la m�moire allou�e pour "vider" la liste des s�jours
	sejour *courant = first;
	while(courant != NULL && courant->nxtSej != NULL) {
		sejourSuivant = courant->nxtSej;
		free(courant); 
		courant = sejourSuivant;
	}
}

int lectureSejours(sejour *sejourCourant) {
	int nbSejours = 1, jour, mois, annee, idSuivant, idEmplacement, i;
	char tmpJour[3], tmpMois[3], tmpAnnee[5], tmpDate[11];
	emplacement *empl;// pour lier l'emplacement du s�jour
	
	viderSejours(premierSejour); // on vide la liste au cas o� ce ne serait pas la premi�re lecture
	
	FILE *fSejour; // d�claration du fichier
	fSejour = fopen("data/sejour.dat", "r"); // ouverture du fichier
	
	sejourCourant = malloc(sizeof(sejour)); // allocation de m�moire
	premierSejour = sejourCourant;
	
	while(!feof(fSejour)) {
		// lecture des donn�es des s�jours
		fscanf(fSejour, "%d %d %d %2d %2d %4d %f %d %d %d", &sejourCourant->id, &sejourCourant->formule, &sejourCourant->nbPersonnes, &jour, &mois, &annee, &sejourCourant->prix, &sejourCourant->idClient, &idSuivant, &idEmplacement);
		empl = getEmplacement(idEmplacement);
		sejourCourant->place = empl;
		// conversion entier -> char pour cr�er la date
		itoa(jour, tmpJour, 10); // on copie tmpJour dans jour, en suivant la base 10
		itoa(mois, tmpMois, 10);
		itoa(annee, tmpAnnee, 10);
		// construction de la date
		strcpy(tmpDate, tmpJour);
		strcat(tmpDate, "/");
		strcat(tmpDate, tmpMois);
		strcat(tmpDate, "/");
		strcat(tmpDate, tmpAnnee);
		strcpy(sejourCourant->date, tmpDate); // on l'ajoute dans la structure s�jour
		nbSejours++; // un s�jour de plus
		sejourSuivant = malloc(sizeof(sejour)); // on alloue de la m�moire pour stocker le prochain s�jour
		sejourCourant->nxtSej = sejourSuivant;
   	  	sejourCourant = sejourSuivant;
	}
	sejourCourant = premierSejour; // on reprend le d�but de la liste
	for(i = 1 ; i < nbSejours - 1 ; i++) {
		sejourCourant = sejourCourant->nxtSej; // on cha�ne les s�jours
	}
	sejourCourant->nxtSej = NULL; // le dernier s�jour n'est pas cha�n�
	free(sejourSuivant); // lib�ration de la m�moire non utilis�e
	fclose(fSejour); // fermeture du fichier
	return nbSejours - 1; // retrun incorrect, corriger. enfin quand je pourrais compiler
}

void afficherTitresColonnes() {
	printf("| ID | Formule  | Personnes |    Date    |   Prix  |\n");
	printf("||---|----------|-----------|------------|--------||\n");
}

void afficherListeSejours() {
	int nb, i;
	system("cls"); // on vide la console
	affichageTitre(Accent("Liste des s�jours"), tailleTitreSejour);
	nb = lectureSejours(sejourCourant); // lecture des s�jours
	sejourCourant = premierSejour;
	afficherTitresColonnes(); // titres
	// affichage de la liste des s�jours
	for(i = 1 ; i < nb ; i++) {
		printf("|| %d | ", sejourCourant->id);
		affichageTypeEmplacement(sejourCourant->formule);
		printf("    %d     | %s | %06.2f ||\n", sejourCourant->nbPersonnes, sejourCourant->date, sejourCourant->prix);
		sejourCourant = sejourCourant->nxtSej; // on passe au s�jour suivant
	}
	printf("||================================================||\n");
}

void afficherEmplacementsLibres(char date[]) {
	affichageTitre("Emplacements libres", tailleTitreSejour);
}

char* demanderDate() {
	char date[11] = {0};
	int first = 0;
	do {
		if(first == 0) {
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("%s", Accent("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Date recherch�e %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n"));
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			sdl();sdl();
			printf("|| Entrez la date pour laquelle vous rechercher un emplacement (jj/mm/aaaa) : ");
		}
		else {
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||                                                                            Veuillez entrer une date valide !                                                                            ||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			sdl();sdl();
		}
		lireDate(date, 11);
	} while(date == 0);
	afficherEmplacementsLibres(date);
	system("pause");
}

void switchMenuSejour(int choix) {
	switch(choix) {
		case 1:
			// liste des s�jours
			afficherListeSejours();
			system("pause");
			system("cls");
			break;
		case 2: 
			// emplacements libre
			strcpy(date, demanderDate());
			afficherEmplacementsLibres(date);
			system("pause");
			system("cls");
			break;
	}
}
