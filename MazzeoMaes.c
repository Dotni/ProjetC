/* 

*********************************************************************************************
*****************************Projet C : gestion d'un camping*********************************
*********************************************************************************************
Nom : Mazzeo  			Prenom : Florian
Nom : Maes    			Prenom : Martin



nom fichier : MazzeoMaes.c
date : 30/11/2020 */

#include <stdio.h>
#include <string.h>



///////////////////////////////////
/////Définition des structures/////
///////////////////////////////////

//définition du client
typedef struct client {
	char nom[30];				//nom du client
	struct sej *nxt_sej;		//pour la liste chainée des séjours du client
	struct cl *nxt_cl;			//pour la liste chainée des clients
}cl;

//définition d'un séjour
typedef struct sejour{
	short formule;				//1 pour tente , 2 pour caravane, 3 pour bungalow
	short nb_pers;				//nombre de personnes pour qui
	char date[11];				//sous le format dd/mm/yyyy
	float prix;					//prix du séjour
	short elec;					//1 si il faut de l'électricité, 0 si non
}sej;

//définition d'un emplacement
typedef struct emplacement{
	short type;					//1 pour tente , 2 pour caravane, 3 pour bungalow
	short elec;					//1 s'il y a la possibilité d'avoir l'électricité, 0 si non
	float taille;				//taille de l'emplacement 
	float prix;					//prix de l'emplacement
}empla;

//défintion des employés 					A REVOIR PLUS TARD
typedef struct employe{
	char nom[30];				//nom de l'employé
}emple;

main(){
	
	cl i;
	
	strcpy(i.nom,"ok");
	
	printf("%5s",i.nom);
	
	
	
}
