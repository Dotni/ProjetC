#include "emplacement.h"

const int tailleEmplacement=30;
static emplacement empl[30];

void lectureEmplacements(){
	viderEmplacements();
	FILE *fEmplacement;
	fEmplacement = fopen("data/emplacements.dat","r");
	int i=1;
	while(!feof(fEmplacement)){
		fscanf(fEmplacement,"%2d%1d%1d%2f%3f",&empl[i].id,&empl[i].type,&empl[i].electricite,&empl[i].taille,&empl[i].prix);
		i++;
	}
	fclose(fEmplacement);
}

void affichageListeEmplacement(){
	lectureEmplacements();
	int i=1;
	while(empl[i].id!=0){
		printf("Emplacement %2d : id:%2d  type:%2d  electricite:%2d  taille:%04.2f prix:%05.2f%€\n",i,empl[i].id,empl[i].type,empl[i].electricite,empl[i].taille,empl[i].prix);
		i++;
	}
}

void viderEmplacements(){
	int i;
	for (i=1;i<tailleEmplacement;i++){
		empl[i].id=0;
	}
}
