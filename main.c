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
	
	//d�claration des variables
	int choixMP, choixIntro, choixModeEmploi, choixEmplacement, choixClient, choixEmploye, choixSejour;
	sejour sejours;
	
	//fonctions graphiques
	int intro();
	int menuEmplacement();				//fonction intro
	int menuPrincipal();				//fonction menu
	int modeEmploi();					// acc�der au mode d'emploi du projet
	void quitter();						// quitter le programme
	void switchModeEmploi(int);         // mode d'emploi
	
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
			case 2: // acc�der au mode d'emploi
				do {
					choixModeEmploi = modeEmploi();
					switchModeEmploi(choixModeEmploi);
				} while(choixModeEmploi != 6);
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
			printf ("%s", Accent("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Menu employ� %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n"));
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
		printf ("%s", Accent("||  1.  Liste des employ�s                                                                    ||\n"));
		printf ("%s", Accent("||  2.  Ajouter un employ�                                                                    ||\n"));
		printf ("%s", Accent("||  3.  Supprimer un employ�                                                                  ||\n"));
		printf ("%s", Accent("||  4.  Ajouter une demi-journ�e de travail � un employ�                                      ||\n"));
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
		printf ("%s", Accent("|| Entrez le num�ro correspondant � votre choix.                                              ||\n"));
		sdl();sdl();
		printf ("||  1.  Le menu principal                                                                     ||\n");
		printf("||  2.  Le menu emplacement                                                                   ||\n");
		printf ("||  3.  Le menu clients                                                                       ||\n");	
		printf("%s", Accent("||  4.  Le menu employ�                                                                       ||\n"));
		printf("%s", Accent("||  5.  Le menu s�jour                                                                        ||\n"));
		printf("||  6.  Retour                                                                                ||\n");
		sdl();
		printf("||  Votre choix :  ");
		choix = lire(tmp, 2);
	}while(choix < 1 || choix > 6);
	system("cls");
	return choix;
}

void quitter() {
	printf("%s", Accent("Fermeture du logiciel. A bient�t!"));
}

void switchModeEmploi(int choix) {
	// d�clarations des diff�rentes parties du mode d'emploi
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
	printf("%s", Accent("|| Le menu principal permet au gestionnaire du camping d'acc�der aux diff�rentes parties du   ||\n\
|| programme en fonction de ses besoins. Il peut donc acc�der � 4 diff�rents menus :          ||\n\
||                                                                                            ||\n\
||		1. Le menu emplacement.                                                       ||\n\
||		2. Le menu client.                                                            ||\n\
||		3. Le menu employ�.                                                           ||\n\
||		4. Le menu s�jour.                                                            ||\n\
||                                                                                            ||\n\
|| Il peut aussi revenir � l'�cran d'accueil s'il souhaite chercher une information dans le   ||\n\
|| mode d'emploi ou s'il souhaite quitter le programme.                                       ||\n\
||============================================================================================||\n"));
}

void meEmplacement() {
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Le menu emplacement %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	sdl();sdl();
	printf("%s", Accent("|| Depuis ce menu, le gestionnaire peut :                                                     ||\n\
||                                                                                            ||\n\
||		1. Afficher la liste des emplacements.                                        ||\n\
||		2. Ajouter un emplacement.                                                    ||\n\
||		3. Supprimer un emplacement.                                                  ||\n\
||		4. Modifier un emplacement.                                                   ||\n\
||		5. Revenir au menu principal.                                                 ||\n\
||                                                                                            ||\n\
|| L'affichage des emplacements donne, pour chaque emplacement, son ID, si l'emplacement est  ||\n\
|| un emplacement pour tente, caravane ou bungalow, la disponibilit�, ou non, d'�lectricit�,  ||\n\
|| la taille (en m�) et le prix (en euros) de l'emplacement.                                  ||\n\
||                                                                                            ||\n\
|| Pour l'ajout d'un emplacement il suffit de saisir toutes les informations cit�es ci-dessus ||\n\
|| , mis � part l'ID, qui est g�n�r� automatiquement. Le programme demande ensuite une        ||\n\
|| confirmation pour l'ajout. Si le gestionnaire souhaite supprimer un emplacement, il lui    ||\n\
|| suffit d'entrer l'ID de l'emplacement dont la suppression est souhait�e, puis de confirmer ||\n\
|| son choix.                                                                                 ||\n\
||                                                                                            ||\n\
|| Enfin, la modification d'emplacement se fait par s�lection de l'ID de l'emplacement �      ||\n\
|| modifier. Une confirmation de ce choix est ensuite demand�e. Si le gestionnaire confirme   ||\n\
|| son choix, il ne lui reste qu'� entrer les nouvelles informations concernant l'emplacement ||\n\
|| s�lectionn�.                                                                               ||\n\
||                                                                                            ||\n\
|| A noter : pour toutes ces options, le programme v�rifie les donn�es entr�es. Il est donc   ||\n\
|| impossible de donner une taille ou un prix d'emplacement trop �lev� ou trop bas, ainsi que ||\n\
|| d'entrer du texte lorsque c'est un nombre qui est demand�.                                 ||\n\
||============================================================================================||\n"));
}

