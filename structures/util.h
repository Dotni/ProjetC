#ifndef UTIL_H
#define UTIL_H

void sdl();								//saut de ligne
char * Accent(const char *);			//permet d'afficher les accents
int lire(char *, int);					//lecture d'entrées
int verifier(char[]);					//vérification d'entrée
float lireFloat(char *, int);			//lecture d'entrées
char * lireDate(char *, int);			// lecture de dates
int verifierdate(char[]);				// vérification de dates
float verifierFloat(char[]);			//vérification d'entrée
void viderBuffer();						//vider buffer
void affichageTitre(char [], int);
void affichageTypeEmplacement(int);
int fchoixEntier(int, int, int);
float choixReel(float , float ,int );
void extraire(int, int, char*, char*);
#endif
