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
			printf("pas un nombre\n");
			return 0;
		}
		i++;
	}
	return ok;
}

float verifierFloat(char saisie[]) { // vérifier que la saisie est correcte
	float ok = 1;
	int i = 0,nb=0;
	while(saisie[i] != '\0') {
		if (!isdigit(saisie[i])&&saisie[i]!='.') {
			printf("pas un nombre\n");
			return 0;	
		}
		if(saisie[i]=='.'){
			nb++;
			if(nb>1){
				printf("pas un nombre\n");
				return 0;
			}
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

float lireFloat(char *chaine, int longueur){
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
