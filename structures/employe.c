#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "employe.h"
#include "util.h"

employe *premierEmpl, *courantEmpl, *suivantEmpl;
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
	
	//création d'un nouvel employé
	employe *tmp;
	tmp = malloc(sizeof(employe));
	
	//on parcourt la liste des employés pour récupérer l'ID du dernier employé
	courantEmpl = premierEmpl;
	for(i = 1 ; i < nb-1 ; i++) {
		courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employés
	}
	tmp->id = courantEmpl->id + 1;
	
	affichageTitre(Accent("Ajout d'un employé"), tailleTitreEmploye);
	printf ("%s", Accent(" Nom de l'employé : "));
	lireString(nom, 30);
	strcpy(tmp->nom, nom);
	
	affichageTitre(Accent("Ajout d'un employé"), tailleTitreEmploye);
	printf ("%s", Accent(" Prenom de l'employé : "));
	lireString(prenom, 30);
	strcpy(tmp->prenom, prenom);	
	
	affichageTitre(Accent("Ajout d'un employé"), tailleTitreEmploye);
	printf ("%s", Accent(" Salaire horaire de l'employé (en euros): "));
	float x = choixReel(0.0, 99.99, 6);
	tmp->salaireParHeure = x; 
	
	affichageTitre(Accent("Ajout d'un employé"), tailleTitreEmploye);
	printf ("%s", Accent(" Nombre d'heures déja prestées (et pas encore payées) : "));
	tmp->nbHeures = choixEntier(0, 999, 5);
	
	affichageTitre(Accent("Ajout d'un employé"), tailleTitreEmploye);
	printf ("%s", Accent("Confirmez-vous l'ajout de l'employé suivant?\n\n"));
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