void meClients() {
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Le menu clients %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	sdl();sdl();
	printf("%s", Accent("|| Le menu client permet � l'utilisateur :                                                    ||\n\
||                                                                                            ||\n\
||		1. D'afficher la liste des clients.                                           ||\n\
||		2. Ajouter un nouveau client.                                                 ||\n\
||		3. Client existant.                                                           ||\n\
||		4. Revenir au menu principal.                                                 ||\n\
||                                                                                            ||\n\
|| La liste des clients contient les ID, noms et pr�noms de chaque client. L'ajout d'un       ||\n\
|| client ne demande que son nom et son pr�nom. L'ID est ici aussi g�n�r� automatiquement.    ||\n\
|| Lorsque l'utilisateur choisi et confirme un client existant d�j�  dans les donn�es du      ||\n\
|| camping, il acc�de � un nouveau sous-menu.                                                 ||\n\
||                                                                                            ||\n\
|| Menu d'un client :                                                                         ||\n\
|| D�s que l'utilisateur a choisi un client sp�cifique, un nouveau menu est affich� pour      ||\n\
|| traiter ce client. Ce menu permet :                                                        ||\n\
||		1. D'afficher la liste de s�jours du client.                                  ||\n\
||		2. D'effectuer une nouvelle r�servation.                                      ||\n\
||		3. De modifier une de ses r�servations.                                       ||\n\
||		4. Faire payer le s�jour au client.                                           ||\n\
||		5. Revenir au menu des clients.                                               ||\n\
||                                                                                            ||\n\
|| La liste des s�jours pour le client choisi contient l'ID du s�jour, sa formule (tente,     ||\n\
|| bungalow, caravane), le nombre de personnes, la date et le prix (en �) de chaque s�jour.   ||\n\
||                                                                                            ||\n\
|| Ensuite, pour effectuer une nouvelle r�servation, l'utilisateur doit entrer la date de     ||\n\
|| cette r�servation. La date permet de v�rifier si le client n'a pas d�j� un s�jour pr�vu �  ||\n\
|| cette date. Si c'est le cas, l'utilisateur est pr�venu de ce s�jour et les d�tails de      ||\n\
|| cette r�servation sont affich�s. Dans le cas contraire, la liste des emplacements libres   ||\n\
|| est affich�e (l'affichage contient les m�mes informations que pour l'affichage de tous les ||\n\
|| emplacements du camping. Cf. le menu emplacement). L'utilisateur entre l'ID de             ||\n\
|| l'emplacement souhait� par le client. Apr�s confirmation de l'emplacement, l'utilisateur   ||\n\
|| entre le nombre de personnes qui vont s�journer. Lorsque c'est fait, si la r�servation est ||\n\
|| confirm�e, le s�jour est valid� et ajout�.                                                 ||\n\
||                                                                                            ||\n\
|| La suppression d'un s�jour se fait en entrant l'ID du s�jour dont la suppression est       ||\n\
|| souhait�e. La liste des s�jours est affich�e pour permettre de voir les diff�rents s�jours.||\n\
|| Le s�jour est supprim� si l'utilisateur confirme la suppression.                           ||\n\
||                                                                                            ||\n\
|| La m�me logique est suivie pour le paiement d'un s�jour, la liste des s�jours du client    ||\n\
|| est affich�e et il ne reste � l'utilisateur qu'� entrer l'ID du s�jour qu'il souhaite      ||\n\
|| payer. Le programme pr�vient l'utilisateur si le s�jour a d�j� �t� pay� par le client. Si  ||\n\
|| le s�jour n'a pas �t� pay�, le programme attend une confirmation de payement. Lorsque le   ||\n\
|| payement est effectu�, le montant du s�jour est ajout� au budget du camping.               ||\n\
||============================================================================================||\n"));
}

