#include <stdio.h>
#include <string.h>
#include "emplacement.h"
#include "util.h"


//déclaration des constantes
const int tailleEmplacement = 50;
int tailleTitre = 65;
emplacement empl[50];
//permet d'initialiser tous les ID du tableau a 0
//En effet, l'affichage des id ne se fait que pour les ID dont la valeur est différente de 0
void viderEmplacements(){
	int i;
	for (i = 1 ; i < tailleEmplacement ; i++){
		empl[i].id = 0;
	}
}

//permet de lire les emplacements et de les stocker dans un tableau
int lectureEmplacements(){
	//on oublie pas de "vider" le tableau pour ne pas afficher des éléments qui ont été supprimés mais qui sont tjrs en mémoire
	viderEmplacements();
	FILE *fEmplacement;
	fEmplacement = fopen("data/emplacements.dat","r");
	int i = 1;
	while(!feof(fEmplacement)){
		fscanf(fEmplacement, "%2d %1d %1d %5f %6f", &empl[i].id, &empl[i].type, &empl[i].electricite, &empl[i].taille, &empl[i].prix);
		i++;
	}
	fclose(fEmplacement);
	
	//on retourne le nombre d'éléments du tableau
	return i - 1;
}

//affiche le titre des colonnes
void affichageTitreColonnes(){
	char x = 253;
	printf("%s", Accent("|| Id |   Type   | Electricité "));
	printf("| Taille (m%c) | Prix (en euros) ||\n", x);
	printf("||----|----------|-------------|-------------|-----------------||\n");
}

//affiche un seul emplacement
void affichageUnEmplacement(emplacement empl){
	//affichage de l'id
	printf("|| %2d | ", empl.id);
	
	//affichage du type
	affichageTypeEmplacement(empl.type);
	
	//affichage de l'électricité
	if(empl.electricite == 0){ 
		printf("     Non    | ");
	}
	else{ 
		printf("     Oui    | ");  
	}
	
	//affichage de la taille et du prix
	printf("   %5.2f    |     %06.2f      ||\n", empl.taille, empl.prix);
}

//affiche la liste complète des emplacements
void affichageListeEmplacement(){
	
	//on lit les emplacements
	lectureEmplacements();
	
	//affichages des éléments non dynamiques
	affichageTitre("Liste des emplacements",tailleTitre);
	affichageTitreColonnes();
	
	//affichage des emplacements
	int i = 1;
	while(empl[i].id != 0){
		affichageUnEmplacement(empl[i]);
		i++; 
	}
	printf("||-------------------------------------------------------------||\n");
}

void nouvelEmplacement(){
	//permet de récupérer le nombre d'emplacements et de remplir empl[]
	int nb = lectureEmplacements(empl, tailleEmplacement);
	int i;
	char x = 253; 
	
	//S'il y a trop d'emplacements :
	if(nb >= tailleEmplacement - 1){
		printf ("%s", Accent("Impossible d'ajouter un emplacement, la liste est déja complète!\n"));
		system("PAUSE");
		system("cls");
		return;
	}
	
	//s'il y a de la place on continue.
	//attention que les id doivent etre triés pour éviter que deux emplacement aient le meme id
	emplacement nouvEmpl;
	nouvEmpl.id = empl[nb - 1].id + 1;
	printf("%2d %2d", nb, empl[nb - 1].id);
	system("PAUSE");
	int choix;
	char tmp[7];
	float valeur;
	affichageTitre("Ajout d'un emplacement",tailleTitre);
	//on demande à l'utilisateur ce qu'il doit entrer
	
	//type
	printf("Type de l'emplacement ?\n\n");
	printf("1 : Tente \n");
	printf("2 : Caravane \n");
	printf("3 : Bungalow \n\n");
	printf("Votre choix : ");
	
	i = 0;
	do{
		if(i != 0){
			printf("Veuillez entrer un nombre correct! Votre choix : ");
		}
		choix = lire(tmp, 2);
		i++;
	}while(choix < 1 || choix > 3);
	nouvEmpl.type = choix;
	
	//elec
	affichageTitre("Ajout d'un emplacement",tailleTitre);
	printf ("%s", Accent("L'emplacement possède-t-il un accès à l'électricité ?\n\n"));
	printf("1 : Non \n");
	printf("2 : Oui \n");
	printf("Votre choix : ");
	
	i = 0;
	do{
		if(i != 0){
			printf("Veuillez entrer un nombre correct! Votre choix : ");
		}
		choix = lire(tmp, 2);
		i++;
	}while(choix < 1 || choix > 2);
	nouvEmpl.electricite = choix - 1;
	
	//taille
	affichageTitre("Ajout d'un emplacement",tailleTitre);
	printf ("%s", Accent("Quelle est la superficie de l'emplacement (en m"));
	printf("%c) (compris entre 0.01 et 99.99)?\n\n", x);
	printf("Superficie : ");
	
	i=0;
	do{
		if(i != 0){
			printf("Veuillez entrer un nombre correct! (compris entre 0.01 et 99.99) Votre choix : ");
		}
		valeur = lireFloat(tmp, 6);
		i++;
	}while(valeur > 99.99 || valeur <= 0);
	nouvEmpl.taille = valeur;
	
	//prix
	affichageTitre("Ajout d'un emplacement",tailleTitre);
	printf ("Quel est le prix de l'emplacement(en euros)(compris entre 0.01 et 999.99)?\n\n", x);
	printf("prix : ");
	
	i = 0;
	do{
		if(i != 0){
			printf("Veuillez entrer un nombre correct! (compris entre 0.01 et 999.99) Votre choix : ");
		}
		valeur = lireFloat(tmp, 7);
		i++;
	}while(valeur > 999.99 || valeur <= 0.01);
	nouvEmpl.prix = valeur;
	
	affichageTitre("Ajout d'un emplacement",tailleTitre);
	printf("Confirmez-vous l'ajout de l'emplacement suivant?\n\n");
	affichageTitreColonnes();
	affichageUnEmplacement(nouvEmpl);
	printf("\n\n1 : Non \n");
	printf("2 : Oui \n");
	printf("Votre choix :");
	
	i = 0;
	do{
		if(i != 0){
			printf("Veuillez entrer un nombre correct! Votre choix :");
		}
		choix = lire(tmp, 2);
		i++;
	}while(choix < 1 || choix > 2);
	
	if(choix == 2){
		FILE *fEmplacement;
		fEmplacement = fopen("data/emplacements.dat","w");
		for(i = 1 ; i <nb ; i++){
			fprintf(fEmplacement, "%2d %1d %1d %5.2f %6.2f\n", empl[i].id, empl[i].type, empl[i].electricite, empl[i].taille, empl[i].prix);
		}
		fprintf(fEmplacement,"%2d %1d %1d %5.2f %6.2f", nouvEmpl.id, nouvEmpl.type, nouvEmpl.electricite, nouvEmpl.taille, nouvEmpl.prix);
		
		fclose(fEmplacement);
		system("cls");
		printf ("%s", Accent("Emplacement ajouté avec succès!\n"));
		system("PAUSE");
		system("cls");
	}
	else{
		system("cls");
		printf ("%s", Accent("Emplacement non ajouté!\n"));
		system("PAUSE");
		system("cls");
	}	
}

