#ifndef SEJOUR_H
#define SEJOUR_H

//d�finition d'un s�jour
typedef struct sejour{
	short id;
	short idClient;
	short formule;						//1 pour tente , 2 pour caravane, 3 pour bungalow
	short nbPersonnes;					//nombre de personnes pour qui
	char date[11];						//sous le format dd/mm/yyyy
	float prix;							//prix du s�jour
	short electricite;					//1 si il faut de l'�lectricit�, 0 si non
	struct sejour *nxtSej;
	struct emplacement *place;
}sejour;

void afficherListeSejours();
void afficherEmplacementsLibres(char[]);
int lectureSejours(sejour*);
void viderSejours(sejour*);
void switchMenuSejour(int);
char* demanderdate();

#endif
