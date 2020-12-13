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
	system("TITLE Gestion du camping");
	
	//déclaration des variables
	int choixMP, choixIntro, choixModeEmploi, choixEmplacement, choixClient, choixEmploye, choixSejour;
	sejour sejours;
	
	//fonctions graphiques
	int intro();
	int menuEmplacement();				//fonction intro
	int menuPrincipal();				//fonction menu
	int modeEmploi();					// accéder au mode d'emploi du projet
	void quitter();						// quitter le programme
	void switchModeEmploi(int);         // mode d'emploi
	
	do {
		choixIntro = intro();
		switch(choixIntro) {
			case 1: // accéder au menu principal
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
							do{
								choixClient = menuClient();
								switchMenuClient(choixClient);
							} while(choixClient != 4); // 4 = retour au menu principal
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
			case 2: // accéder au mode d'emploi
				do {
					choixModeEmploi = modeEmploi();
					switchModeEmploi(choixModeEmploi);
				} while(choixModeEmploi != 6);
				break;
			default: // sécurité, ne devrait pas arriver puisque le choix est déjà contrôlé dans la fonction intro
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
			printf ("%s", Accent("||                         (entrez le numéro correspondant à votre choix)                     ||\n"));
			sdl();sdl();
			printf ("%s", Accent("||  1.  Accéder au menu principal                                                             ||\n"));
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
		printf ("%s", Accent("|| Entrez le numéro correspondant à votre choix.                                              ||\n"));
		sdl();sdl();
		printf ("%s", Accent("||  1.  Menu emplacement                                                                      ||\n"));
		printf("||  2.  Menu client                                                                           ||\n");
		printf ("%s",Accent("||  3.  Menu employé                                                                          ||\n"));
		printf ("%s", Accent("||  4.  Menu séjour                                                                           ||\n"));	
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
		printf ("%s", Accent("|| Entrez le numéro correspondant à votre choix.                                              ||\n"));
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
		printf ("%s", Accent("|| Entrez le numéro correspondant à votre choix.                                              ||\n"));
		sdl();sdl();
		printf ("%s", Accent("||  1.  Liste des clients                                                                     ||\n"));
		printf("||  2.  Nouveau Client                                                                        ||\n");
		printf ("%s", Accent("||  3.  Client existant                                                                       ||\n"));	
		printf("||  4.  Retour                                                                                ||\n");
		sdl();
		printf("||  Votre choix :  ");
		choix = lire(tmp, 2);
	}while(choix < 1 || choix > 4);
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
			printf ("%s", Accent("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Menu employé %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n"));
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
		printf ("%s", Accent("|| Entrez le numéro correspondant à votre choix.                                              ||\n"));
		sdl();sdl();
		printf ("%s", Accent("||  1.  Liste des employés                                                                    ||\n"));
		printf ("%s", Accent("||  2.  Ajouter un employé                                                                    ||\n"));
		printf ("%s", Accent("||  3.  Supprimer un employé                                                                  ||\n"));
		printf ("%s", Accent("||  4.  Ajouter une demi-journée de travail à un employé                                      ||\n"));
		printf ("%s", Accent("||  5.  Modifier le salaire d'un employé                                                      ||\n"));
		printf ("%s", Accent("||  6.  Payer Les employés                                                                    ||\n"));	
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
			printf ("%s", Accent("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Menu Séjour %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n"));
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
		printf ("%s", Accent("|| Entrez le numéro correspondant à votre choix.                                              ||\n"));
		sdl();sdl();
		printf ("%s", Accent("||  1.  Liste des séjours                                                                     ||\n"));
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
	int choix = 0;
	short first = 0;
	char tmp[2];
	
	do{
		if(first == 0){
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Mode d'emploi %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
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
		printf ("%s", Accent("|| Entrez le numéro correspondant à votre choix.                                              ||\n"));
		sdl();sdl();
		printf ("||  1.  Le menu principal                                                                     ||\n");
		printf("||  2.  Le menu emplacement                                                                   ||\n");
		printf ("||  3.  Le menu clients                                                                       ||\n");	
		printf("%s", Accent("||  4.  Le menu employé                                                                       ||\n"));
		printf("%s", Accent("||  5.  Le menu séjour                                                                        ||\n"));
		printf("||  6.  Retour                                                                                ||\n");
		sdl();
		printf("||  Votre choix :  ");
		choix = lire(tmp, 2);
	}while(choix < 1 || choix > 6);
	system("cls");
	return choix;
}

void quitter() {
	printf("%s", Accent("Fermeture du logiciel. A bientôt!"));
}

void switchModeEmploi(int choix) {
	// déclarations des différentes parties du mode d'emploi
	void mePrincipal();
	void meEmplacement();
	void meClients();
	void meEmployes();
	void meSejour();
	
	switch(choix) {
		case 1:
			mePrincipal();
			system("pause");
			system("cls");
			break;
		case 2:
			meEmplacement();
			system("pause");
			system("cls");
			break;
		case 3:
			meClients();
			system("pause");
			system("cls");
			break;
		case 4:
			meEmployes();
			system("pause");
			system("cls");
			break;
		case 5:
			meSejour();
			system("pause");
			system("cls");
			break;
	}	
}

void mePrincipal() {
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Le menu principal %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	sdl();sdl();
	printf("%s", Accent("|| Le menu principal permet au gestionnaire du camping d'accéder aux différentes parties du   ||\n\
|| programme en fonction de ses besoins. Il peut donc accéder à 4 différents menus :\          ||\n\
||		1. Le menu emplacement.                                                       ||\n\
||		2. Le menu client.                                                            ||\n\
||		3. Le menu employé.                                                           ||\n\
||		4. Le menu séjour.                                                            ||\n\
|| Il peut aussi revenir à l'écran d'accueil s'il souhaite chercher une information dans le   ||\n\
|| mode d'emploi ou s'il souhaite quitter le programme.                                       ||\n\
||============================================================================================||\n"));
}

void meEmplacement() {
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Le menu emplacement %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	sdl();sdl();
	printf("%s", Accent("|| Depuis ce menu, le gestionnaire peut :                                                     ||\n\
||		1. Afficher la liste des emplacements.                                        ||\n\
||		2. Ajouter un emplacement.                                                    ||\n\
||		3. Supprimer un emplacement.                                                  ||\n\
||		4. Modifier un emplacement.                                                   ||\n\
||		5. Revenir au menu principal.                                                 ||\n\
|| L'affichage des emplacements donne, pour chaque emplacement, son ID, si l'emplacement est  ||\n\
|| un emplacement pour tente, caravane ou bungalow, la disponibilité, ou non, d'électricité,  ||\n\
|| la taille (en m²) et le prix (en euros) de l'emplacement. Pour l'ajout d'un emplacement il ||\n\
|| suffit de saisir toutes les informations citées ci-dessus, mis à part l'ID, qui est généré ||\n\
|| automatiquement. Le programme demande ensuite une confirmation pour l'ajout. Si le         ||\n\
|| gestionnaire souhaite supprimer un emplacement, il lui suffit d'entrer l'ID de             ||\n\
|| l'emplacement dont la suppression est souhaitée, puis de confirmer son choix. Enfin, la    ||\n\
|| modification d'emplacement se fait par sélection de l'ID de l'emplacement à modifier. Une  ||\n\
|| confirmation de ce choix est ensuite demandée. Si le gestionnaire confirme son choix, il   ||\n\
|| ne lui reste qu'à entrer les nouvelles informations concernant l'emplacement sélectionné.  ||\n\
|| A noter : pour toutes ces options, le programme vérifie les données entrées. Il est donc   ||\n\
|| impossible de donner une taille ou un prix d'emplacement trop élevé ou trop bas, ainsi que ||\n\
|| d'entrer du texte lorsque c'est un nombre qui est demandé.                                 ||\n\
||============================================================================================||\n"));
}

void meClients() {
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Le menu clients %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	sdl();sdl();
}

void meEmployes() {
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("%s", Accent("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Le menu employé %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n"));
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	sdl();sdl();
	printf("%s", Accent("|| En ce qui concerne la gestion des employés, le gestionnaire du camping peut :              ||\n\
||		1. Afficher la liste des employés.                                            ||\n\
||		2. Ajouter un employé.                                                        ||\n\
||		3. Supprimer un employé.                                                      ||\n\
||		4. Ajouter une demi-journée de travail à un employé.                          ||\n\
||		5. Modifier le salaire d'un employé.                                          ||\n\
||		6. Payer les employés.                                                        ||\n\
||		7. Revenir au menu principal.                                                 ||\n\
|| L'affichage de la liste des employés indique, pour chaque employé, son ID, ses noms et     ||\n\
|| prénoms, le salaire (en euros) et le nombre d'heures prestées. Ensuite, l'ajout d'employé  ||\n\
|| requiert les informations citées ci-dessus, mis à part l'ID généré automatiquement. La     ||\n\
|| suppression d'employé ne demande que son ID et une confirmation de suppression. S'il y a   ||\n\
|| confirmation, l'utilisateur peut choisir de payer ou non l'employé qu'il supprime. Il est  ||\n\
|| possible d'ajouter une ou plusieurs demi-journée(s) de travail à un employé. Chaque demi-  ||\n\
|| journée équivaut à 4h de travail. Le nombre de demi-journée(s) ajoutée(s) est convertit en ||\n\
|| heures et ces heures sont ajoutées au total d'heures prestées par l'employé. Un salaire    ||\n\
|| n'est pas fixe, il peut être revu à la baisse ou à la hausse par le gestionnaire. Pour     ||\n\
|| modifier un salaire, l'utilisateur entre l'ID de l'employé et confirme son choix. Il est   ||\n\
|| possible de payer l'employé avant de modifier son salaire. En cas de payement avant un     ||\n\
|| changement de salaire, le total d'heures est remis à 0 puisque ses heures ont été payées.  ||\n\
|| Pour terminer, l'utilisateur peut payer les employés. Il peut choisir de payer tous les    ||\n\
|| employés, ou d'en sélectionner un et de le payer. A noter : lors d'un payement de salaire, ||\n\
|| le total payé est déduit du budget du camping.                                             ||\n\
||============================================================================================||\n"));
}

void meSejour() {
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("%s", Accent("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Le menu séjour %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n"));
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	sdl();sdl();
	printf("%s", Accent("|| Ce menu permet à l'utilisateur :                                                           ||\n\
||		1. Afficher la liste des séjours réservés aux camping.                        ||\n\
||		2. Voir la liste des emplacements disponibles.                                ||\n\
||		3. Revenir au menu principal.                                                 ||\n\
|| Si l'utilisateur affiche la liste des séjours, il aura comme information l'ID du séjour,   ||\n\
|| la formule (tente, bungalow, caravane), le nombre de personnes, la date et le prix         ||\n\
|| (en euros) de chaque séjour. L'utilisateur peut aussi afficher la liste des emplacements   ||\n\
|| disponibles pour une date choisie. Cf. le menu emplacement pour les informations affichées ||\n\
|| à l'écran.                                                                                 ||\n\
||============================================================================================||\n"));
}
