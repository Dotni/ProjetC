/********************************************************************************************
*****************************Projet C : gestion d'un camping*********************************
*********************************************************************************************
Nom : Mazzeo  			Prenom : Florian       Classe : 2BIa1
Nom : Maes    			Prenom : Martin        Classe : 2BIa1

nom fichier : MazzeoMaes.c
date : 30/11/2020 
**********************************************************************************************
**********************************************************************************************
**********************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include "structures/util.h"
#include "structures/emplacement.h"
#include "structures/sejour.h"
#include "structures/client.h"
#include "structures/employe.h"


void main(){
	
	//d�claration des variables
	int choixMP, choixIntro,choixEmplacement,choixClient,choixEmploye,choixSejour;
	sejour sejours;
	
	//fonctions graphiques
	int intro();
	int menuEmplacement();				//fonction intro
	int menuPrincipal();				//fonction menu
	int modeEmploi();					// acc�der au mode d'emploi du projet
	void quitter();						// quitter le programme

	do {
		choixIntro = intro();
		switch(choixIntro) {
			case 1: // acc�der au menu principal
				do{
					choixMP = menuPrincipal();
					switch(choixMP){
						case 1: 
							do{
								choixEmplacement = menuEmplacement();
								switchMenuEmplacement(choixEmplacement);
							} while(choixEmplacement != 5); // 5 = retour au menu principal
							break;
						case 2:
							
							choixClient = menuClient();
							
							break;
						case 3:
							do{
								choixEmploye = menuEmploye();
								switchMenuEmploye(choixEmploye);
							} while(choixEmploye != 7); // 5 = retour au menu principal
							break;
						case 4:
							do {
								choixSejour = menuSejour();
								switchMenuSejour(choixSejour);
							} while(choixSejour != 3); // 3 = retour au menu principal
							break;		
					}
				} while(choixMP != 5);
				break;
			case 2: // acc�der au mode d'emploi
				modeEmploi();
				break;
			default: // s�curit�, ne devrait pas arriver puisque le choix est d�j� contr�l� dans la fonction intro
				quitter();
				break;
		}
	} while(choixIntro != 3);
}

int intro(){
	int choix = 0;
	short first = 0;
	char tmp[2];
	
	do { //on effectue cette boucle tant que l'utilisateur n'a pas fait de choix valide
		if(first == 0){ //si l'utilisateur n'a pas fait d'erreur
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PROGRAMME DE GESTION D'UN CAMPING %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			sdl();sdl();
			printf("||                   --------------------------------------------------------                 ||\n");
			printf("||                   || Bienvenue dans le programme de gestion du camping! ||                 ||\n");
			printf("||                   --------------------------------------------------------                 ||\n");
			first = 1;	//permet de dire que ce n'est pas la premiere fois qu'on passe dans la boucle	
		}
		else { //si l'utilisateur a fait une erreur
			system("cls");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||                              Veuillez entrer un nombre valide!                             ||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
		}
		
		//code commun (peut importe si l'utilisateur a fait une erreur ou pas)
		sdl();sdl();
		printf("||                                   Que souhaitez-vous faire?                                ||\n");
		printf ("%s", Accent("||                         (entrez le num�ro correspondant � votre choix)                     ||\n"));
		sdl();sdl();
		printf ("%s", Accent("||  1.  Acc�der au menu principal                                                             ||\n"));
		printf("||  2.  Mode d'emploi                                                                         ||\n");
		printf("||  3.  Quitter le programme                                                                  ||\n");
		sdl();
		printf("||  Votre choix :  ");
		choix = lire(tmp, 2);
	} while(choix < 1 || choix > 3);
	system("cls");
	return choix;
}

int menuPrincipal(){
	int choix = 0;
	short first = 0;
	char tmp[2];
	
	do { //on effectue cette boucle tant que l'utilisateur n'a pas fait de choix valide
		if(first == 0) { //si l'utilisateur n'a pas fait d'erreur
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Menu Principal %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			first = 1;	
		}
		else{ //si l'utilisateur a fait une erreur
			system("cls");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||                              Veuillez entrer un nombre valide!                             ||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
		}
		
		//code commun (peut importe si l'utilisateur a fait une erreur ou pas)
		sdl();sdl();
		printf ("%s", Accent("|| Entrez le num�ro correspondant � votre choix.                                              ||\n"));
		sdl();sdl();
		printf ("%s", Accent("||  1.  Menu emplacement                                                                      ||\n"));
		printf("||  2.  Menu client                                                                           ||\n");
			printf ("%s",Accent("||  3.  Menu employ�                                                                          ||\n"));
		printf ("%s", Accent("||  4.  Menu s�jour                                                                           ||\n"));	
		printf("||  5.  Retour                                                                                ||\n");
		sdl();
		printf("||  Votre choix :  ");
		choix = lire(tmp, 2);
	}while(choix < 1 || choix > 5);
	system("cls");
	return choix;		
}

int menuEmplacement(){
	int choix = 0;
	short first = 0;
	char tmp[2];
	
	do {
		if(first == 0) {
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Menu Emplacement %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			first = 1;	
		}
		else {
			system("cls");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||                              Veuillez entrer un nombre valide!                             ||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
		}
		sdl();sdl();
		printf ("%s", Accent("|| Entrez le num�ro correspondant � votre choix.                                              ||\n"));
		sdl();sdl();
		printf ("%s", Accent("||  1.  Afficher la liste des emplacements                                                    ||\n"));
		printf("||  2.  Ajouter un emplacement                                                                ||\n");
		printf("||  3.  Supprimer un emplacement                                                              ||\n");
		printf ("%s", Accent("||  4.  Modifier un emplacement                                                               ||\n"));	
		printf("||  5.  Retour                                                                                ||\n");
		sdl();
		printf("||  Votre choix :   ");
		choix = lire(tmp, 2);
	}while(choix < 1 || choix > 5);
	system("cls");
	return choix;		
}

int menuClient(){
	int choix = 0;
	short first = 0;
	char tmp[2];
	
	do{
		if(first == 0){
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Menu Client %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			first = 1;	
		}
		else{
			system("cls");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||                              Veuillez entrer un nombre valide!                             ||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
		}
		sdl();sdl();
		printf ("%s", Accent("|| Entrez le num�ro correspondant � votre choix.                                              ||\n"));
		sdl();sdl();
		printf ("%s", Accent("||  1.  Liste des clients                                                                     ||\n"));
		printf("||  2.  Ajouter un client                                                                     ||\n");
		printf ("%s", Accent("||  3.  Effectuer une r�servation                                                             ||\n"));
		printf ("%s", Accent("||  4.  Modifier une r�servation                                                              ||\n"));	
		printf("||  5.  Retour                                                                                ||\n");
		sdl();
		printf("||  Votre choix :  ");
		choix = lire(tmp, 2);
		
	}while(choix < 1 || choix > 5);
	system("cls");
	return choix;	
}

int menuEmploye(){
	int choix = 0;
	short first = 0;
	char tmp[2];
	
	do{
		if(first == 0){
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf ("%s", Accent("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Menu employ� %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n"));
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			first=1;	
		}
		else{
			system("cls");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||                              Veuillez entrer un nombre valide!                             ||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
		}
		sdl();sdl();
		printf ("%s", Accent("|| Entrez le num�ro correspondant � votre choix.                                              ||\n"));
		sdl();sdl();
		printf ("%s", Accent("||  1.  Liste des employ�s                                                                    ||\n"));
		printf ("%s", Accent("||  2.  Ajouter un employ�                                                                    ||\n"));
		printf ("%s", Accent("||  3.  Supprimer un employ�                                                                  ||\n"));
		printf ("%s", Accent("||  4.  Ajouter une journ�e/demi journ�e de travail � un employ�                              ||\n"));
		printf ("%s", Accent("||  5.  Modifier le salaire d'un employ�                                                      ||\n"));
		printf ("%s", Accent("||  6.  Payer Les employ�s                                                                    ||\n"));	
		printf("||  7.  Retour                                                                                ||\n");
		sdl();
		printf("||  Votre choix :   \n");
		choix = lire(tmp, 2);
		
	}while(choix < 1 || choix > 7);
	system("cls");
	return choix;	
}

int menuSejour(){
	int choix = 0;
	short first = 0;
	char tmp[2];
	
	do{
		if(first == 0){
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf ("%s", Accent("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Menu S�jour %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n"));
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			first=1;	
		}
		else{
			system("cls");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||                              Veuillez entrer un nombre valide!                             ||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
		}
		sdl();sdl();
		printf ("%s", Accent("|| Entrez le num�ro correspondant � votre choix.                                              ||\n"));
		sdl();sdl();
		printf ("%s", Accent("||  1.  Liste des s�jours                                                                     ||\n"));
		printf ("%s", Accent("||  2.  Liste des emplacements disponibles                                                    ||\n"));
		printf("||  3.  Retour                                                                                ||\n");
		sdl();
		printf("||  Votre choix :  ");
		choix = lire(tmp, 2);
		
	}while(choix < 1 || choix > 3);
	system("cls");
	return choix;
}

int modeEmploi() {
	printf("On le fera en dernier c'est que de l'affichage\n");
	sdl();
	sdl();
	return 0;
}

void quitter() {
	printf("%s", Accent("Fermeture du logiciel. A bient�t!"));
}
