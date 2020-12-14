#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sejour.h"
#include "emplacement.h"
#include "util.h"

sejour *premierSejour, *sejourCourant, *sejourSuivant;
char date[11];
int tailleTitreSejour = 52, tailleTitreEmplacemement = 63;

sejour *getPremierSej(){
	return premierSejour;
}

int getDernierSej(){
	sejour *sej;
	int nb = lectureSejours(sej),i;
	
	sejourCourant = premierSejour;
	for(i = 1 ; i < nb - 1 ; i++) {
		sejourCourant = sejourCourant->nxtSej; // on passe au s�jour suivant
	}	
	return sejourCourant->id;
}

sejour * getSejour(int id) {
	int i = 1, nb, continuer = 1;
	sejour *sejourReturn;
	nb = lectureSejours(sejourCourant); // lecture des s�jours
	sejourCourant = premierSejour;
	// affichage de la liste des s�jours
	while(i <= nb && continuer == 1) {
		if(id == sejourCourant->id) {
			sejourReturn = sejourCourant;
			continuer = 0;
		}
		else {
			sejourCourant = sejourCourant->nxtSej; // on passe au s�jour suivant
			i++;
		}
	}
	return sejourReturn;
}

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
		int x,paye; //parce  que lecture du type de s�jour bug
		fscanf(fSejour, "%d %d %d %2d %2d %4d %f %d %d %d", &sejourCourant->id, &x, &sejourCourant->nbPersonnes, &jour, &mois, &annee, &sejourCourant->prix, &sejourCourant->idClient, &idEmplacement,&paye);
		empl = getEmplacement(idEmplacement);
		sejourCourant->place = empl;
		sejourCourant->formule=sejourCourant->place->type;
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
		sejourCourant->paye=paye;
		nbSejours++; // un s�jour de plus
		sejourSuivant = malloc(sizeof(sejour)); // on alloue de la m�moire pour stocker le prochain s�jour
		sejourCourant->nxtSej = sejourSuivant;
   	  	sejourCourant = sejourSuivant;
	}
	sejourCourant = premierSejour; // on reprend le d�but de la liste
	for(i = 1 ; i < nbSejours - 1 ; i++) {
		sejourCourant = sejourCourant->nxtSej; 
	}
	sejourCourant->nxtSej = NULL; // le dernier s�jour n'est pas cha�n�
	free(sejourSuivant); // lib�ration de la m�moire non utilis�e
	fclose(fSejour); // fermeture du fichier
	return nbSejours - 1; // retrun incorrect, corriger. enfin quand je pourrais compiler
}

void afficherTitresColonnesSejour() {
	printf("|| ID  | Formule  | Personnes |    Date    |   Prix  |\n");
	printf("||-----|----------|-----------|------------|--------||\n");
}

void afficherUnSejour(sejour *sej){
		printf("|| %03d | ", sej->id);
		affichageTypeEmplacement(sej->formule);
		printf("    %d     | %s | %06.2f ||\n", sej->nbPersonnes, sej->date, sej->prix);
}

void afficherListeSejours() {
	int nb, i;
	system("cls"); // on vide la console
	affichageTitre(Accent("Liste des s�jours"), tailleTitreSejour);
	nb = lectureSejours(sejourCourant); // lecture des s�jours
	sejourCourant = premierSejour;
	afficherTitresColonnesSejour(); // titres
	// affichage de la liste des s�jours
	for(i = 1 ; i < nb ; i++) {
		afficherUnSejour(sejourCourant);
		sejourCourant = sejourCourant->nxtSej; // on passe au s�jour suivant
	}
	printf("||==================================================||\n");
}

void afficherEmplacementsLibres(char date[],int ti) {
	// un emplacement est libre si il n'est pas li� � un s�jour pour la date donn�e ou si il n'est li� � aucun s�jour
	int i, j, nbSej, nbEmpl, afficher;
	int max = 1; // cette variable va placer les indices des emplacements dans le tableau d�di�, elle servira ensuite de limite � la boucle for d'affichage
	emplacement *empl;
	
	nbSej = lectureSejours(sejourCourant); // r�cup�ration du nombre de s�jours
	nbEmpl = lectureEmplacements(); // r�cup�ration du nombre d'emplacements
	
	if(ti == 1){
		affichageTitre("Emplacements libres", tailleTitreEmplacemement);
	}
	
	int listeOccupes[nbEmpl + 1]; // car il y aura forc�ment moins ou autant d'emplacements libres qu'il y a d'emplacements
	memset(listeOccupes, 0, (nbEmpl + 1) * sizeof(listeOccupes[0])); // initialisation du tableau, tout les �l�ments valent 0
	// le tableau va stocker les id des emplacelents libre pour pouvoir les afficher
	
	sejourCourant = premierSejour;
	// affichage de la liste des s�jours
	for(i = 1 ; i < nbSej ; i++) {
		for(j = 1 ; j <= nbEmpl ; j++) {
			empl = getEmplacement(j);
			if(sejourCourant->place->id == empl->id && strcmp(date, sejourCourant->date) == 0) {
				listeOccupes[max] = j;
				max++;
			}
		}
		sejourCourant = sejourCourant->nxtSej; // on passe au s�jour suivant
	}
	max--;
	
	affichageTitreColonnes();
	
	if(max == nbEmpl) { // tout les emplacements sont occup�s
		printf("||                  Pas d'emplacements libres                  ||\n");
	}
	else {
		// affichage des emplacements libres
		for(i = 1 ; i <= nbEmpl ; i++) {
			afficher = 1;
			for(j = 1 ; j <= max ; j++) {
				if(listeOccupes[j] == getEmplacement(i)->id) {
					afficher = 0; // l'emplacement avec l'id j fait partie des emplacements occup�s, on ne l'affche pas
				}
			}
			if(afficher == 1) {
				empl = getEmplacement(i);
				affichageUnEmplacement(empl);
			}
		}
	}
}

void demanderDate() {
	char date[11] = {0};
	int first = 0, ok = 0;
	do {
		if(first == 0) {
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("%s", Accent("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Date recherch�e %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n"));
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
	afficherEmplacementsLibres(date,1);
}

void copierSejour(sejour *sej1, sejour *sej2){
	sej1->id = sej2->id;
	strcpy(sej1->date, sej2->date);
	sej1->formule = sej2->formule;
	sej1->idClient = sej2->idClient;
	sej1->nbPersonnes = sej2->nbPersonnes;
	sej1->prix = sej2->prix;
	sej1->place = sej2->place;
	sej1->paye = sej2->paye;
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
			demanderDate();
			system("pause");
			system("cls");
			break;
	}
}