void supprimerEmplacement(){
	int nb = lectureEmplacements(empl, tailleEmplacement);
	int i, choix, choix2;
	char tmp[3];
	char tmp2[2];
	char x = 253;
	
	affichageTitre("Suppression d'un emplacement",tailleTitre);
	affichageListeEmplacement(empl, tailleEmplacement);
	
	printf ("Entrez l'id de l'emplacement que vous souhaitez supprimer.\n\n");
	printf("Votre choix : ");
	
	i = 0;
	do{
		if(i != 0){
			printf("Veuillez entrer un nombre correct! Votre choix : ");
		}
		choix = lire(tmp, 3);
		i++;
	}while(choix < 1 || choix > nb );
	
	
	affichageTitre("Suppression d'un emplacement",tailleTitre);
	printf("Confirmez-vous la suppression de l'emplacement suivant?\n\n");
	affichageTitreColonnes();
	affichageUnEmplacement(empl[choix]);
	printf("\n\n1 : Non \n");
	printf("2 : Oui \n");
	printf("Votre choix :");
	
	i = 0;
	do{
		if(i != 0){
			printf("Veuillez entrer un nombre correct! Votre choix :");
		}
		choix2 = lire(tmp2, 2);
		i++;
	}while(choix2 < 1 || choix2 > 2);
	
	if(choix2 == 2){
		for(i = choix + 1 ; i <= nb ; i++){
			empl[i] = empl[i - 1];
		}
		nb--;
		FILE *fEmplacement;
		fEmplacement = fopen("data/emplacements.dat","w");
		for(i = 1 ; i <=nb ; i++){
			fprintf(fEmplacement, "%2d %1d %1d %5.2f %6.2f\n", empl[i].id, empl[i].type, empl[i].electricite, empl[i].taille, empl[i].prix);
		}
		fclose(fEmplacement);
		system("cls");
		printf ("%s", Accent("Emplacement supprimé avec succès!\n"));
		system("PAUSE");
		system("cls");
	}
	else{
		system("cls");
		printf ("%s", Accent("Emplacement non supprimé!\n"));
		system("PAUSE");
		system("cls");
	}	
}

