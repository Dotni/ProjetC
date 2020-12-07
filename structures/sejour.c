#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sejour.h"
#include "emplacement.h"

sejour *premierSejour, *sejourCourant, *sejourSuivant, *sejourIntercale;

void viderSejours(){
	printf("sdfg");
}

int lectureSejours(sejour *sejourCourant) {
	int nbSejours = 1, jour, mois, annee, idSuivant, idEmplacement, i;
	char tmpJour[3], tmpMois[3], tmpAnnee[5], tmpDate[11];
	
	FILE *fSejour;
	fSejour = fopen("data/sejour.dat", "r");
	
	sejourCourant = malloc(sizeof(sejour));
	premierSejour = sejourCourant;
	
	while(!feof(fSejour)) {
		fscanf(fSejour, "%d %d %d %2d %2d %4d %f %d %d %d", &sejourCourant->id, &sejourCourant->formule, &sejourCourant->nbPersonnes, &jour, &mois, &annee, &sejourCourant->prix, &sejourCourant->idClient, &idSuivant, &idEmplacement); 
		// conversion entier -> char pour créer la date
		itoa(jour, tmpJour, 10); // on copie tmpJour dans jour, en suivant la base 10
		itoa(mois, tmpMois, 10);
		itoa(annee, tmpAnnee, 10);
		// création de la date
		strcpy(tmpDate, tmpJour);
		strcat(tmpDate, "/");
		strcat(tmpDate, tmpMois);
		strcat(tmpDate, "/");
		strcat(tmpDate, tmpAnnee);
		strcpy(sejourCourant->date, tmpDate);
		nbSejours++;
		sejourSuivant = malloc(sizeof(sejour));
		sejourCourant->nxtSej = sejourSuivant;
   	  	sejourCourant = sejourSuivant;
		// problème de boucle 
	}
	sejourCourant = premierSejour;
	for(i = 1 ; i < nbSejours - 1 ; i++) {
		sejourCourant = sejourCourant->nxtSej;
	}
	sejourCourant->nxtSej = NULL;
	free(sejourSuivant);
	fclose(fSejour);
	return nbSejours - 1; // retrun incorrect, corriger. enfin quand je pourrais compiler
}

void afficherListeSejours() {
	int nb, i;
	system("cls"); // on vide la console
	printf("====================================================\n");
	printf("%s", Accent("============== Liste des séjours ===================\n"));
	printf("====================================================\n");
	printf("| ID | Formule  | Personnes |    Date    |   Prix  |\n");
	printf("||---|----------|-----------|------------|--------||\n");
	nb = lectureSejours(sejourCourant);
	//printf("%d %d %d %s %6.2f\n", sejours[j].id, sejours[j].formule, sejours[j].nbPersonnes, sejours[j].date, sejours[j].prix); 
	sejourCourant = premierSejour;
	for(i = 1 ; i < nb ; i++) {
		printf("|| %d ", sejourCourant->id);
		if(sejourCourant->formule == 1) {
			printf("|   Tente  |");
		}
		else if(sejourCourant->formule == 2) {
			printf("| Caravane |");
		}
		else {
			printf("| Bungalow |");
		}
		printf("     %d     | %s | %06.2f ||\n", sejourCourant->nbPersonnes, sejourCourant->date, sejourCourant->prix);
		sejourCourant = sejourCourant->nxtSej;
	}
	printf("||================================================||\n");
	system("pause");
}

void afficherEmplacementsLibres() {
	printf("liste des emplacements libres");
}

void switchMenuSejour(int choix) {
	switch(choix) {
		case 1:
			// liste des séjours
			afficherListeSejours();
			break;
		case 2: 
			// emplacements libre
			afficherEmplacementsLibres();
			break;
	}
}
