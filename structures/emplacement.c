#include <stdio.h>

const int tailleEmplacement=30;

typedef struct emplacement{
	short id;							//id de l'emplacement max 32 767	
	short type;							//1 pour tente , 2 pour caravane, 3 pour bungalow 				1d
	short electricite;					//1 s'il y a la possibilité d'avoir l'électricité, 0 si non		1d
	float taille;						//taille de l'emplacement 										2d
	float prix;							//prix de l'emplacement											3d
}emplacement;

void viderEmplacements(emplacement empl[]){
	int i;
	for (i=1;i<tailleEmplacement;i++){
		empl[i].id=0;
	}
}

void lectureEmplacements(emplacement empl[]){
	viderEmplacements(empl);
	FILE *fEmplacement;
	fEmplacement = fopen("data/emplacements.dat","r");
	int i=1;
	while(!feof(fEmplacement)){
		fscanf(fEmplacement,"%2d%1d%1d%2f%3f",&empl[i].id,&empl[i].type,&empl[i].electricite,&empl[i].taille,&empl[i].prix);
		i++;
	}
	fclose(fEmplacement);
}

void affichageListeEmplacement(emplacement empl[]){
	lectureEmplacements(empl);
	int i=1;
	while(empl[i].id!=0){
		printf("Emplacement %2d : id:%2d  type:%2d  electricite:%2d  taille:%04.2f prix:%05.2f%€\n",i,empl[i].id,empl[i].type,empl[i].electricite,empl[i].taille,empl[i].prix);
		i++;
	}
}


