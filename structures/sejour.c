#include <stdio.h>
#include "emplacement.h"

int lectureSejours() {
	int nbSejours = 0;
	FILE *fSejour;
	fSejour = fopen("data/sejour.dat", "r");
	while(!feof(fSejour)) {
		fscanf("");
	}
	return nbSejours;
}

void afficherListeSejours() {
	system("cls"); // on vide la console
	printf("==========================================================\n");
	printf("%s", Accent("================= Liste des séjours ======================\n"));
	printf("==========================================================\n");
	printf("%d", lectureSejours());
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
