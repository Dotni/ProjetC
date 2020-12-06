#include <stdio.h>
#include <string.h>
#include "sejour.h"
#include "emplacement.h"

void viderSejours(sejour sejours[], int tailleMax){
	int i;
	for (i = 1 ; i < tailleMax ; i++){
		sejours[i].id = 0;
	}
}

int lectureSejours(int tailleMax, sejour sejours[]) {
	printf("test");
	int nbSejours = 1, jour, mois, annee;
	char tmpJour[3], tmpMois[3], tmpAnnee[5], tmpDate[11];
	FILE *fSejour;
	fSejour = fopen("data/sejour.dat", "r");
	while(!feof(fSejour)) {
		fscanf(fSejour, "%3d %1d %1d %2d %2d %4d", &sejours[nbSejours].id, &sejours[nbSejours].formule, &jour, &mois, &annee, &sejours[nbSejours].prix); // a terminer
		// organisation de sejour.dat ? à quoi correspond le 3eme nombre ?
		// conversion entier -> char pour créer la date
		itoa(jour, tmpJour, 10);
		itoa(mois, tmpMois, 10);
		itoa(annee, tmpAnnee, 10);
		// création de la date
		strcpy(tmpDate, tmpJour);
		strcat(tmpDate, "/");
		strcat(tmpDate, tmpMois);
		strcat(tmpDate, "/");
		strcat(tmpDate, tmpAnnee);
		strcpy(sejours[nbSejours].date, tmpDate);
		printf("%s", sejours[nbSejours].date);
		nbSejours++;
		printf("test 2");
		// problème de boucle 
	}
	fclose(fSejour);
	printf("test  3"); // test non atteind
	return nbSejours - 1;
}

void afficherListeSejours(int tailleMax, sejour sejours[]) {
	int i;
	system("cls"); // on vide la console
	printf("==========================================================\n");
	printf("%s", Accent("================= Liste des séjours ======================\n"));
	printf("==========================================================\n");
	i = lectureSejours(tailleMax, sejours);
	printf("%d\n", i);
	system("pause");
}

void afficherEmplacementsLibres() {
	printf("liste des emplacements libres");
}

void switchMenuSejour(int choix, int tailleMax, sejour sejours[]) {
	switch(choix) {
		case 1:
			// liste des séjours
			afficherListeSejours(tailleMax, sejours);
			break;
		case 2: 
			// emplacements libre
			afficherEmplacementsLibres();
			break;
	}
}
