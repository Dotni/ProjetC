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
	printf("test\n");
	int nbSejours = 1, jour, mois, annee, tmp, tmp2;
	char tmpJour[3], tmpMois[3], tmpAnnee[5], tmpDate[11];
	FILE *fSejour;
	fSejour = fopen("data/sejour.dat", "r");
	while(!feof(fSejour)) {
		fscanf(fSejour, "%d %d %d %2d %2d %4d %f %d %d", &sejours[nbSejours].id, &sejours[nbSejours].formule, &sejours[nbSejours].nbPersonnes, &jour, &mois, &annee, &sejours[nbSejours].prix, &tmp, &tmp2); 
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
		printf("%d %d %d %s %6.2f\n", sejours[nbSejours].id, sejours[nbSejours].formule, sejours[nbSejours].nbPersonnes, sejours[nbSejours].date, sejours[nbSejours].prix);
		nbSejours++;
		printf("test 2\n");
		// problème de boucle 
	}
	fclose(fSejour);
	printf("test  3\n"); // test non atteind
	return nbSejours - 2; // scotch de tes morts
}

void afficherListeSejours(int tailleMax, sejour sejours[]) {
	int i, j;
	system("cls"); // on vide la console
	printf("==========================================================\n");
	printf("%s", Accent("================= Liste des séjours ======================\n"));
	printf("==========================================================\n");
	i = lectureSejours(tailleMax, sejours);
	printf("%d\n", i);
	for(j = 1 ; j <= i ; j++) {
		printf("%d %d %d %s %6.2f\n", sejours[j].id, sejours[j].formule, sejours[j].nbPersonnes, sejours[j].date, sejours[j].prix); 
	}
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
