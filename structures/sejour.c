#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sejour.h"
#include "emplacement.h"
#include "util.h"

sejour *premierSejour, *sejourCourant, *sejourSuivant;
char date[11];
int tailleTitreSejour = 52, tailleTitreEmplacemement = 63;
const float taxe = 0.4;

sejour *getPremierSej(){
	return premierSejour;
}



sejour * getSejour(int id) {
	int i = 1, nb, continuer = 1;
	sejour *sejourReturn;
	nb = lectureSejours(sejourCourant); // lecture des séjours
	sejourCourant = premierSejour;
	// affichage de la liste des séjours
	while(i <= nb && continuer == 1) {
		if(id == sejourCourant->id) {
			sejourReturn = sejourCourant;
			continuer = 0;
		}
		else {
			sejourCourant = sejourCourant->nxtSej; // on passe au séjour suivant
			i++;
		}
	}
	return sejourReturn;
}

void calculerPrixSejour(int id) {
	sejour *sejACalculer;
	sejACalculer = getSejour(id);
	sejACalculer->prix = sejACalculer->place->prix + taxe;
}

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
		fscanf(fSejour, "%d %d %d %2d %2d %4d %f %d %d %d", 
		&sejourCourant->id, &sejourCourant->formule, &sejourCourant->nbPersonnes, 
		&jour, &mois, &annee, &sejourCourant->prix, &sejourCourant->idClient, &idSuivant, &idEmplacement);
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
		sejourCourant = sejourCourant->nxtSej; 
	}
	sejourCourant->nxtSej = NULL; // le dernier séjour n'est pas chaîné
	free(sejourSuivant); // libération de la mémoire non utilisée
	fclose(fSejour); // fermeture du fichier
	return nbSejours - 1; // retrun incorrect, corriger. enfin quand je pourrais compiler
}

void afficherTitresColonnesSejour() {
	printf("|| ID  | Formule  | Personnes |    Date    |   Prix  |\n");
	printf("||-----|----------|-----------|------------|--------||\n");
}

void afficherUnSejour(sejour *sejourCourant){
		printf("|| %03d | ", sejourCourant->id);
		affichageTypeEmplacement(sejourCourant->formule);
		printf("    %d     | %s | %06.2f ||\n", sejourCourant->nbPersonnes, sejourCourant->date, sejourCourant->prix);
}

void afficherListeSejours() {
	int nb, i;
	system("cls"); // on vide la console
	affichageTitre(Accent("Liste des séjours"), tailleTitreSejour);
	nb = lectureSejours(sejourCourant); // lecture des séjours
	sejourCourant = premierSejour;
	afficherTitresColonnesSejour(); // titres
	// affichage de la liste des séjours
	for(i = 1 ; i < nb ; i++) {
		afficherUnSejour(sejourCourant);
		sejourCourant = sejourCourant->nxtSej; // on passe au séjour suivant
	}
	printf("||==================================================||\n");
}

void afficherEmplacementsLibres(char date[]) {
	
	// un emplacement est libre si il n'est pas lié à un séjour pour la date donnée ou si il n'est lié à aucun séjour
	int i, j, nbSej, nbEmpl, afficher;
	int max = 1; // cette variable va placer les indices des emplacements dans le tableau dédié, elle servira ensuite de limite à la boucle for d'affichage
	emplacement *empl;
	
	affichageTitre("Emplacements libres", tailleTitreEmplacemement);
	nbSej = lectureSejours(sejourCourant); // récupération du nombre de séjours
	nbEmpl = lectureEmplacements(); // récupération du nombre d'emplacements
	
	
	int listeOccupes[nbEmpl + 1]; // car il y aura forcément moins ou autant d'emplacements libres qu'il y a d'emplacements
	memset(listeOccupes, 0, (nbEmpl + 1) * sizeof(listeOccupes[0])); // initialisation du tableau, tout les éléments valent 0
	// le tableau va stocker les id des emplacelents libre pour pouvoir les afficher
	
	sejourCourant = premierSejour;
	// affichage de la liste des séjours
	for(i = 1 ; i < nbSej ; i++) {
		for(j = 1 ; j <= nbEmpl ; j++) {
			empl = getEmplacement(j);
			if(sejourCourant->place->id == empl->id && strcmp(date, sejourCourant->date) == 0) {
				listeOccupes[max] = j;
				max++;
			}
		}
		sejourCourant = sejourCourant->nxtSej; // on passe au séjour suivant
	}
	max--;
	
	affichageTitreColonnes();
	
	if(max == nbEmpl) { // tout les emplacements sont occupés
		printf("||                  Pas d'emplacements libres                  ||\n");
	}
	else {
		// affichage des emplacements libres
		for(i = 1 ; i <= nbEmpl ; i++) {
			afficher = 1;
			for(j = 1 ; j <= max ; j++) {
				if(listeOccupes[j] == getEmplacement(i)->id) {
					afficher = 0; // l'emplacement avec l'id j fait partie des emplacements occupés, on ne l'affche pas
				}
			}
			if(afficher == 1) {
				empl = getEmplacement(i);
				affichageUnEmplacement(empl);
			}
		}
	}
	free(listeOccupes);
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
