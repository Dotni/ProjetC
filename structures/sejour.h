#ifndef SEJOUR_H
#define SEJOUR_H

#include "emplacement.h"

//d�finition d'un s�jour
typedef struct sejour{
	short id							//id du s�jour
	short formule;						//1 pour tente , 2 pour caravane, 3 pour bungalow
	short nbPersonne;					//nombre de personnes pour qui
	char date[9];						//sous le format ddmmyyyy
	float prix;							//prix du s�jours
	struct sejour *nxtSej;				//pour la liste chainn�e
	struct emplacement place;           //emplacement attribu� au s�jour
}sejour;
#endif
