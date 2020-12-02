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
	//d�claration des variables
	int choixMP, choixIntro;
	
	FILE *Fclient, *Femplacement, *Femploye, *Fsejour;
	
	//ouverture des fichiers
	/////////////////////////////////////////////////////
	//////////////d�finition des fonctions///////////////
	/////////////////////////////////////////////////////
	
	//fonctions utiles
	char * accent(const char *);							//permet d'afficher les accents
	
	//fonctions graphiques
	void sdl();												//saut de ligne
	int intro();											//fonction intro
	int menu();												//fonction menu
	void modeEmploi();										// acc�der au mode d'emploi du projet
	
	do{
		choixIntro = intro();
		switch(choixIntro) {
			case 1: // acc�der au menu principal
				menu();
				break;
			case 2: // acc�der au mode d'emploi
				modeEmploi();
				break;
			default: // s�curit�, ne devrait pas arriver puisque le choix est d�j� contr�l� dans la fonction intro
				break;
		}
	}while(choixIntro!=3);
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
		int choix=0,ret=1;
		
		printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
		printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  PROGRAMME DE GESTION D'UN CAMPING %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
		printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
		sdl();sdl();
		printf("||                   --------------------------------------------------------                 ||\n");
		printf("||                   || Bienvenue dans le programme de gestion du camping! ||                 ||\n");
		printf("||                   --------------------------------------------------------                 ||\n");
		sdl();sdl();
		printf("||                                   Que souhaitez-vous faire?                                ||\n");
		printf ("%s",Accent("||                         (entrez le num�ro correspondant � votre choix)                     ||\n"));
		sdl();sdl();
		printf ("%s",Accent("||  1.  Acc�der au menu principal                                                             ||\n"));
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
			printf ("%s",Accent("||                         (entrez le num�ro correspondant � votre choix)                     ||\n"));
			sdl();sdl();
			printf ("%s",Accent("||  1.  Acc�der au menu principal                                                             ||\n"));
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
	
	int choix=0;
	
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Menu Principal %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	sdl();sdl();
	printf ("%s",Accent("|| Entrez le num�ro correspondant � votre choix                                               ||\n"));
	sdl();sdl();
	printf ("%s",Accent("||  1.  Emplacement                                                                           ||\n"));
	printf("||  2.  Client                                                                                ||\n");
	printf("||  3.  Employe                                                                               ||\n");
	printf ("%s",Accent("||  4.  S�jour                                                                                ||\n"));	
	printf("||  5.  Retour                                                                                ||\n");
	printf("||  6.  Quitter                                                                               ||\n");
	sdl();sdl();
	printf("||  Votre choix :                                                                             ||\n");
	scanf("%d",&choix);
		
	while(choix<1||choix>6){
		system("cls");
		printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
		printf("||                              Veuillez entrer un nombre valide!                             ||\n");
		printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
		sdl();sdl();
		printf ("%s",Accent("|| Entrez le num�ro correspondant � votre choix                                               ||\n"));
		sdl();sdl();
		printf ("%s",Accent("||  1.  Emplacement                                                                           ||\n"));
		printf("||  2.  Client                                                                                ||\n");
		printf("||  3.  Employe                                                                               ||\n");
		printf ("%s",Accent("||  4.  S�jour                                                                                ||\n"));	
		printf("||  5.  Retour                                                                                ||\n");
		printf("||  6.  Quitter                                                                               ||\n");
		sdl();sdl();
		printf("||  Votre choix :                                                                             ||\n");
		scanf("%d",&choix);
	}
	system("cls");
	return choix;		
}

void modeEmploi() {
	printf("On le fera en dernier c'est que de l'affichage\n");
	sdl();
	sdl();
}
