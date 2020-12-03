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
	//d�claration des variables
	int choixMP, choixIntro;
	
	FILE *Fclient, *Femplacement, *Femploye, *Fsejour;
	
	//ouverture des fichiers
	/////////////////////////////////////////////////////
	//////////////d�finition des fonctions///////////////
	/////////////////////////////////////////////////////
	
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
	void modeEmploi();										// acc�der au mode d'emploi du projet
	
	do{
		choixIntro = intro();
		switch(choixIntro) {
			case 1: // acc�der au menu principal
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
			case 2: // acc�der au mode d'emploi
				modeEmploi();
				break;
			default: // s�curit�, ne devrait pas arriver puisque le choix est d�j� contr�l� dans la fonction intro
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
		int choix = 0,ret = 1;
		char tmp[2];
		
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
		choix = lire(tmp, 2);
		printf("test apres    %d\n", choix);
		
		while(choix<1||choix>3){
			//system("cls");
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
			scanf("%c",&tmp);	
			/*if(isdigit(tmp)>0){
				//choix=(int)tmp;
			}*/
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
	printf ("%s",Accent("|| Entrez le num�ro correspondant � votre choix                                               ||\n"));
	sdl();sdl();
	printf ("%s",Accent("||  1.  Emplacement                                                                           ||\n"));
	printf("||  2.  Client                                                                                ||\n");
	printf("||  3.  Employe                                                                               ||\n");
	printf ("%s",Accent("||  4.  S�jour                                                                                ||\n"));	
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
		printf ("%s",Accent("|| Entrez le num�ro correspondant � votre choix                                               ||\n"));
		sdl();sdl();
		printf ("%s",Accent("||  1.  Emplacement                                                                           ||\n"));
		printf("||  2.  Client                                                                                ||\n");
		printf("||  3.  Employe                                                                               ||\n");
		printf ("%s",Accent("||  4.  S�jour                                                                                ||\n"));	
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
	printf ("%s",Accent("|| Entrez le num�ro correspondant � votre choix                                               ||\n"));
	sdl();sdl();
	printf ("%s",Accent("||  1.  Emplacement                                                                           ||\n"));
	printf("||  2.  Client                                                                                ||\n");
	printf("||  3.  Employe                                                                               ||\n");
	printf ("%s",Accent("||  4.  S�jour                                                                                ||\n"));	
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
		printf ("%s",Accent("|| Entrez le num�ro correspondant � votre choix                                               ||\n"));
		sdl();sdl();
		printf ("%s",Accent("||  1.  Emplacement                                                                           ||\n"));
		printf("||  2.  Client                                                                                ||\n");
		printf("||  3.  Employe                                                                               ||\n");
		printf ("%s",Accent("||  4.  S�jour                                                                                ||\n"));	
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

int verifier(char saisie[]) { // v�rifier que la saisie est correcte
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
            *positionln = '\0'; // On remplace ce caract�re par \0
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
















