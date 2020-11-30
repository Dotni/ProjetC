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
/////D�finition des structures/////
///////////////////////////////////

//d�finition du client
typedef struct client {
	char nom[30];				//nom du client
	struct sej *nxt_sej;		//pour la liste chain�e des s�jours du client
	struct cl *nxt_cl;			//pour la liste chain�e des clients
}cl;

//d�finition d'un s�jour
typedef struct sejour{
	short formule;				//1 pour tente , 2 pour caravane, 3 pour bungalow
	short nb_pers;				//nombre de personnes pour qui
	char date[11];				//sous le format dd/mm/yyyy
	float prix;					//prix du s�jour
	short elec;					//1 si il faut de l'�lectricit�, 0 si non
}sej;

//d�finition d'un emplacement
typedef struct emplacement{
	short type;					//1 pour tente , 2 pour caravane, 3 pour bungalow
	short elec;					//1 s'il y a la possibilit� d'avoir l'�lectricit�, 0 si non
	float taille;				//taille de l'emplacement 
	float prix;					//prix de l'emplacement
}empla;

//d�fintion des employ�s 					A REVOIR PLUS TARD
typedef struct employe{
	char nom[30];				//nom de l'employ�
}emple;

main(){
	
	cl i;
	
	strcpy(i.nom,"ok");
	
	printf("%5s",i.nom);
	
	
	
}
