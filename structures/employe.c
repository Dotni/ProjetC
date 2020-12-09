#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "employe.h"
#include "util.h"

employe *premierEmpl, *courantEmpl, *suivantEmpl, *intercaleEmpl;
int tailleTitreEmploye=106;

void viderEmploye(employe *first){
	// on lib�re la m�moire allou�e pour "vider" la liste des employ�s
	employe *courant=first;
	while(courant != NULL && courant->nxtEmpl != NULL) {
		suivantEmpl = courant->nxtEmpl;
		free(courant); 
		courant = suivantEmpl;
	}
}

int lectureEmploye() {
	
	int nbEmployes = 1, i;

	viderEmploye(premierEmpl); // on vide la liste au cas o� ce ne serait pas la premi�re lecture
	
	FILE *fEmploye; // d�claration du fichier
	fEmploye = fopen("data/employes.dat", "r"); // ouverture du fichier
	
	courantEmpl = malloc(sizeof(employe)); // allocation de m�moire
	premierEmpl = courantEmpl;
	
	while(!feof(fEmploye)) {
		// lecture des donn�es des employ�s
		fscanf(fEmploye, "%d %29s %29s %5f %d", &courantEmpl->id, &courantEmpl->nom, &courantEmpl->prenom, &courantEmpl->salaireParHeure, &courantEmpl->nbHeures);
		nbEmployes++; // un employ� de plus
		suivantEmpl = malloc(sizeof(employe)); // on alloue de la m�moire pour stocker le prochain employ�
		courantEmpl->nxtEmpl = suivantEmpl;
   	  	courantEmpl = suivantEmpl;
	}
	
	nbEmployes--; // un employ� de trop
	
	courantEmpl = premierEmpl; // on reprend le d�but de la liste
	for(i = 1 ; i < nbEmployes ; i++) {
		courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employ�s
	}
	courantEmpl->nxtEmpl = NULL; // le dernier employ� n'est pas cha�n�
	free(suivantEmpl); // lib�ration de la m�moire non utilis�e
	fclose(fEmploye); // fermeture du fichier
	return nbEmployes; 
}

void afficherTitresColonnesEmploye() {
	printf ("%s", Accent("|| ID |             Nom               |             Pr�nom            | Salaire(euro/h) | Heures prest�es ||\n"));
	printf("||----|-------------------------------|-------------------------------|-----------------|-----------------||\n");
}

//affiche un seul employ�
void affichageUnEmploye(employe *empl){
	printf("|| %02d | %-29s | %-29s |      %5.2f      |       %3d       ||\n", empl->id,empl->nom,empl->prenom,empl->salaireParHeure,empl->nbHeures);
}

void afficherListeEmploye(){
	int nb, i;
	affichageTitre(Accent("Liste des employ�s"),tailleTitreEmploye);
	nb = lectureEmploye(); 
	employe *e = premierEmpl;
	afficherTitresColonnesEmploye(); 
	for(i = 1 ; i < nb ; i++) {
		affichageUnEmploye(e);
		e = e->nxtEmpl; 
	}
	printf("||========================================================================================================||\n");
}

void ajouterEmploye(){
	system("cls");
	int nb = lectureEmploye() , i;
	char nom[30],prenom[30];
	
	//cr�ation d'un nouvel employ�
	employe *tmp;
	tmp = malloc(sizeof(employe));
	
	//on parcourt la liste des employ�s pour r�cup�rer l'ID du dernier employ�
	courantEmpl = premierEmpl;
	for(i = 1 ; i < nb-1 ; i++) {
		courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employ�s
	}
	tmp->id=courantEmpl->id + 1;
	
	affichageTitre(Accent("Ajout d'un employ�"),tailleTitreEmploye);
	printf ("%s", Accent(" Nom de l'employ� : "));
	lireString(nom,30);
	strcpy(tmp->nom,nom);
	system("PAUSE");
	
	affichageTitre(Accent("Ajout d'un employ�"),tailleTitreEmploye);
	printf ("%s", Accent(" Prenom de l'employ� : "));
	lireString(prenom,30);
	strcpy(tmp->prenom,prenom);	
	system("PAUSE");
	
	affichageTitre(Accent("Ajout d'un employ�"),tailleTitreEmploye);
	printf ("%s", Accent(" Salaire horaire de l'employ� (en euros): "));
	float x = choixReel(0.0,99.99,5);
	tmp->salaireParHeure = x; 
	
	affichageTitre(Accent("Ajout d'un employ�"),tailleTitreEmploye);
	printf ("%s", Accent(" Nombre d'heures d�ja prest�es (et pas encore pay�es) : "));
	tmp->nbHeures = choixEntier(0,999,3);
	
	affichageTitre(Accent("Ajout d'un employ�"),tailleTitreEmploye);
	printf ("%s", Accent("Confirmez-vous l'ajout de l'employ� suivant?\n\n"));
	afficherTitresColonnesEmploye(); 
	affichageUnEmploye(tmp);
	printf("\n\n1 : Non \n");
	printf("2 : Oui \n");
	printf("Votre choix :");
	
	int choix=choixEntier(1,2,1);	
	
	if(choix==2){
		tmp->nxtEmpl = NULL;
		courantEmpl->nxtEmpl = tmp;
		nb++;
		
		FILE *fEmploye;
		fEmploye = fopen("data/employes.dat","w");
		courantEmpl = premierEmpl;
		for(i = 1 ; i <nb ; i++){
			fprintf(fEmploye, "%2d %-29s %-29s %5.2f %03d\n", courantEmpl->id, courantEmpl->nom, courantEmpl->prenom, courantEmpl->salaireParHeure, courantEmpl->nbHeures);
			courantEmpl = courantEmpl->nxtEmpl;
		}
		fclose(fEmploye);
		
		printf ("%s", Accent("Employ� ajout� avec succ�s\n\n"));
		system("PAUSE");
		system("cls");
	}
	else{
		printf ("%s", Accent("Employ� non-ajout�\n\n"));
		system("PAUSE");
		system("cls");	
	}
}

void SupprimerEmploye(){
	affichageTitre(Accent("Suppression d'un employ�"),tailleTitreEmploye);
}


void switchMenuEmploye(int choix){
	switch(choix){
		case 1 : 
			afficherListeEmploye();
			system("PAUSE");
			system("cls");
			break;
		case 2 :
			ajouterEmploye();
			break;
		case 3:
		
			break;
		case 4:
		
			break;
		case 5:
		
			break;
		case 6:
		
			break;
	}
}
