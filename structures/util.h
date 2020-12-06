#ifndef UTIL_H
#define UTIL_H

void sdl();								//saut de ligne
char * Accent(const char *);			//permet d'afficher les accents
int lire(char *, int);					//lecture d'entrées
int verifier(char[]);					//vérification d'entrée
float lireFloat(char *, int);					//lecture d'entrées
float verifierFloat(char[]);					//vérification d'entrée
void viderBuffer();						//vider buffer

#endif
