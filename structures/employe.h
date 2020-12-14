#ifndef EMPLOYE_H
#define EMPLOYE_H

//défintion des employés 					A REVOIR PLUS TARD
typedef struct employe{
	short id;							//id de l'employé
	char nom[30];						//nom de l'employé
	char prenom[30];					//prenom de l'employé
	float salaireParHeure;				//salaire par heure
	int nbHeures;						//nb d'heures prestées depuis la derniere paie
	struct employe *nxtEmpl;
}employe;

void switchMenuEmploye(int);
#endif
