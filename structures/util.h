#ifndef UTIL_H
#define UTIL_H

void sdl();								//saut de ligne
char * Accent(const char *);			//permet d'afficher les accents
int lire(char *, int);					//lecture d'entr�es
int verifier(char[]);					//v�rification d'entr�e
float lireFloat(char *, int);					//lecture d'entr�es
char * lireDate(char *, int);
float verifierFloat(char[]);					//v�rification d'entr�e
void viderBuffer();						//vider buffer
void affichageTitre(char [], int);
void affichageTypeEmplacement(int);
int fchoixEntier(int, int, int);
float choixReel(float , float ,int );
#endif
