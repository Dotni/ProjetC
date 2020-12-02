#ifndef EMPLACEMENT_H
#define EMPLACEMENT_H
//e
//définition d'un emplacement
typedef struct emplacement{
	short type;							//1 pour tente , 2 pour caravane, 3 pour bungalow 				1d
	short electricite;					//1 s'il y a la possibilité d'avoir l'électricité, 0 si non		1d
	float taille;						//taille de l'emplacement 										2d
	float prix;							//prix de l'emplacement											3d
}emplacement;
#endif
