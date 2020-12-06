#ifndef SEJOUR_H
#define SEJOUR_H

//définition d'un séjour
typedef struct sejour{
	short formule;						//1 pour tente , 2 pour caravane, 3 pour bungalow
	short nbPersonne;					//nombre de personnes pour qui
	char date[11];						//sous le format dd/mm/yyyy
	float prix;							//prix du séjour
	short electricite;					//1 si il faut de l'électricité, 0 si non
	struct sejour *nxtSej;
	struct emplacement *place;
}sejour;

void afficherListeSejours();
void afficherEmplacementsLibres();
int lectureSejours();
void switchMenuSejour(int);

#endif
