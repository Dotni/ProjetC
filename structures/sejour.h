#ifndef SEJOUR_H
#define SEJOUR_H

//d�finition d'un s�jour
typedef struct sejour{
	short id;
	short formule;						//1 pour tente , 2 pour caravane, 3 pour bungalow
	short nbPersonne;					//nombre de personnes pour qui
	char date[11];						//sous le format dd/mm/yyyy
	float prix;							//prix du s�jour
	short electricite;					//1 si il faut de l'�lectricit�, 0 si non
	struct sejour *nxtSej;
	struct emplacement *place;
}sejour;

void afficherListeSejours();
void afficherEmplacementsLibres();
int lectureSejours(int, sejour[]);
void viderSejours(sejour[], int);
void switchMenuSejour(int, int, sejour[]);

#endif
