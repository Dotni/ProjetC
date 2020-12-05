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
#include "structures/emplacement.h"
#include "structures/sejour.h"
#include "structures/client.h"
#include "structures/employe.h"


void main(){
	//déclaration des variables
	int choixMP, choixIntro,choixEmplacement,choixClient,choixEmploye,choixSejour;
	emplacement empl[30];
	
	FILE *Fclient, *Femplacement, *Femploye, *Fsejour;
	
	//ouverture des fichiers
	
	//définition des fonctions
	//fonctions utiles
	char * accent(const char *);							//permet d'afficher les accents
	int lire(char *, int);
	int verifier(char[]);
	void viderBuffer();
	
	//fonctions graphiques
	void sdl();												//saut de ligne
	int intro();
	int menuEmplacement();											//fonction intro
	int menuPrincipal();												//fonction menu
	int modeEmploi();										// accéder au mode d'emploi du projet
	
	
	
	do{
		choixIntro = intro();
		switch(choixIntro) {
			case 1: // accéder au menu principal
				do{
					choixMP=menuPrincipal();
					switch(choixMP){
						case 1: 
							choixEmplacement=menuEmplacement();
							affichageListeEmplacement(empl);
							//printf("%2d",tailleEmplacement);
							system("PAUSE");
							break;
						case 2:
							choixClient=menuClient();
							break;
						case 3:
							choixEmploye=menuEmploye();
							break;
						case 4:
							choixSejour=menuSejour();
							break;		
					}
				}while(choixMP!=5);
				break;
			case 2: // accéder au mode d'emploi
				modeEmploi();
				break;
			default: // sécurité, ne devrait pas arriver puisque le choix est déjà contrôlé dans la fonction intro
				break;
		}
	}while(choixIntro!=3);
}

//permet d'afficher les accents
char * Accent(const char * message) {
      static char retour [80];
      CharToOem (message, retour); // API Windows
      return retour;
   }

void sdl(){ //saut de ligne
	printf("||                                                                                            ||\n");
}

int intro(){
		int choix = 0;
		short first=0;
		char tmp[2];
		
		//on effectue cette boucle tant que l'utilisateur n'a pas fait de choix valide
		do{
			//si l'utilisateur n'a pas fait d'erreur
			if(first==0){
				printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
				printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PROGRAMME DE GESTION D'UN CAMPING %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
				printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
				sdl();sdl();
				printf("||                   --------------------------------------------------------                 ||\n");
				printf("||                   || Bienvenue dans le programme de gestion du camping! ||                 ||\n");
				printf("||                   --------------------------------------------------------                 ||\n");
				first=1;					//permet de dire que ce n'est pas la premiere fois qu'on passe dans la boucle	
			}
			//si l'utilisateur a fait une erreur
			else{
				system("cls");
				printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
				printf("||                              Veuillez entrer un nombre valide!                             ||\n");
				printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			}
			
			//code commun (peut importe si l'utilisateur a fait une erreur ou pas)
			sdl();sdl();
			printf("||                                   Que souhaitez-vous faire?                                ||\n");
			printf ("%s",Accent("||                         (entrez le numéro correspondant à votre choix)                     ||\n"));
			sdl();sdl();
			printf ("%s",Accent("||  1.  Accéder au menu principal                                                             ||\n"));
			printf("||  2.  Mode d'emploi                                                                         ||\n");
			printf("||  3.  Quitter le programme                                                                  ||\n");
			sdl();sdl();
			printf("||  Votre choix :                                                                             ||\n");
			choix = lire(tmp, 2);
		}while(choix<1||choix>3);
		
		system("cls");
		return choix;
}

int menuPrincipal(){
	int choix=0;
	short first=0;
	char tmp[2];
	
	//on effectue cette boucle tant que l'utilisateur n'a pas fait de choix valide
	do{
		//si l'utilisateur n'a pas fait d'erreur
		if(first==0){
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Menu Principal %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			first=1;	
		}
		//si l'utilisateur a fait une erreur
		else{
			system("cls");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||                              Veuillez entrer un nombre valide!                             ||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
		}
		
		//code commun (peut importe si l'utilisateur a fait une erreur ou pas)
		sdl();sdl();
		printf ("%s",Accent("|| Entrez le numéro correspondant à votre choix                                               ||\n"));
		sdl();sdl();
		printf ("%s",Accent("||  1.  Emplacement                                                                           ||\n"));
		printf("||  2.  Client                                                                                ||\n");
		printf("||  3.  Employe                                                                               ||\n");
		printf ("%s",Accent("||  4.  Séjour                                                                                ||\n"));	
		printf("||  5.  Retour                                                                                ||\n");
		sdl();sdl();
		printf("||  Votre choix :                                                                             ||\n");
		choix = lire(tmp, 2);
	}while(choix<1||choix>5);
	system("cls");
	return choix;		
}