void modifierEmplacement(){
	int nb = lectureEmplacements(empl, tailleEmplacement);
	int i, choix, choix2;
	char tmp[4];
	char tmp2[2];
	char tmp3[7];
	char x = 253;
	
	affichageTitre("Modification d'un emplacement",tailleTitre);
	affichageListeEmplacement(empl, tailleEmplacement);
	
	printf ("Entrez l'id de l'emplacement que vous souhaitez modifier.\n\n");
	printf("Votre choix : ");
	
	i = 0;
	do{
		if(i != 0){
			printf("Veuillez entrer un nombre correct! Votre choix : ");
		}
		choix = lire(tmp, 4);
		i++;
	}while(choix < 1 || choix > nb );
	
	affichageTitre("Modification d'un emplacement",tailleTitre);
	printf("%s", Accent("Confirmez-vous la séléction de l'emplacement suivant pour modifications?\n\n"));
	affichageTitreColonnes();
	affichageUnEmplacement(empl[choix]);
	
	int indice = choix;
	printf("\n\n1 : Non \n");
	printf("2 : Oui \n");
	printf("Votre choix :");
	
	i = 0;
	do{
		if(i != 0){
			printf("Veuillez entrer un nombre correct! Votre choix :");
		}
		choix2 = lire(tmp2, 2);
		i++;
	}while(choix2 < 1 || choix2 > 2);
	
	if(choix2 == 2){
		affichageTitre("Modification d'un emplacement",tailleTitre);
		//type
		printf("Type de l'emplacement ?\n\n");
		printf("1 : Tente \n");
		printf("2 : Caravane \n");
		printf("3 : Bungalow \n\n");
		printf("Votre choix : ");
		float valeur;
		emplacement nouvEmpl;
		nouvEmpl.id = empl[indice].id;
		
		i=0;
		do{
			if(i != 0){
				printf("Veuillez entrer un nombre correct! Votre choix : ");
			}
			choix = lire(tmp, 2);
			i++;
		}while(choix < 1 || choix > 3);
		nouvEmpl.type = choix;
		
		//elec
		affichageTitre("Modification d'un emplacement",tailleTitre);
		printf ("%s", Accent("L'emplacement possède-t-il un accès à l'électricité ?\n\n"));
		printf("1 : Non \n");
		printf("2 : Oui \n");
		printf("Votre choix : ");
		
		i = 0;
		do{
			if(i != 0){
				printf("Veuillez entrer un nombre correct! Votre choix : ");
			}
			choix = lire(tmp, 2);
			i++;
		}while(choix < 1 || choix > 2);
		nouvEmpl.electricite = choix - 1;
		
		//taille
		affichageTitre("Modification d'un emplacement",tailleTitre);
		printf ("%s", Accent("Quelle est la superficie de l'emplacement (en m"));
		printf("%c)?\n\n", x);
		printf("Superficie : ");
		
		i = 0;
		do{
			if(i != 0){
				printf("Veuillez entrer un nombre correct! (compris entre 0.01 et 99.99) Votre choix : ");
			}
			valeur = lireFloat(tmp3, 6);
			i++;
		}while(valeur > 99.99 || valeur <= 0);
		nouvEmpl.taille = valeur;
		
		//prix
		affichageTitre("Modification d'un emplacement",tailleTitre);
		printf ("Quel est le prix de l'emplacement(en euros)?\n\n");
		printf("prix : ");
		
		i = 0;
		do{
			if(i != 0){
				printf("Veuillez entrer un nombre correct! (compris entre 0.01 et 999.99) Votre choix : ");
			}
			valeur = lireFloat(tmp3, 7);
			i++;
		}while(valeur > 999.99 || valeur <= 0);
		nouvEmpl.prix = valeur;
		
		affichageTitre("Modification d'un emplacement",tailleTitre);
		printf ("Voulez-vous remplacer cet emplacement \n\n");
		affichageTitreColonnes();
		affichageUnEmplacement(empl[indice]);
		printf ("par celui-ci ? \n\n");
		affichageTitreColonnes();
		affichageUnEmplacement(nouvEmpl);
		printf("1 : Non \n");
		printf("2 : Oui \n");
		printf("Votre choix : ");
		
		i = 0;
		do{
			if(i != 0){
				printf("Veuillez entrer un nombre correct! Votre choix : ");
			}
			choix = lire(tmp, 2);
			i++;
		}while(choix < 1 || choix > 2);
		
		if(choix == 2){
			empl[indice] = nouvEmpl;
		
			FILE *fEmplacement;
			fEmplacement = fopen("data/emplacements.dat","w");
			for(i = 1 ; i < nb ; i++){
				fprintf(fEmplacement, "%2d %1d %1d %5.2f %6.2f\n", empl[i].id, empl[i].type, empl[i].electricite, empl[i].taille, empl[i].prix);
			}
			fclose(fEmplacement);
			system("cls");
			printf ("%s", Accent("Emplacement modifié avec succès!\n"));
			system("PAUSE");
			system("cls");
		}
		else{
			system("cls");
			printf ("%s", Accent("Emplacement non modifié!\n"));
			system("PAUSE");
			system("cls");
		}
	}
	else{
		system("cls");
		printf ("%s", Accent("Emplacement non modifié!\n"));
		system("PAUSE");
		system("cls");
	}	
}

emplacement * getEmplacement(int id){
	lectureEmplacements(empl, tailleEmplacement);
	return &(empl[id]);
}


void switchMenuEmplacement(int choix){
	switch(choix){
		case 1 : 
			affichageListeEmplacement();
			system("PAUSE");
			system("cls");
			break;
		case 2 :
			nouvelEmplacement();
			system("cls");
			break;
		case 3:
			supprimerEmplacement();
			break;
		case 4:
			modifierEmplacement();
			break;
	}
}
