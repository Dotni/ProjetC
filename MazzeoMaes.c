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
#include <ctype.h>
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
	int intro();
	int menuEmplacement();											//fonction intro
	int menuPrincipal();												//fonction menu
	void modeEmploi();										// accéder au mode d'emploi du projet
	
	do{
		choixIntro = intro();
		switch(choixIntro) {
			case 1: // accéder au menu principal
			
				do{
					choixMP=menuPrincipal();
					switch(choixMP){
						case 1: 
							printf("case 1");
							break;
						case 2:
							printf("case 2");
							break;
						case 3:
							printf("case 3");
							break;
							
						case 4:
							printf("case 4");
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
		char stTemp[2];
 
		
		
		char tmp;
		
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
		scanf("%c",&tmp);
		sprintf(stTemp,"%c",tmp);
		choix = atoi(stTemp);
		if(isdigit(tmp)>0){
			//choix=atoi(tmp-'0');
		}
		
		while(isdigit(tmp)==0||choix<1||choix>3){
			//system("cls");
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
			scanf("%c",&tmp);	
			if(isdigit(tmp)>0){
				//choix=(int)tmp;
			}
		}
		//system("cls");
		return choix;
}

int menuPrincipal(){
	
	int choix=0;
	
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Menu Principal %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
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
	scanf("%d",&choix);
		
	while(choix<1||choix>5){
		system("cls");
		printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
		printf("||                              Veuillez entrer un nombre valide!                             ||\n");
		printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
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
		scanf("%d",&choix);
	}
	system("cls");
	return choix;		
}

int menuEmplacement(){
	int choix=0;
	
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Menu Emplacement %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
	printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
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
	scanf("%d",&choix);
		
	while(choix<1||choix>5){
		system("cls");
		printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
		printf("||                              Veuillez entrer un nombre valide!                             ||\n");
		printf("||%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%||\n");
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
		scanf("%d",&choix);
	}
	system("cls");
	return choix;		
}

int menuClient(){
}

int menuEmploye(){
}

int menuSejour(){
}

void modeEmploi() {
	printf("On le fera en dernier c'est que de l'affichage\n");
	sdl();
	sdl();
}
