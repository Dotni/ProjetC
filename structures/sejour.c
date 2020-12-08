#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sejour.h"
#include "emplacement.h"
#include "util.h"

sejour *premierSejour, *sejourCourant, *sejourSuivant, *sejourIntercale;
char date[11];

void viderSejours(){
	while(sejourCourant->nxtSej != NULL) {
		sejourCourant->id = 0;
		sejourCourant = sejourCourant->nxtSej;
	}
}

int lectureSejours(sejour *sejourCourant) {
	int nbSejours = 1, jour, mois, annee, idSuivant, idEmplacement, i;
	char tmpJour[3], tmpMois[3], tmpAnnee[5], tmpDate[11];
	emplacement *empl;// pour lier l'emplacement du séjour
	
	viderSejours();
	
	FILE *fSejour;
	fSejour = fopen("data/sejour.dat", "r");
	
	sejourCourant = malloc(sizeof(sejour));
	premierSejour = sejourCourant;
	
	while(!feof(fSejour)) {
		// ignorer le caractère
		fscanf(fSejour, "%d %d %d %2d %2d %4d %f %d %d %d", &sejourCourant->id, &sejourCourant->nbPersonnes, &jour, &mois, &annee, &sejourCourant->prix, &sejourCourant->idClient, &idSuivant, &idEmplacement); 
		empl = getEmplacement(idEmplacement);
		sejourCourant->place = empl;
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

void affichertitresColonnes() {
	printf("| ID | Formule  | Personnes |    Date    |   Prix  |\n");
	printf("||---|----------|-----------|------------|--------||\n");
}

void afficherListeSejours() {
	int nb, i;
	system("cls"); // on vide la console
	printf("====================================================\n");
	printf("%s", Accent("============== Liste des séjours ===================\n"));
	printf("====================================================\n");
	nb = lectureSejours(sejourCourant);
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
}

void afficherEmplacementsLibres(char date[]) {
	printf("liste des emplacements libres pour %s", date);
	/*int nbSej, nbEmpl, i, j;
	emplacement *empl;
	nbSej = lectureSejours(sejourCourant);
	nbEmpl = lectureEmplacements();
	sejourCourant = premierSejour;
	for(i = 1 ; i < nbSej ; i++) {
		for(j = 1 ; j <= nbEmpl ; j++) {
			empl = getEmplacement(j);
			if(sejourCourant->place->id == empl->id) {
				
			}
		}
		sejourCourant = sejourCourant->nxtSej;
	}*/
}

char* demanderDate() {
	char date[11];
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("%s", Accent("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Date recherchée %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n"));
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	sdl();sdl();
	printf("|| Entrez la date pour laquelle vous rechercher un emplacement (jj/mm/aaaa) : ");
	lireDate(date, 12);
	// à faire : variante de lire, adapté pour la date
	// créer fonction vérifier date
	// vérifier
	printf("%s\n", date);
	system("pause");
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
			strcpy(date, demanderDate());
			afficherEmplacementsLibres(date);
			system("pause");
			system("cls");
			break;
	}
}
