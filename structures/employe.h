#ifndef EMPLOYE_H
#define EMPLOYE_H

//d�fintion des employ�s 					A REVOIR PLUS TARD
typedef struct employe{
	short id;							//id de l'employ�
	char nom[30];						//nom de l'employ�
	char prenom[30];					//prenom de l'employ�
	float salaireParHeure;				//salaire par heure
	int nbHeures;						//nb d'heures prest�es depuis la derniere paie
	struct employe *nxtEmpl;
}employe;

void switchMenuEmploye(int);
#endif
