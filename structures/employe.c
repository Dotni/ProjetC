#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "employe.h"
#include "util.h"

employe *premierEmpl, *courantEmpl, *suivantEmpl, *intercaleEmpl;
int tailleTitreEmploye=106;

void viderEmploye(employe *first){
	// on libère la mémoire allouée pour "vider" la liste des employés
	employe *courant=first;
	while(courant != NULL && courant->nxtEmpl != NULL) {
		suivantEmpl = courant->nxtEmpl;
		free(courant); 
		courant = suivantEmpl;
	}
}

int lectureEmploye() {
	
	int nbEmployes = 1, i;

	viderEmploye(premierEmpl); // on vide la liste au cas où ce ne serait pas la première lecture
	
	FILE *fEmploye; // déclaration du fichier
	fEmploye = fopen("data/employes.dat", "r"); // ouverture du fichier
	
	courantEmpl = malloc(sizeof(employe)); // allocation de mémoire
	premierEmpl = courantEmpl;
	
	while(!feof(fEmploye)) {
		// lecture des données des employés
		fscanf(fEmploye, "%d %29s %29s %5f %d", &courantEmpl->id, &courantEmpl->nom, &courantEmpl->prenom, &courantEmpl->salaireParHeure, &courantEmpl->nbHeures);
		nbEmployes++; // un employé de plus
		suivantEmpl = malloc(sizeof(employe)); // on alloue de la mémoire pour stocker le prochain employé
		courantEmpl->nxtEmpl = suivantEmpl;
   	  	courantEmpl = suivantEmpl;
	}
	
	nbEmployes--; // un employé de trop
	
	courantEmpl = premierEmpl; // on reprend le début de la liste
	for(i = 1 ; i < nbEmployes ; i++) {
		courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employés
	}
	courantEmpl->nxtEmpl = NULL; // le dernier employé n'est pas chaîné
	free(suivantEmpl); // libération de la mémoire non utilisée
	fclose(fEmploye); // fermeture du fichier
	return nbEmployes; 
}

void afficherTitresColonnesEmploye() {
	printf ("%s", Accent("|| ID |             Nom               |             Prénom            | Salaire(euro/h) | Heures prestées ||\n"));
	printf("||----|-------------------------------|-------------------------------|-----------------|-----------------||\n");
}

//affiche un seul employé
void affichageUnEmploye(employe *empl){
	printf("|| %02d | %-29s | %-29s |      %5.2f      |       %3d       ||\n", empl->id,empl->nom,empl->prenom,empl->salaireParHeure,empl->nbHeures);
}

void afficherListeEmploye(){
	int nb, i;
	affichageTitre(Accent("Liste des employés"),tailleTitreEmploye);
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
	
	//création d'un nouvel employé
	employe *tmp;
	tmp = malloc(sizeof(employe));
	
	//on parcourt la liste des employés pour récupérer l'ID du dernier employé
	courantEmpl = premierEmpl;
	for(i = 1 ; i < nb-1 ; i++) {
		courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employés
	}
	tmp->id=courantEmpl->id + 1;
	
	affichageTitre(Accent("Ajout d'un employé"),tailleTitreEmploye);
	printf ("%s", Accent(" Nom de l'employé : "));
	lireString(nom,30);
	strcpy(tmp->nom,nom);
	system("PAUSE");
	
	affichageTitre(Accent("Ajout d'un employé"),tailleTitreEmploye);
	printf ("%s", Accent(" Prenom de l'employé : "));
	lireString(prenom,30);
	strcpy(tmp->prenom,prenom);	
	system("PAUSE");
	
	affichageTitre(Accent("Ajout d'un employé"),tailleTitreEmploye);
	printf ("%s", Accent(" Salaire horaire de l'employé (en euros): "));
	float x = choixReel(0.0,99.99,5);
	tmp->salaireParHeure = x; 
	
	affichageTitre(Accent("Ajout d'un employé"),tailleTitreEmploye);
	printf ("%s", Accent(" Nombre d'heures déja prestées (et pas encore payées) : "));
	tmp->nbHeures = choixEntier(0,999,3);
	
	affichageTitre(Accent("Ajout d'un employé"),tailleTitreEmploye);
	printf ("%s", Accent("Confirmez-vous l'ajout de l'employé suivant?\n\n"));
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
		
		printf ("%s", Accent("Employé ajouté avec succès\n\n"));
		system("PAUSE");
		system("cls");
	}
	else{
		printf ("%s", Accent("Employé non-ajouté\n\n"));
		system("PAUSE");
		system("cls");	
	}
}

void SupprimerEmploye(){
	affichageTitre(Accent("Suppression d'un employé"),tailleTitreEmploye);
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
