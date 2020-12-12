#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "employe.h"
#include "util.h"

employe *premierEmpl, *courantEmpl, *suivantEmpl;
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
	printf("|| %02d | %-29s | %-29s |      %5.2f      |       %3d       ||\n", empl->id, empl->nom, empl->prenom, empl->salaireParHeure, empl->nbHeures);
}

void afficherListeEmploye(){
	int nb, i;
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
	tmp->id = courantEmpl->id + 1;
	
	affichageTitre(Accent("Ajout d'un employ�"), tailleTitreEmploye);
	printf ("%s", Accent(" Nom de l'employ� : "));
	lireString(nom, 30);
	strcpy(tmp->nom, nom);
	
	affichageTitre(Accent("Ajout d'un employ�"), tailleTitreEmploye);
	printf ("%s", Accent(" Prenom de l'employ� : "));
	lireString(prenom, 30);
	strcpy(tmp->prenom, prenom);	
	
	affichageTitre(Accent("Ajout d'un employ�"), tailleTitreEmploye);
	printf ("%s", Accent(" Salaire horaire de l'employ� (en euros): "));
	float x = choixReel(0.0, 99.99, 6);
	tmp->salaireParHeure = x; 
	
	affichageTitre(Accent("Ajout d'un employ�"), tailleTitreEmploye);
	printf ("%s", Accent(" Nombre d'heures d�ja prest�es (et pas encore pay�es) : "));
	tmp->nbHeures = choixEntier(0, 999, 5);
	
	affichageTitre(Accent("Ajout d'un employ�"), tailleTitreEmploye);
	printf ("%s", Accent("Confirmez-vous l'ajout de l'employ� suivant?\n\n"));
	afficherTitresColonnesEmploye(); 
	affichageUnEmploye(tmp);
	printf("\n\n1 : Non \n");
	printf("2 : Oui \n");
	printf("Votre choix :");
	
	int choix=choixEntier(1, 2, 1);	
	
	if(choix == 2){
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

void supprimerEmploye(){
	int nb = lectureEmploye(), i, j, ok, idMax, choix, choix2, choix3;
	char nom[30],prenom[30],tmp[3];
	
	affichageTitre(Accent("Suppression d'un employ�"), tailleTitreEmploye);
	afficherListeEmploye();
	
	printf ("%s", Accent("Entrez l'id de l'employ� que vous souhaitez supprimer.\n\n"));
	printf("Votre choix : ");
		
	courantEmpl = premierEmpl;
	for(i = 1 ; i < nb-1 ; i++) {
		courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employ�s
	}	
	idMax=courantEmpl->id;
	
	i = 0;	
	do{
		ok = 0;
		if(i != 0){
			printf("Veuillez entrer un ID valide! Votre choix : ");
		}
		choix = lire(tmp, 3);
		i++;
		
		courantEmpl = premierEmpl;
		for(j = 1 ; j < nb ; j++){
			if(courantEmpl->id == choix){
				ok = 1;
			}
			courantEmpl = courantEmpl->nxtEmpl;
		}
	}while(choix < 1 || choix > idMax || ok == 0);
	
	affichageTitre(Accent("Suppression d'un employ�"),tailleTitreEmploye);
	afficherTitresColonnesEmploye();
	courantEmpl = premierEmpl;
	for(i = 1 ; i < nb ; i++) {
		if(courantEmpl->id == choix){
			affichageUnEmploye(courantEmpl);
		}
		courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employ�s
	}	
	
	
	printf ("%s", Accent("\n\nConfirmez-vous la suppression de l'employ� suivant?\n\n"));
	printf("\n1 : Non \n");
	printf("2 : Oui \n");
	printf("Votre choix :");
	
	choix2=choixEntier(1, 2, 1);
	
	if(choix2 == 2){
		
		printf ("%s", Accent("\n\nVoulez-vous payer cet employ� avant de le supprimer?\n\n"));
		printf("\n1 : Non \n");
		printf("2 : Oui \n");
		printf("Votre choix :");
		
		choix3=choixEntier(1, 2, 1);
		system("cls");
		
		//paiement de l'employ�
		if(choix3 == 2){
			FILE *fEmploye;
			//on lit le solde du camping
			fEmploye = fopen("data/campingData.dat", "r");
			float caisse;
			fscanf(fEmploye,"%f", &caisse);
			fclose(fEmploye);
			
			//on parcourt les employ�s pour savoir lequel doit etre d�bit�
			courantEmpl = premierEmpl;
			while(courantEmpl->nxtEmpl != NULL){
				if(courantEmpl->id == choix){
					caisse -= courantEmpl->nbHeures * courantEmpl->salaireParHeure;
					courantEmpl->nbHeures = 0;
				}
				courantEmpl = courantEmpl->nxtEmpl;
			}
			
			//on r��crit dans le fichier le solde d�bit�
			fEmploye = fopen("data/campingData.dat", "w");
			fprintf(fEmploye,"%10.2f\n", caisse);
			fclose(fEmploye);
		}
		
		courantEmpl = premierEmpl;
		employe *precedent;
		//on parcourt la liste
		for(j = 1 ; j < nb ; j++){
			//si j>1, il faut "retenir" le pr�c�dent pour savoir d'ou pointer
			if(j > 1){
				
				//on part donc avec un d�calage de 1
				if(j == 2){
					precedent = premierEmpl;
				}
				else{
					precedent = precedent->nxtEmpl;
				}
			}
			
			//si on a trouv� le bon id
			if(courantEmpl->id == choix){
				//si c'est le premier �l�ment de la liste
				if(j == 1){
					premierEmpl = courantEmpl->nxtEmpl;
					free(courantEmpl);
					courantEmpl = premierEmpl;
					break;
				}
				//si c'est le dernier �l�ment de la liste
				else if (courantEmpl->nxtEmpl==NULL){
					precedent->nxtEmpl = NULL;
					free(courantEmpl);
					break;
				}
				//si c'est un �l�ment a l'int�rieur de la liste
				else {
					precedent->nxtEmpl = courantEmpl->nxtEmpl;
					free(courantEmpl);
					break;
				}
			}
			//si on a pas trouv� le bon ID on avance
			else{
				courantEmpl = courantEmpl->nxtEmpl;
			}
		}
		
		affichageTitre(Accent("Suppression d'un employ�"),tailleTitreEmploye);
		afficherTitresColonnesEmploye();
		courantEmpl = premierEmpl;
		while(courantEmpl->nxtEmpl != NULL){
			affichageUnEmploye(courantEmpl);
			courantEmpl = courantEmpl->nxtEmpl;
		}
		
		FILE *fEmploye;
		fEmploye = fopen("data/employes.dat", "w");
		courantEmpl = premierEmpl;
		while(courantEmpl->nxtEmpl != NULL){
			fprintf(fEmploye, "%2d %-29s %-29s %5.2f %03d\n", courantEmpl->id, courantEmpl->nom, courantEmpl->prenom, courantEmpl->salaireParHeure, courantEmpl->nbHeures);
			courantEmpl = courantEmpl->nxtEmpl;
		}
		fclose(fEmploye);
		
		printf ("%s", Accent("Employ� supprim�!\n\n"));
		system("PAUSE");
		system("cls");	
	}	
	else{
		printf ("%s", Accent("Employ� non supprim�\n\n"));
		system("PAUSE");
		system("cls");	
	}
}

void ajouterJourneeTravail(){
	int  nb = lectureEmploye(), i, j, idMax, ok, choix, choix2, nbDemiJournee;
	char tmp[3];
	affichageTitre(Accent("Ajout d'heures de travail � un employ�"), tailleTitreEmploye);
	afficherListeEmploye();
	
	printf ("%s", Accent("Entrez l'id de l'employ� auquel vous souhaitez ajouter des demi-journ�es de travail.\n\n"));
	printf("Votre choix : ");
	
	courantEmpl = premierEmpl;
	for(i = 1 ; i < nb - 1 ; i++) {
		courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employ�s
	}	
	idMax=courantEmpl->id;
	
	i = 0;
	do{
		ok = 0;
		if(i != 0){
			printf("Veuillez entrer un ID valide! Votre choix : ");
		}
		choix = lire(tmp, 3);
		i++;
		
		courantEmpl = premierEmpl;
		for(j = 1 ; j < nb ; j++){
			if(courantEmpl->id == choix){
				ok = 1;
			}
			courantEmpl = courantEmpl->nxtEmpl;
		}
	}while(choix < 1 || choix > idMax || ok == 0);
	
	affichageTitre(Accent("Ajout d'heures de travail � un employ�"), tailleTitreEmploye);
	afficherTitresColonnesEmploye();
	courantEmpl = premierEmpl;
	for(i = 1 ; i < nb ; i++) {
		if(courantEmpl->id == choix){
			affichageUnEmploye(courantEmpl);
			break;
		}
		courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employ�s
	}	
	
	printf ("%s", Accent("\n\nConfirmez-vous le choix de l'employ� suivant?\n\n"));
	printf("\n1 : Non \n");
	printf("2 : Oui \n");
	printf("Votre choix :");
	
	choix2=choixEntier(1, 2, 1);
	
	if(choix2 == 2){
		affichageTitre(Accent("Ajout d'heures de travail � un employ�"), tailleTitreEmploye);
		afficherTitresColonnesEmploye();
		affichageUnEmploye(courantEmpl);
		ok = 0;
		do{
			if(ok > 0){
				printf("\n l'employe aura trop d'heures !");
			}
			printf ("%s", Accent("\n\nCombien de demi-journ�es de travail voulez-vous lui ajouter?\n\n"));
			nbDemiJournee = choixEntier(0, 999, 5);
			ok++;
		}while((nbDemiJournee * 4 + courantEmpl->nbHeures) > 999);
		
		affichageTitre(Accent("Ajout d'heures de travail � un employ�"), tailleTitreEmploye);
		afficherTitresColonnesEmploye();
		affichageUnEmploye(courantEmpl);
		printf ("%s", Accent("\nNombre de demi-journ�es � ajouter : "));
		printf ("%3d", nbDemiJournee);
		
		printf ("%s", Accent("\n\nConfirmez-vous l'ajout de ces demi-journ�es � l'employ� suivant?\n\n"));
		printf("\n1 : Non \n");
		printf("2 : Oui \n");
		printf("Votre choix :");
		choix2=choixEntier(1, 2, 1);
		
		if(choix2 == 2){
			courantEmpl->nbHeures = nbDemiJournee * 4 + courantEmpl->nbHeures;
			FILE *fEmploye;
			fEmploye = fopen("data/employes.dat","w");
			courantEmpl = premierEmpl;
			while(courantEmpl->nxtEmpl != NULL){
				fprintf(fEmploye, "%2d %-29s %-29s %5.2f %03d\n", courantEmpl->id, courantEmpl->nom, courantEmpl->prenom, courantEmpl->salaireParHeure, courantEmpl->nbHeures);
				courantEmpl = courantEmpl->nxtEmpl;
			}
			fclose(fEmploye);
			printf ("%s", Accent("Heures ajout�es!\n\n"));
			system("PAUSE");
			system("cls");
		}
	}
	else{
		printf ("%s", Accent("Ajout d'heures annul�\n\n"));
		system("PAUSE");
		system("cls");	
	}	
}

void modifierSalaire(){
	int  nb = lectureEmploye(), i, j, idMax, ok, choix, choix2, choix3;
	float nSalaire;
	char tmp[3];
	affichageTitre(Accent("Modification du salaire d'un employ�"), tailleTitreEmploye);
	afficherListeEmploye();
	
	printf ("%s", Accent("Entrez l'id de l'employ� dont vous voulez modifier le salaire\n\n"));
	printf("Votre choix : ");
	
	courantEmpl = premierEmpl;
	for(i = 1 ; i < nb - 1 ; i++) {
		courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employ�s
	}	
	idMax=courantEmpl->id;
	
	i = 0;
	do{
		ok = 0;
		if(i != 0){
			printf("Veuillez entrer un ID valide! Votre choix : ");
		}
		choix = lire(tmp, 3);
		i++;
		
		courantEmpl = premierEmpl;
		for(j = 1 ; j < nb ; j++){
			if(courantEmpl->id == choix){
				ok = 1;
			}
			courantEmpl = courantEmpl->nxtEmpl;
		}
	}while(choix < 1 || choix > idMax || ok == 0);
	
	affichageTitre(Accent("Modification du salaire d'un employ�"), tailleTitreEmploye);
	afficherTitresColonnesEmploye();
	courantEmpl = premierEmpl;
	for(i = 1 ; i < nb ; i++) {
		if(courantEmpl->id == choix){
			affichageUnEmploye(courantEmpl);
			break;
		}
		courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employ�s
	}	
	
	printf ("%s", Accent("\n\nConfirmez-vous le choix de l'employ� suivant?\n\n"));
	printf("\n1 : Non \n");
	printf("2 : Oui \n");
	printf("Votre choix :");
	
	choix2=choixEntier(1, 2, 1);
	
	if(choix2 == 2){
		printf ("%s", Accent("\n\nVoulez-vous payer cet employ� avant de modifier son salaire?\n\n"));
		printf("\n1 : Non \n");
		printf("2 : Oui \n");
		printf("Votre choix :");
		
		choix3 = choixEntier(1, 2, 1);
		system("cls");
		
		//paiement de l'employ�
		if(choix3 == 2){
			FILE *fEmploye;
			//on lit le solde du camping
			fEmploye = fopen("data/campingData.dat", "r");
			float caisse;
			fscanf(fEmploye, "%f", &caisse);
			fclose(fEmploye);
			
			//on parcourt les employ�s pour savoir lequel doit etre d�bit�
			courantEmpl = premierEmpl;
			while(courantEmpl->nxtEmpl != NULL){
				if(courantEmpl->id == choix){
					caisse -= courantEmpl->nbHeures * courantEmpl->salaireParHeure;
					courantEmpl->nbHeures = 0;
				}
				courantEmpl = courantEmpl->nxtEmpl;
			}
			
			//on r��crit dans le fichier le solde d�bit�
			fEmploye = fopen("data/campingData.dat", "w");
			fprintf(fEmploye, "%10.2f\n", caisse);
			fclose(fEmploye);
		}
		
		courantEmpl = premierEmpl;
		for(i = 1 ; i < nb ; i++) {
			if(courantEmpl->id == choix){
				affichageUnEmploye(courantEmpl);
				break;
			}
			courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employ�s
		}
		//modification du salaire
		affichageTitre(Accent("Modification du salaire d'un employ�"),tailleTitreEmploye);
		printf ("%s", Accent("Nouveau Salaire horaire de l'employ� (en euros): "));
		float x = choixReel(0.0,99.99,6);
		nSalaire = x; 
		
		affichageTitre(Accent("Modification du salaire d'un employ�"), tailleTitreEmploye);
		afficherTitresColonnesEmploye();
		affichageUnEmploye(courantEmpl);
		printf ("%s", Accent("\nNouveau salaire : "));
		printf ("%5.2f", nSalaire);
		
		printf ("%s", Accent("\n\nConfirmez-vous la modification de salaire suivante?\n\n"));
		printf("\n1 : Non \n");
		printf("2 : Oui \n");
		printf("Votre choix :");
		choix2=choixEntier(1, 2, 1);
		
		if(choix2 == 2){
			courantEmpl->salaireParHeure=nSalaire;
			FILE *fEmploye;
			fEmploye = fopen("data/employes.dat", "w");
			courantEmpl = premierEmpl;
			while(courantEmpl->nxtEmpl != NULL){
				fprintf(fEmploye, "%2d %-29s %-29s %5.2f %03d\n", courantEmpl->id, courantEmpl->nom, courantEmpl->prenom, courantEmpl->salaireParHeure, courantEmpl->nbHeures);
				courantEmpl = courantEmpl->nxtEmpl;
			}
			fclose(fEmploye);
			
			printf ("%s", Accent("Modification effectu�e!\n\n"));
			system("PAUSE");
			system("cls");
		}
	}
	else{
		printf ("%s", Accent("Modification annul�e\n\n"));
		system("PAUSE");
		system("cls");
	}
}

void paiementEmployes(){
	int choix2, i, j, idMax, ok, choix, nb;
	nb = lectureEmploye();
	char tmp[3];
	affichageTitre(Accent("Paiement des employ�s"), tailleTitreEmploye);
	printf ("%s", Accent("\n\nVoulez vous :\n\n"));
	printf ("%s", Accent("\n1 : Payer tous les employ�s \n"));
	printf ("%s", Accent("2 : Payer un employ� sp�cifique \n"));
	printf("Votre choix :");
	choix2=choixEntier(1, 2, 1);
	
	if(choix2 == 1){
		float aDebiter = 0;
		courantEmpl = premierEmpl;
		while(courantEmpl->nxtEmpl!=NULL) {
			aDebiter += courantEmpl->nbHeures * courantEmpl->salaireParHeure;
			courantEmpl->nbHeures = 0;
			courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employ�s
		}
		
		FILE *fEmploye;
		//on lit le solde du camping
		fEmploye = fopen("data/campingData.dat", "r");
		float caisse;
		fscanf(fEmploye, "%f", &caisse);
		fclose(fEmploye);
		
		//on r��crit dans le fichier le solde d�bit�
		fEmploye = fopen("data/campingData.dat", "w");
		fprintf(fEmploye, "%10.2f\n", caisse-aDebiter);
		fclose(fEmploye);
		
		//on r��crit les heures de travail des employ�s
		fEmploye = fopen("data/employes.dat", "w");
		courantEmpl = premierEmpl;
		while(courantEmpl->nxtEmpl != NULL){
			fprintf(fEmploye, "%2d %-29s %-29s %5.2f %03d\n", courantEmpl->id, courantEmpl->nom, courantEmpl->prenom, courantEmpl->salaireParHeure, courantEmpl->nbHeures);
			courantEmpl = courantEmpl->nxtEmpl;
		}
		fclose(fEmploye);
		
		printf ("%s", Accent("Paiement effectu�\n\n"));
		system("PAUSE");
		system("cls");	
	}
	else{
		affichageTitre(Accent("Paiement des employ�s"), tailleTitreEmploye);
		afficherListeEmploye();
		
		printf ("%s", Accent("Entrez l'id de l'employ� dont vous voulez modifier le salaire\n\n"));
		printf("Votre choix : ");
		
		courantEmpl = premierEmpl;
		while(courantEmpl->nxtEmpl != NULL) {
			courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employ�s
		}	
		idMax = courantEmpl->id;
		
		i = 0;	
		do{
			ok = 0;
			if(i != 0){
				printf("Veuillez entrer un ID valide! Votre choix : ");
			}
			choix = lire(tmp, 3);
			i++;
			
			courantEmpl = premierEmpl;
			for(j = 1 ; j < nb ; j++){
				if(courantEmpl->id == choix){
					ok = 1;
				}
				courantEmpl = courantEmpl->nxtEmpl;
			}
		}while(choix < 1 || choix > idMax || ok == 0);
		
		affichageTitre(Accent("Paiement des employ�s"), tailleTitreEmploye);
		afficherTitresColonnesEmploye();
		courantEmpl = premierEmpl;
		for(i = 1 ; i < nb ; i++) {
			if(courantEmpl->id == choix){
				affichageUnEmploye(courantEmpl);
				break;
			}
			courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employ�s
		}	
		
		printf ("%s", Accent("\n\nConfirmez-vous le paiement de l'employ� suivant?\n\n"));
		printf("\n1 : Non \n");
		printf("2 : Oui \n");
		printf("Votre choix :");
		
		choix2=choixEntier(1, 2, 1);
		
		if(choix2 == 2){
			FILE *fEmploye;
			//on lit le solde du camping
			fEmploye = fopen("data/campingData.dat", "r");
			float caisse;
			fscanf(fEmploye, "%f", &caisse);
			fclose(fEmploye);
		
			caisse -= courantEmpl->nbHeures * courantEmpl->salaireParHeure;
			courantEmpl->nbHeures = 0;
			//on r��crit dans le fichier le solde d�bit�
			fEmploye = fopen("data/campingData.dat", "w");
			fprintf(fEmploye, "%10.2f\n", caisse);
			fclose(fEmploye);
			
			fEmploye = fopen("data/employes.dat","w");
			courantEmpl = premierEmpl;
			while(courantEmpl->nxtEmpl != NULL){
				fprintf(fEmploye, "%2d %-29s %-29s %5.2f %03d\n", courantEmpl->id, courantEmpl->nom, courantEmpl->prenom, courantEmpl->salaireParHeure, courantEmpl->nbHeures);
				courantEmpl = courantEmpl->nxtEmpl;
			}
			fclose(fEmploye);
			
			printf ("%s", Accent("Paiement effectu�\n\n"));
			system("PAUSE");
			system("cls");
		}
	}
}

void switchMenuEmploye(int choix){
	switch(choix){
		case 1 : 
			affichageTitre(Accent("Liste des employ�s"), tailleTitreEmploye);
			afficherListeEmploye();
			system("PAUSE");
			system("cls");
			break;
		case 2 :
			ajouterEmploye();
			break;
		case 3:
			supprimerEmploye();
			break;
		case 4:
			ajouterJourneeTravail();
			break;
		case 5:
			modifierSalaire();
			break;
		case 6:
			paiementEmployes();
			break;
	}
}
