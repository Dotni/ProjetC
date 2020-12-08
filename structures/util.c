#include <stdio.h>
#include <windows.h>
#include <ctype.h>

//saut de ligne
void sdl(){ 
	printf("||                                                                                            ||\n");
}

//permet d'afficher les accents
char * Accent(const char * message) {
      static char retour [100];
      CharToOem (message, retour); // API Windows
      return retour;
}
   
int verifier(char saisie[]) { // vérifier que la saisie est correcte
	int ok = 1, i = 0;
	while(saisie[i] != '\0') {
		if (!isdigit(saisie[i])) {
			printf("Votre saisie n'est pas un nombre, veuillez entrer un nombre correct.\n");
			return 0;
		}
		i++;
	}
	return ok;
}

float verifierFloat(char saisie[]) { // vérifier que la saisie est correcte
	float ok = 1;
	int i = 0, nb = 0;
	while(saisie[i] != '\0') {
		if (!isdigit(saisie[i])&&saisie[i] != '.') {
			printf("Votre saisie n'est pas un nombre, veuillez entrer un nombre correct.\n");
			return 0;	
		}
		if(saisie[i]=='.'){
			nb++;
			if(nb>1){
				printf("Votre saisie n'est pas un nombre, veuillez entrer un nombre correct.\n");
				return 0;
			}
		}
		i++;
	}
	return ok;
}

int verifierDate(char saisie[]) { // vérifier la saisie de date
	int ok = 1;
	
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

char * lireDate(char *chaine, int longueur) {
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
		if(verifierDate(chaine) == 0) {
 			return 0;
		}
        return chaine;
    }
    else{
    	viderBuffer();
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}

float lireFloat(char *chaine, int longueur){
    char *positionln = NULL;

	if (fgets(chaine, longueur, stdin) != NULL) { // On lit le texte saisi au clavier
        positionln = strchr(chaine, '\n'); 
        if (positionln != NULL) {
            *positionln = '\0'; // On remplace ce caractère par \0
        }
        else {
        	viderBuffer();
		}
		if(verifierFloat(chaine) == 0) {
 			return 0;
		}
        return atof(chaine);
    }
    else{
    	viderBuffer();
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}


//affiche le titre global de la fenetre
void affichageTitre(char titre[], int tailleTitre){
	//longueur totale du titre = 65
	//espace des deux cotés du titre 65-2=63  
	//taille totale - taille du titre = taille des  "="
	//taille des "=" /2 = taille des égals a gauche
	//comme ca peut etre un nombre impair, taille des égals a gauche n'est pas forcément égal a taille des égals a droite
	//donc on le recalcule avec la formule 61-taille des égals a gauche - taille du titre;
	int taille = strlen(titre);
	int gauche = (tailleTitre - taille) / 2;
	int droite = tailleTitre - gauche - taille ;
	int i;
	system("cls");
	for(i = 0 ; i <= tailleTitre+1 ; i++){
		printf("=");
	}
	printf("\n");
	for(i = 1 ; i <= gauche ; i++){
		printf("=");
	}
	printf(" %s ",titre);
	for(i = 1 ; i <= droite ; i++){
		printf("=");
	}
	printf("\n");
	for(i = 0 ; i <= tailleTitre+1 ; i++){
		printf("=");
	}
	printf("\n\n");
}

void affichageTypeEmplacement(int i){
	//affichage du type
	if(i == 1){
		printf("  Tente  | ");
	}
	else if(i == 2){
		printf("Caravane | ");
	}
	else{
		printf("Bungalow | ");
	}
}

int choixEntier(int inf, int sup,int taille){
	char tmp[taille+1];		//attention, il y a tjrs le char \0 a la fin, donc taille + 1
	int i = 0,choix;
	do{
		if(i != 0){
			printf("Veuillez entrer un nombre correct! (compris entre %d et %d)\n Votre choix :",inf,sup);
		}
		choix = lire(tmp, taille+1);
		printf("%2d",choix);
		i++;
	}while(choix < inf || choix > sup);
	return choix;
}


float choixReel(float inf, float sup,int taille){
	char tmp[taille+1];		//attention, il y a tjrs le char \0 a la fin, donc taille + 1
	int i = 0;
	float choix;
	do{
		if(i != 0){
			printf("Veuillez entrer un nombre correct! (compris entre %6.2f et %6.2f)\n Votre choix :",inf,sup);
		}
		choix = lireFloat(tmp, taille+1);
		i++;
	}while(choix < inf || choix > sup);
	return choix;
}