void supprimerEmploye(){
	int nb = lectureEmploye(), i, j, ok, idMax, choix, choix2, choix3;
	char nom[30],prenom[30],tmp[3];
	
	affichageTitre(Accent("Suppression d'un employé"), tailleTitreEmploye);
	afficherListeEmploye();
	
	printf ("%s", Accent("Entrez l'id de l'employé que vous souhaitez supprimer.\n\n"));
	printf("Votre choix : ");
		
	courantEmpl = premierEmpl;
	for(i = 1 ; i < nb-1 ; i++) {
		courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employés
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
	
	affichageTitre(Accent("Suppression d'un employé"),tailleTitreEmploye);
	afficherTitresColonnesEmploye();
	courantEmpl = premierEmpl;
	for(i = 1 ; i < nb ; i++) {
		if(courantEmpl->id == choix){
			affichageUnEmploye(courantEmpl);
		}
		courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employés
	}	
	
	
	printf ("%s", Accent("\n\nConfirmez-vous la suppression de l'employé suivant?\n\n"));
	printf("\n1 : Non \n");
	printf("2 : Oui \n");
	printf("Votre choix :");
	
	choix2=choixEntier(1, 2, 1);
	
	if(choix2 == 2){
		
		printf ("%s", Accent("\n\nVoulez-vous payer cet employé avant de le supprimer?\n\n"));
		printf("\n1 : Non \n");
		printf("2 : Oui \n");
		printf("Votre choix :");
		
		choix3=choixEntier(1, 2, 1);
		system("cls");
		
		//paiement de l'employé
		if(choix3 == 2){
			FILE *fEmploye;
			//on lit le solde du camping
			fEmploye = fopen("data/campingData.dat", "r");
			float caisse;
			fscanf(fEmploye,"%f", &caisse);
			fclose(fEmploye);
			
			//on parcourt les employés pour savoir lequel doit etre débité
			courantEmpl = premierEmpl;
			while(courantEmpl->nxtEmpl != NULL){
				if(courantEmpl->id == choix){
					caisse -= courantEmpl->nbHeures * courantEmpl->salaireParHeure;
					courantEmpl->nbHeures = 0;
				}
				courantEmpl = courantEmpl->nxtEmpl;
			}
			
			//on réécrit dans le fichier le solde débité
			fEmploye = fopen("data/campingData.dat", "w");
			fprintf(fEmploye,"%10.2f\n", caisse);
			fclose(fEmploye);
		}
		
		courantEmpl = premierEmpl;
		employe *precedent;
		//on parcourt la liste
		for(j = 1 ; j < nb ; j++){
			//si j>1, il faut "retenir" le précédent pour savoir d'ou pointer
			if(j > 1){
				
				//on part donc avec un décalage de 1
				if(j == 2){
					precedent = premierEmpl;
				}
				else{
					precedent = precedent->nxtEmpl;
				}
			}
			
			//si on a trouvé le bon id
			if(courantEmpl->id == choix){
				//si c'est le premier élément de la liste
				if(j == 1){
					premierEmpl = courantEmpl->nxtEmpl;
					free(courantEmpl);
					courantEmpl = premierEmpl;
					break;
				}
				//si c'est le dernier élément de la liste
				else if (courantEmpl->nxtEmpl==NULL){
					precedent->nxtEmpl = NULL;
					free(courantEmpl);
					break;
				}
				//si c'est un élément a l'intérieur de la liste
				else {
					precedent->nxtEmpl = courantEmpl->nxtEmpl;
					free(courantEmpl);
					break;
				}
			}
			//si on a pas trouvé le bon ID on avance
			else{
				courantEmpl = courantEmpl->nxtEmpl;
			}
		}
		
		affichageTitre(Accent("Suppression d'un employé"),tailleTitreEmploye);
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
		
		printf ("%s", Accent("Employé supprimé!\n\n"));
		system("PAUSE");
		system("cls");	
	}	
	else{
		printf ("%s", Accent("Employé non supprimé\n\n"));
		system("PAUSE");
		system("cls");	
	}
}

void ajouterJourneeTravail(){
	int  nb = lectureEmploye(), i, j, idMax, ok, choix, choix2, nbDemiJournee;
	char tmp[3];
	affichageTitre(Accent("Ajout d'heures de travail à un employé"), tailleTitreEmploye);
	afficherListeEmploye();
	
	printf ("%s", Accent("Entrez l'id de l'employé auquel vous souhaitez ajouter des demi-journées de travail.\n\n"));
	printf("Votre choix : ");
	
	courantEmpl = premierEmpl;
	for(i = 1 ; i < nb - 1 ; i++) {
		courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employés
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
	
	affichageTitre(Accent("Ajout d'heures de travail à un employé"), tailleTitreEmploye);
	afficherTitresColonnesEmploye();
	courantEmpl = premierEmpl;
	for(i = 1 ; i < nb ; i++) {
		if(courantEmpl->id == choix){
			affichageUnEmploye(courantEmpl);
			break;
		}
		courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employés
	}	
	
	printf ("%s", Accent("\n\nConfirmez-vous le choix de l'employé suivant?\n\n"));
	printf("\n1 : Non \n");
	printf("2 : Oui \n");
	printf("Votre choix :");
	
	choix2=choixEntier(1, 2, 1);
	
	if(choix2 == 2){
		affichageTitre(Accent("Ajout d'heures de travail à un employé"), tailleTitreEmploye);
		afficherTitresColonnesEmploye();
		affichageUnEmploye(courantEmpl);
		ok = 0;
		do{
			if(ok > 0){
				printf("\n l'employe aura trop d'heures !");
			}
			printf ("%s", Accent("\n\nCombien de demi-journées de travail voulez-vous lui ajouter?\n\n"));
			nbDemiJournee = choixEntier(0, 999, 5);
			ok++;
		}while((nbDemiJournee * 4 + courantEmpl->nbHeures) > 999);
		
		affichageTitre(Accent("Ajout d'heures de travail à un employé"), tailleTitreEmploye);
		afficherTitresColonnesEmploye();
		affichageUnEmploye(courantEmpl);
		printf ("%s", Accent("\nNombre de demi-journées à ajouter : "));
		printf ("%3d", nbDemiJournee);
		
		printf ("%s", Accent("\n\nConfirmez-vous l'ajout de ces demi-journées à l'employé suivant?\n\n"));
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
			printf ("%s", Accent("Heures ajoutées!\n\n"));
			system("PAUSE");
			system("cls");
		}
	}
	else{
		printf ("%s", Accent("Ajout d'heures annulé\n\n"));
		system("PAUSE");
		system("cls");	
	}	
}

void modifierSalaire(){
	int  nb = lectureEmploye(), i, j, idMax, ok, choix, choix2, choix3;
	float nSalaire;
	char tmp[3];
	affichageTitre(Accent("Modification du salaire d'un employé"), tailleTitreEmploye);
	afficherListeEmploye();
	
	printf ("%s", Accent("Entrez l'id de l'employé dont vous voulez modifier le salaire\n\n"));
	printf("Votre choix : ");
	
	courantEmpl = premierEmpl;
	for(i = 1 ; i < nb - 1 ; i++) {
		courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employés
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
	
	affichageTitre(Accent("Modification du salaire d'un employé"), tailleTitreEmploye);
	afficherTitresColonnesEmploye();
	courantEmpl = premierEmpl;
	for(i = 1 ; i < nb ; i++) {
		if(courantEmpl->id == choix){
			affichageUnEmploye(courantEmpl);
			break;
		}
		courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employés
	}	
	
	printf ("%s", Accent("\n\nConfirmez-vous le choix de l'employé suivant?\n\n"));
	printf("\n1 : Non \n");
	printf("2 : Oui \n");
	printf("Votre choix :");
	
	choix2=choixEntier(1, 2, 1);
	
	if(choix2 == 2){
		printf ("%s", Accent("\n\nVoulez-vous payer cet employé avant de modifier son salaire?\n\n"));
		printf("\n1 : Non \n");
		printf("2 : Oui \n");
		printf("Votre choix :");
		
		choix3 = choixEntier(1, 2, 1);
		system("cls");
		
		//paiement de l'employé
		if(choix3 == 2){
			FILE *fEmploye;
			//on lit le solde du camping
			fEmploye = fopen("data/campingData.dat", "r");
			float caisse;
			fscanf(fEmploye, "%f", &caisse);
			fclose(fEmploye);
			
			//on parcourt les employés pour savoir lequel doit etre débité
			courantEmpl = premierEmpl;
			while(courantEmpl->nxtEmpl != NULL){
				if(courantEmpl->id == choix){
					caisse -= courantEmpl->nbHeures * courantEmpl->salaireParHeure;
					courantEmpl->nbHeures = 0;
				}
				courantEmpl = courantEmpl->nxtEmpl;
			}
			
			//on réécrit dans le fichier le solde débité
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
			courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employés
		}
		//modification du salaire
		affichageTitre(Accent("Modification du salaire d'un employé"),tailleTitreEmploye);
		printf ("%s", Accent("Nouveau Salaire horaire de l'employé (en euros): "));
		float x = choixReel(0.0,99.99,6);
		nSalaire = x; 
		
		affichageTitre(Accent("Modification du salaire d'un employé"), tailleTitreEmploye);
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
			
			printf ("%s", Accent("Modification effectuée!\n\n"));
			system("PAUSE");
			system("cls");
		}
	}
	else{
		printf ("%s", Accent("Modification annulée\n\n"));
		system("PAUSE");
		system("cls");
	}
}

void paiementEmployes(){
	int choix2, i, j, idMax, ok, choix, nb;
	nb = lectureEmploye();
	char tmp[3];
	affichageTitre(Accent("Paiement des employés"), tailleTitreEmploye);
	printf ("%s", Accent("\n\nVoulez vous :\n\n"));
	printf ("%s", Accent("\n1 : Payer tous les employés \n"));
	printf ("%s", Accent("2 : Payer un employé spécifique \n"));
	printf("Votre choix :");
	choix2=choixEntier(1, 2, 1);
	
	if(choix2 == 1){
		float aDebiter = 0;
		courantEmpl = premierEmpl;
		while(courantEmpl->nxtEmpl!=NULL) {
			aDebiter += courantEmpl->nbHeures * courantEmpl->salaireParHeure;
			courantEmpl->nbHeures = 0;
			courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employés
		}
		
		FILE *fEmploye;
		//on lit le solde du camping
		fEmploye = fopen("data/campingData.dat", "r");
		float caisse;
		fscanf(fEmploye, "%f", &caisse);
		fclose(fEmploye);
		
		//on réécrit dans le fichier le solde débité
		fEmploye = fopen("data/campingData.dat", "w");
		fprintf(fEmploye, "%10.2f\n", caisse-aDebiter);
		fclose(fEmploye);
		
		//on réécrit les heures de travail des employés
		fEmploye = fopen("data/employes.dat", "w");
		courantEmpl = premierEmpl;
		while(courantEmpl->nxtEmpl != NULL){
			fprintf(fEmploye, "%2d %-29s %-29s %5.2f %03d\n", courantEmpl->id, courantEmpl->nom, courantEmpl->prenom, courantEmpl->salaireParHeure, courantEmpl->nbHeures);
			courantEmpl = courantEmpl->nxtEmpl;
		}
		fclose(fEmploye);
		
		printf ("%s", Accent("Paiement effectué\n\n"));
		system("PAUSE");
		system("cls");	
	}
	else{
		affichageTitre(Accent("Paiement des employés"), tailleTitreEmploye);
		afficherListeEmploye();
		
		printf ("%s", Accent("Entrez l'id de l'employé dont vous voulez modifier le salaire\n\n"));
		printf("Votre choix : ");
		
		courantEmpl = premierEmpl;
		while(courantEmpl->nxtEmpl != NULL) {
			courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employés
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
		
		affichageTitre(Accent("Paiement des employés"), tailleTitreEmploye);
		afficherTitresColonnesEmploye();
		courantEmpl = premierEmpl;
		for(i = 1 ; i < nb ; i++) {
			if(courantEmpl->id == choix){
				affichageUnEmploye(courantEmpl);
				break;
			}
			courantEmpl = courantEmpl->nxtEmpl; // on parcourt les employés
		}	
		
		printf ("%s", Accent("\n\nConfirmez-vous le paiement de l'employé suivant?\n\n"));
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
			//on réécrit dans le fichier le solde débité
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
			
			printf ("%s", Accent("Paiement effectué\n\n"));
			system("PAUSE");
			system("cls");
		}
	}
}

void switchMenuEmploye(int choix){
	switch(choix){
		case 1 : 
			affichageTitre(Accent("Liste des employés"), tailleTitreEmploye);
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
