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
	// on libère la mémoire allouée pour "vider" la liste des séjours
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
	emplacement *empl;// pour lier l'emplacement du séjour
	
	viderSejours(premierSejour); // on vide la liste au cas où ce ne serait pas la première lecture
	
	FILE *fSejour; // déclaration du fichier
	fSejour = fopen("data/sejour.dat", "r"); // ouverture du fichier
	
	sejourCourant = malloc(sizeof(sejour)); // allocation de mémoire
	premierSejour = sejourCourant;
	
	while(!feof(fSejour)) {
		// lecture des données des séjours
		fscanf(fSejour, "%d %d %d %2d %2d %4d %f %d %d %d", &sejourCourant->id, &sejourCourant->formule, &sejourCourant->nbPersonnes, &jour, &mois, &annee, &sejourCourant->prix, &sejourCourant->idClient, &idSuivant, &idEmplacement);
		empl = getEmplacement(idEmplacement);
		sejourCourant->place = empl;
		// conversion entier -> char pour créer la date
		itoa(jour, tmpJour, 10); // on copie tmpJour dans jour, en suivant la base 10
		itoa(mois, tmpMois, 10);
		itoa(annee, tmpAnnee, 10);
		// construction de la date
		strcpy(tmpDate, tmpJour);
		strcat(tmpDate, "/");
		strcat(tmpDate, tmpMois);
		strcat(tmpDate, "/");
		strcat(tmpDate, tmpAnnee);
		strcpy(sejourCourant->date, tmpDate); // on l'ajoute dans la structure séjour
		nbSejours++; // un séjour de plus
		sejourSuivant = malloc(sizeof(sejour)); // on alloue de la mémoire pour stocker le prochain séjour
		sejourCourant->nxtSej = sejourSuivant;
   	  	sejourCourant = sejourSuivant;
	}
	sejourCourant = premierSejour; // on reprend le début de la liste
	for(i = 1 ; i < nbSejours - 1 ; i++) {
		sejourCourant = sejourCourant->nxtSej; // on chaîne les séjours
	}
	sejourCourant->nxtSej = NULL; // le dernier séjour n'est pas chaîné
	free(sejourSuivant); // libération de la mémoire non utilisée
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
	affichageTitre(Accent("Liste des séjours"), tailleTitreSejour);
	nb = lectureSejours(sejourCourant); // lecture des séjours
	sejourCourant = premierSejour;
	afficherTitresColonnes(); // titres
	// affichage de la liste des séjours
	for(i = 1 ; i < nb ; i++) {
		printf("|| %d | ", sejourCourant->id);
		affichageTypeEmplacement(sejourCourant->formule);
		printf("    %d     | %s | %06.2f ||\n", sejourCourant->nbPersonnes, sejourCourant->date, sejourCourant->prix);
		sejourCourant = sejourCourant->nxtSej; // on passe au séjour suivant
	}
	printf("||================================================||\n");
}

void afficherEmplacementsLibres(char date[]) {
	// un emplacement est libre si il n'est pas lié à un séjour pour la date donnée ou si il n'est lié à aucun séjour
	int i, nb;
	
	affichageTitre("Emplacements libres", tailleTitreSejour);
	nb = lectureSejours(sejourCourant); // lecture des séjours
	sejourCourant = premierSejour;
	// affichage de la liste des séjours
	for(i = 1 ; i < nb ; i++) {
		if(strcmp(date, sejourCourant->date) == 0) { // la date correspond
			
		}
		sejourCourant = sejourCourant->nxtSej; // on passe au séjour suivant
	}
	system("pause");
}

void demanderDate() {
	char date[11] = {0};
	int first = 0, ok = 0;
	do {
		if(first == 0) {
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("%s", Accent("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Date recherchée %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n"));
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			sdl();sdl();
			printf("|| Entrez la date pour laquelle vous rechercher un emplacement (jj/mm/aaaa) : ");
			first = 1;
		}
		else {
			system("cls");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||                              Veuillez entrer une date valide !                             ||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			sdl();sdl();
			printf("|| Entrez la date pour laquelle vous rechercher un emplacement (jj/mm/aaaa) : ");
		}
		ok = lireDate(date, 11);
	} while(ok == 0);
	afficherEmplacementsLibres(date);
}

void switchMenuSejour(int choix) {
	switch(choix) {
		case 1:
			// liste des séjours
			afficherListeSejours();
			system("pause");
			system("cls");
			break;
		case 2: 
			// emplacements libre
			demanderDate();
			system("cls");
			break;
	}
}