void meEmployes() {
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("%s", Accent("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Le menu employ� %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n"));
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	sdl();sdl();
	printf("%s", Accent("|| En ce qui concerne la gestion des employ�s, le gestionnaire du camping peut :              ||\n\
||                                                                                            ||\n\
||		1. Afficher la liste des employ�s.                                            ||\n\
||		2. Ajouter un employ�.                                                        ||\n\
||		3. Supprimer un employ�.                                                      ||\n\
||		4. Ajouter une demi-journ�e de travail � un employ�.                          ||\n\
||		5. Modifier le salaire d'un employ�.                                          ||\n\
||		6. Payer les employ�s.                                                        ||\n\
||		7. Revenir au menu principal.                                                 ||\n\
||                                                                                            ||\n\
|| L'affichage de la liste des employ�s indique, pour chaque employ�, son ID, ses noms et     ||\n\
|| pr�noms, le salaire (en euros) et le nombre d'heures prest�es. Ensuite, l'ajout d'employ�  ||\n\
|| requiert les informations cit�es ci-dessus, mis � part l'ID g�n�r� automatiquement.        ||\n\
||                                                                                            ||\n\
|| La suppression d'employ� ne demande que son ID et une confirmation de suppression. S'il y  ||\n\
|| a confirmation, l'utilisateur peut choisir de payer ou non l'employ� qu'il supprime.       ||\n\
||                                                                                            ||\n\
|| Il est possible d'ajouter une ou plusieurs demi-journ�e(s) de travail � un employ�. Chaque ||\n\
|| demi-journ�e �quivaut � 4h de travail. Le nombre de demi-journ�e(s) ajout�e(s) est         ||\n\
|| convertit en heures et ces heures sont ajout�es au total d'heures prest�es par l'employ�.  ||\n\
||                                                                                            ||\n\
|| Un salaire n'est pas fixe, il peut �tre revu � la baisse ou � la hausse par le             ||\n\
|| gestionnaire. Pour modifier un salaire, l'utilisateur entre l'ID de l'employ� et confirme  ||\n\
|| son choix.                                                                                 ||\n\
||                                                                                            ||\n\
|| Il est possible de payer l'employ� avant de modifier son salaire. En cas de payement avant ||\n\
|| un changement de salaire, le total d'heures est remis � 0 puisque ses heures ont �t�       ||\n\
|| pay�es.                                                                                    ||\n\
||                                                                                            ||\n\
|| Pour terminer, l'utilisateur peut payer les employ�s. Il peut choisir de payer tous les    ||\n\
|| employ�s, ou d'en s�lectionner un et de le payer. A noter : lors d'un payement de salaire, ||\n\
|| le total pay� est d�duit du budget du camping.                                             ||\n\
||============================================================================================||\n"));
}

void meSejour() {
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("%s", Accent("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Le menu s�jour %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n"));
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	sdl();sdl();
	printf("%s", Accent("|| Ce menu permet � l'utilisateur :                                                           ||\n\
||                                                                                            ||\n\
||		1. Afficher la liste des s�jours r�serv�s aux camping.                        ||\n\
||		2. Voir la liste des emplacements disponibles.                                ||\n\
||		3. Revenir au menu principal.                                                 ||\n\
||                                                                                            ||\n\
|| Si l'utilisateur affiche la liste des s�jours, il aura comme information l'ID du s�jour,   ||\n\
|| la formule (tente, bungalow, caravane), le nombre de personnes, la date et le prix         ||\n\
|| (en euros) de chaque s�jour.                                                               ||\n\
||                                                                                            ||\n\
|| L'utilisateur peut aussi afficher la liste des emplacements disponibles pour une date      ||\n\
|| choisie. Cf. le menu emplacement pour les informations affich�es � l'�cran.                ||\n\
||============================================================================================||\n"));
}
