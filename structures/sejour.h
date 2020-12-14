#ifndef SEJOUR_H
#define SEJOUR_H

//définition d'un séjour
typedef struct sejour{
	short id;
	short idClient;
	short formule;						//1 pour tente , 2 pour caravane, 3 pour bungalow
	short nbPersonnes;					//nombre de personnes pour qui
	char date[11];						//sous le format dd/mm/yyyy
	float prix;							//prix du séjour
	short paye;
	struct sejour *nxtSej;
	struct emplacement *place;
}sejour;

void afficherUnSejour(sejour*);
void afficherListeSejours();
int lectureSejours(sejour*);
void viderSejours(sejour*);
void switchMenuSejour(int);
char* demanderdate();
sejour * getPremierSej();
int getDernierSej();
#endif
