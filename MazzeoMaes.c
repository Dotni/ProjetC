/********************************************************************************************
*****************************Projet C : gestion d'un camping*********************************
*********************************************************************************************
Nom : Mazzeo  			Prenom : Florian
Nom : Maes    			Prenom : Martin

nom fichier : MazzeoMaes.c
date : 30/11/2020 
**********************************************************************************************
**********************************************************************************************
**********************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "structures/emplacement.h"
#include "structures/sejour.h"
#include "structures/client.h"
#include "structures/employe.h"

void main(){
	//déclaration des variables
	int choixMP, choixIntro;
	
	FILE *Fclient, *Femplacement, *Femploye, *Fsejour;
	
	//ouverture des fichiers
	/////////////////////////////////////////////////////
	//////////////définition des fonctions///////////////
	/////////////////////////////////////////////////////
	
	//fonctions utiles
	char * accent(const char *);							//permet d'afficher les accents
	
	//fonctions graphiques
	void sdl();												//saut de ligne
	int intro();											//fonction intro
	int menu();												//fonction menu
	void quitter();											//quitter la gestion
	void modeEmploi();										// accéder au mode d'emploi du projet
	
	choixIntro = intro();
	
	switch(choixIntro) {
		case 1: // accéder au menu principal
			menu();
			break;
		case 2: // accéder au mode d'emploi
			modeEmploi();
			break;
		case 3: // quitter
			quitter();
			break;
		default: // sécurité, ne devrait pas arriver puisque le choix est déjà contrôlé dans la fonction intro
			quitter();
			break;
	}
}

//permet d'afficher les accents
char * Accent(const char * mess) {
      static char retour [80];
      CharToOem (mess,retour); // API Windows
      return retour;
   }

//saut de ligne
void sdl(){
	printf("||                                                                                            ||\n");
}

int intro(){
		int choix=0;
		
		printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
		printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PROGRAMME DE GESTION D'UN CAMPING %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
		printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
		sdl();sdl();
		printf("||                   --------------------------------------------------------                 ||\n");
		printf("||                   || Bienvenue dans le programme de gestion du camping! ||                 ||\n");
		printf("||                   --------------------------------------------------------                 ||\n");
		sdl();sdl();
		printf("||                                   Que souhaitez-vous faire?                                ||\n");
		printf ("%s",Accent("||                         (entrez le numéro correspondant à votre choix)                     ||\n"));
		sdl();sdl();
		printf ("%s",Accent("||  1.  Accéder au menu principal                                                             ||\n"));
		printf("||  2.  Mode d'emploi                                                                         ||\n");
		printf("||  3.  Quitter le programme                                                                  ||\n");
		sdl();sdl();
		printf("||  Votre choix :                                                                             ||\n");
		scanf("%d",&choix);
		
		while(choix<1||choix>3){
			system("cls");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			printf("||                              Veuillez entrer un nombre valide!                             ||\n");
			printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
			sdl();sdl();
			printf("||                                   Que souhaitez-vous faire?                                ||\n");
			printf ("%s",Accent("||                         (entrez le numéro correspondant à votre choix)                     ||\n"));
			sdl();sdl();
			printf ("%s",Accent("||  1.  Accéder au menu principal                                                             ||\n"));
			printf("||  2.  Mode d'emploi                                                                         ||\n");
			printf("||  3.  Quitter le programme                                                                  ||\n");
			sdl();sdl();
			printf("||  Votre choix :                                                                             ||\n");
			scanf("%d",&choix);	
		}
		system("cls");
		return choix;
}

int menu(){
	printf("niquel");
}

void quitter() {
	printf("%s", Accent("A très vite !"));
}

void modeEmploi() {
	printf("mode emploi");
}