int menuEmplacement(){
	int choix=0;
	short first=0;
	char tmp[2];
	
	do{
		if(first==0){
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Menu Emplacement %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
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
		printf ("%s",Accent("|| Entrez le numéro correspondant à votre choix                                               ||\n"));
		sdl();sdl();
		printf ("%s",Accent("||  1.  Liste des emplacements                                                                ||\n"));
		printf("||  2.  Ajouter un emplacement                                                                ||\n");
		printf("||  3.  Supprimer un emplacement                                                              ||\n");
		printf ("%s",Accent("||  4.  Modifier un emplacement                                                               ||\n"));	
		printf("||  5.  Retour                                                                                ||\n");
		sdl();sdl();
		printf("||  Votre choix :                                                                             ||\n");
		choix = lire(tmp, 2);
		
	}while(choix<1||choix>5);
	system("cls");
	return choix;		
}

int menuClient(){
	int choix=0;
	short first=0;
	char tmp[2];
	
	do{
		if(first==0){
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Menu Client %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
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
		printf ("%s",Accent("|| Entrez le numéro correspondant à votre choix                                               ||\n"));
		sdl();sdl();
		printf ("%s",Accent("||  1.  Liste des clients                                                                     ||\n"));
		printf("||  2.  Ajouter un client                                                                     ||\n");
		printf ("%s",Accent("||  3.  Effectuer une réservation                                                             ||\n"));
		printf ("%s",Accent("||  4.  Modifier une réservation                                                              ||\n"));	
		printf("||  5.  Retour                                                                                ||\n");
		sdl();sdl();
		printf("||  Votre choix :                                                                             ||\n");
		choix = lire(tmp, 2);
		
	}while(choix<1||choix>5);
	system("cls");
	return choix;	
}

int menuEmploye(){
	int choix=0;
	short first=0;
	char tmp[2];
	
	do{
		if(first==0){
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf ("%s",Accent("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Menu employé %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n"));
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
		printf ("%s",Accent("|| Entrez le numéro correspondant à votre choix                                               ||\n"));
		sdl();sdl();
		printf ("%s",Accent("||  1.  Liste des employés                                                                    ||\n"));
		printf ("%s",Accent("||  2.  Ajouter un employé                                                                    ||\n"));
		printf ("%s",Accent("||  3.  Supprimer un employé                                                                  ||\n"));
		printf ("%s",Accent("||  4.  Ajouter une journée/demi journée de travail à un employé                              ||\n"));
		printf ("%s",Accent("||  5.  Modifier le salaire d'un employé                                                      ||\n"));
		printf ("%s",Accent("||  6.  Payer Les employés                                                                    ||\n"));	
		printf("||  7.  Retour                                                                                ||\n");
		sdl();sdl();
		printf("||  Votre choix :                                                                             ||\n");
		choix = lire(tmp, 2);
		
	}while(choix<1||choix>7);
	system("cls");
	return choix;	
}

int menuSejour(){
	int choix=0;
	short first=0;
	char tmp[2];
	
	do{
		if(first==0){
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf ("%s",Accent("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Menu Séjour %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n"));
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
		printf ("%s",Accent("|| Entrez le numéro correspondant à votre choix                                               ||\n"));
		sdl();sdl();
		printf ("%s",Accent("||  1.  Liste des séjours                                                                     ||\n"));
		printf ("%s",Accent("||  2.  Liste des emplacements disponibles                                                    ||\n"));
		printf("||  3.  Retour                                                                                ||\n");
		sdl();sdl();
		printf("||  Votre choix :                                                                             ||\n");
		choix = lire(tmp, 2);
		
	}while(choix<1||choix>3);
	system("cls");
	return choix;
}

int modeEmploi() {
	printf("On le fera en dernier c'est que de l'affichage\n");
	sdl();
	sdl();
	return 0;
}

int verifier(char saisie[]) { // vérifier que la saisie est correcte
	int ok = 1, i = 0;
	while(saisie[i] != '\0') {
		if (!isdigit(saisie[i])) {
			printf("pas un nombre\n");
			return 0;
		}
		i++;
	}
	return ok;
}

void viderBuffer(){
    int c = 0;
    while (c != '\n' && c != EOF){
        c = getchar();
    }
}

int lire(char *chaine, int longueur){
    char *positionln = NULL;
 	
    // On lit le texte saisi au clavier
	if (fgets(chaine, longueur, stdin) != NULL) {
        positionln = strchr(chaine, '\n'); 
        if (positionln != NULL) {
            *positionln = '\0'; // On remplace ce caractère par \0
        }
        else {
        	viderBuffer();
		}
		if(verifier(chaine) == 0) {
 			return 0;
		}
        return atoi(chaine);
    }
    else{
    	viderBuffer();
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}
