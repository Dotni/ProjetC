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
		if (!isdigit(saisie[i]) && saisie[i] != '.') {
			printf("Votre saisie n'est pas un nombre, veuillez entrer un nombre correct.\n");
			return 0;	
		}
		if(saisie[i] == '.'){
			nb++;
			if(nb > 1){
				printf("Votre saisie n'est pas un nombre, veuillez entrer un nombre correct.\n");
				return 0;
			}
		}
		i++;
	}
	return ok;
}

void extraire(int debut, int fin, char *chaine, char *sousChaine) { // extrait une chaine depuis une autre
	int i, j, longueur = strlen(chaine);
  
	if(debut > longueur || fin < 0 || fin > longueur) { // vérification des bornes
		return;
	}
	for(i = debut, j = 0 ; i <= fin ; i++, j++) {
		sousChaine[j] = chaine[i];
	}
	sousChaine[j + 1] = '\0';
}

int verifierDate(char saisie[]) { // vérifier la saisie de date
	char cJour[3] = {0}, cMois[3] = {0}, cAnnee[5] = {0};
	int jour, mois, annee, i;
	if(strlen(saisie) != 10) {
		return 0;
	}
	// on vérifie que le format de la date est bien xx/xx/xxxx
	for(i = 0 ; i <= 9 ; i++) {
		if(i != 2 && i != 5) {
			if(!isdigit(saisie[i])) {
				return 0;
			}
		}
		else {
			if(saisie[i] != '/') {
				return 0;
			}
		}
	}
	// extraction des jours mois et années
	extraire(0, 1, saisie, cJour);
	extraire(3, 4, saisie, cMois);
	extraire(6, 9, saisie, cAnnee);
	// convertion en entiers pour récupérer les possibles erreurs
	jour = atoi(cJour);
	mois = atoi(cMois);
	annee = atoi(cAnnee);
	
	if((mois==4||mois==6||mois==9||mois==11)&&jour==31){
		return 0;
	}
	
	// vérification du jour (entre 1 et 31), sauf pour février 
	if(mois != 2 && (jour < 1 || jour > 31)) {
		return 0;
	}
	else if(mois == 2 && (jour < 1 || jour > 29)) { // mois de février
		printf("erreuyr");
		system("pause");
		return 0;
	}
	// v?rification du mois
	if(mois < 1 || mois > 12) {
		return 0;
	}
	// vérification de l'année
	if(annee < 2020) {
		return 0;
	}
	return 1;
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

char * lireString(char *chaine, int longueur){
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
        return chaine;
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
	for(i = 0 ; i <= tailleTitre + 1 ; i++){
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
	for(i = 0 ; i <= tailleTitre + 1 ; i++){
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
	char tmp[taille + 1];		//attention, il y a tjrs le char \0 a la fin, donc taille + 1
	int i = 0, choix;
	do{
		if(i != 0){
			printf("Veuillez entrer un nombre correct! (compris entre %d et %d)\n Votre choix :",inf,sup);
		}
		choix = lire(tmp, taille + 1);
		i++;
	}while(choix < inf || choix > sup);
	return choix;
}

float choixReel(float inf, float sup,int taille){
	char tmp[taille + 1];		//attention, il y a tjrs le char \0 a la fin, donc taille + 1
	int i = 0;
	float choix;
	do{
		if(i != 0){
			printf("Veuillez entrer un nombre correct! (compris entre %6.2f et %6.2f)\n Votre choix :",inf,sup);
		}
		choix = lireFloat(tmp, taille + 1);
		i++;
	}while(choix < inf || choix > sup);
	return choix;
}
