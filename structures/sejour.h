#ifndef SEJOUR_H
#define SEJOUR_H

#include "emplacement.h"

//définition d'un séjour
typedef struct sejour{
	short id							//id du séjour
	short formule;						//1 pour tente , 2 pour caravane, 3 pour bungalow
	short nbPersonne;					//nombre de personnes pour qui
	char date[9];						//sous le format ddmmyyyy
	float prix;							//prix du séjours
	struct sejour *nxtSej;				//pour la liste chainnée
	struct emplacement place;           //emplacement attribué au séjour
}sejour;
#endif
