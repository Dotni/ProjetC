#include <stdio.h>
#include "emplacement.h"
#include "util.h"

void viderEmplacements(emplacement empl[],int tailleEmplacement){
	int i;
	for (i=1;i<tailleEmplacement;i++){
		empl[i].id=0;
	}
}


int lectureEmplacements(emplacement empl[],int tailleEmplacement){
	viderEmplacements(empl,tailleEmplacement);
	FILE *fEmplacement;
	fEmplacement = fopen("data/emplacements.dat","r");
	int i=1;
	while(!feof(fEmplacement)){
		fscanf(fEmplacement,"%2d%1d%1d%5f%6f",&empl[i].id,&empl[i].type,&empl[i].electricite,&empl[i].taille,&empl[i].prix);
		i++;
	}
	fclose(fEmplacement);
	return i-1;
}


void affichageListeEmplacement(emplacement empl[],int tailleEmplacement){
	lectureEmplacements(empl,tailleEmplacement);
	int i=1;
	char x = 253;
	printf("|| Id |   Type   | Elec | taille (m%c) | prix (en euros) ||\n",x);
	printf("||----|----------|------|-------------|-----------------||\n");
	
	while(empl[i].id!=0){
		printf("|| %2d | ",empl[i].id);//%04.2f %05.2f%\n"empl[i].taille,empl[i].prix);
		
		if(empl[i].type==1){
			printf("  tente  | ");
		}
		else{
			if(empl[i].type==2){printf("caravane | ");}
			else{ printf("bungalow | ");}
		}
		
		if(empl[i].electricite==0){ printf(" non | "); }
		else{ printf(" oui | ");  }
		
		printf("   %05.2f    |     %06.2f      ||\n",empl[i].taille,empl[i].prix);
		
		i++; 
	}
	printf("||------------------------------------------------------||\n");
}


void nouvelEmplacement(emplacement empl[],int tailleEmplacement){
	
	//permet de récupérer le nombre d'emplacements et de remplir empl[]
	int nb=lectureEmplacements(empl,tailleEmplacement);
	int i;
	
	//Traitement d'erreur s'il y a trop d'emplacements
	if(nb>=tailleEmplacement-1){
		printf ("%s",Accent("Impossible d'ajouter un emplacement, la liste est déja complète!\n"));
		system("PAUSE");
		system("cls");
		return;
	}
	
	//s'il y a de la place on continue.
	//attention que les id doivent etre triés pour éviter que deux emplacement aient le meme id
	emplacement nouvEmpl;
	nouvEmpl.id=empl[nb-1].id + 1;
	int choix;
	char tmp[7];
	char x = 253;
	float valeur;
	printf("==================================================\n");
	printf("============= Ajout d'un emplacement =============\n");
	printf("==================================================\n");
	//on demande à l'utilisateur ce qu'il doit entrer
	
	
	//type
	printf("Type de l'emplacement ?\n\n");
	printf("1 : tente \n");
	printf("2 : caravane \n");
	printf("3 : bungalow \n\n");
	printf("Votre choix : ");
	
	i=0;
	do{
		if(i!=0){
			printf("Veuillez entrer un nombre correct! Votre choix : ");
		}
		choix = lire(tmp, 2);
		i++;
	}while(choix<1||choix>3);
	nouvEmpl.type=choix;
	
	//elec
	system("cls");
	printf("==================================================\n");
	printf("============= Ajout d'un emplacement =============\n");
	printf("==================================================\n");
	printf ("%s",Accent("L'emplacement possède-t-il un accès à l'électricité ?\n\n"));
	printf("1 : non \n");
	printf("2 : oui \n");
	printf("Votre choix : ");
	
	i=0;
	do{
		if(i!=0){
			printf("Veuillez entrer un nombre correct! Votre choix : ");
		}
		choix = lire(tmp, 2);
		i++;
	}while(choix<1||choix>2);
	nouvEmpl.electricite =choix-1;
	
	//taille
	system("cls");
	printf("==================================================\n");
	printf("============= Ajout d'un emplacement =============\n");
	printf("==================================================\n");
	printf ("%s",Accent("Quelle est la superficie de l'emplacement (en m"));
	printf("%c)?\n\n",x);
	printf("Superficie : ");
	
	i=0;
	do{
		if(i!=0){
			printf("Veuillez entrer un nombre correct! (compris entre 0.01 et 99.99) Votre choix : ");
		}
		valeur = lireFloat(tmp, 6);
		i++;
	}while(valeur>99.99||valeur<=0);
	nouvEmpl.taille=valeur;
	
	//prix
	system("cls");
	printf("==================================================\n");
	printf("============= Ajout d'un emplacement =============\n");
	printf("==================================================\n");
	printf ("%s",Accent("Quel est le prix de l'emplacement(en euros)?\n\n",x));
	printf("prix : ");
	
	i=0;
	do{
		if(i!=0){
			printf("Veuillez entrer un nombre correct! (compris entre 0.01 et 999.99) Votre choix : ");
		}
		valeur = lireFloat(tmp, 7);
		i++;
	}while(valeur>999.99||valeur<=0);
	nouvEmpl.prix=valeur;
	
	system("cls");
	printf("==================================================\n");
	printf("============= Ajout d'un emplacement =============\n");
	printf("==================================================\n\n");
	printf("Confirmez-vous l'ajout de l'emplacement suivant?\n\n");
	
	
	printf("|| Id |   Type   | Elec | taille (m%c) | prix (en euros) ||\n",x);
	printf("||----|----------|------|-------------|-----------------||\n");
	printf("|| %2d | ",nouvEmpl.id);	
	if(nouvEmpl.type==1){
		printf("  tente  | ");
	}
	else{
		if(nouvEmpl.type==2){printf("caravane | ");}
		else{ printf("bungalow | ");}
	}
	
	if(nouvEmpl.electricite==0){ printf(" non | "); }
	else{ printf(" oui | ");  }
	
	printf("   %05.2f    |     %06.2f      ||\n",nouvEmpl.taille,nouvEmpl.prix);
	
	
	
	printf("\n\n1 : non \n");
	printf("2 : oui \n");
	printf("Votre choix :");
	
	i=0;
	do{
		if(i!=0){
			printf("Veuillez entrer un nombre correct! Votre choix :");
		}
		choix = lire(tmp, 2);
		i++;
	}while(choix<1||choix>2);
	
	
	if(choix==2){
		FILE *fEmplacement;
		fEmplacement = fopen("data/emplacements.dat","w");
		for(i=1;i<nb;i++){
			fprintf(fEmplacement,"%2d %1d %1d %5.2f %6.2f\n",empl[i].id,empl[i].type,empl[i].electricite,empl[i].taille,empl[i].prix);
			
		}
		fprintf(fEmplacement,"%2d %1d %1d %5.2f %6.2f",nouvEmpl.id,nouvEmpl.type,nouvEmpl.electricite,nouvEmpl.taille,nouvEmpl.prix);
		
		fclose(fEmplacement);
		system("cls");
		printf ("%s",Accent("Emplacement ajouté avec succès!\n"));
		system("PAUSE");
		system("cls");
	}
	else{
		system("cls");
		printf ("%s",Accent("Emplacement non ajouté!\n"));
		system("PAUSE");
		system("cls");
	}	
}


void supprimerEmplacement(emplacement empl[],int tailleEmplacement){
	int nb=lectureEmplacements(empl,tailleEmplacement);
	int i,choix,choix2;
	char tmp[3];
	char tmp2[2];
	char x = 253;
	
	system("cls");
	printf("========================================================\n");
	printf("============= Suppression d'un emplacement =============\n");
	printf("========================================================\n\n");
	affichageListeEmplacement(empl,tailleEmplacement);
	
	printf ("%s",Accent("Entrez l'id de l'emplacement que vous souhaitez supprimer\n\n"));
	printf("Votre choix : ");
	
	i=0;
	do{
		if(i!=0){
			printf("Veuillez entrer un nombre correct! Votre choix : ");
		}
		choix = lire(tmp, 3);
		i++;
	}while(choix<1||choix>nb);
	
	
	system("cls");
	printf("========================================================\n");
	printf("============= Suppression d'un emplacement =============\n");
	printf("========================================================\n\n");
	printf("Confirmez-vous la suppression de l'emplacement suivant?\n\n");
	
	
	printf("|| Id |   Type   | Elec | taille (m%c) | prix (en euros) ||\n",x);
	printf("||----|----------|------|-------------|-----------------||\n");
	printf("|| %2d | ",empl[choix].id);	
	if(empl[choix].type==1){
		printf("  tente  | ");
	}
	else{
		if(empl[choix].type==2){printf("caravane | ");}
		else{ printf("bungalow | ");}
	}
	
	if(empl[choix].electricite==0){ printf(" non | "); }
	else{ printf(" oui | ");  }
	
	printf("   %05.2f    |     %06.2f      ||\n",empl[choix].taille,empl[choix].prix);
	
	
	
	printf("\n\n1 : non \n");
	printf("2 : oui \n");
	printf("Votre choix :");
	
	i=0;
	do{
		if(i!=0){
			printf("Veuillez entrer un nombre correct! Votre choix :");
		}
		choix2 = lire(tmp2, 2);
		i++;
	}while(choix2<1||choix2>2);
	
	if(choix2==2){
		
		for(i=choix+1;i<=nb;i++){
			empl[i]=empl[i-1];
		}
		nb-1;
		FILE *fEmplacement;
		fEmplacement = fopen("data/emplacements.dat","w");
		for(i=1;i<nb;i++){
			fprintf(fEmplacement,"%2d %1d %1d %5.2f %6.2f\n",empl[i].id,empl[i].type,empl[i].electricite,empl[i].taille,empl[i].prix);
			
		}
		fclose(fEmplacement);
		system("cls");
		printf ("%s",Accent("Emplacement supprimé avec succès!\n"));
		system("PAUSE");
		system("cls");
	}
	else{
		system("cls");
		printf ("%s",Accent("Emplacement non supprimé!\n"));
		system("PAUSE");
		system("cls");
	}	
	
}


void modifierEmplacement(emplacement empl[],int tailleEmplacement){
	int nb=lectureEmplacements(empl,tailleEmplacement);
	int i,choix,choix2;
	char tmp[3];
	char tmp2[2];
	char tmp3[7];
	char x = 253;
	
	system("cls");
	printf("========================================================\n");
	printf("============= Modification d'un emplacement ============\n");
	printf("========================================================\n\n");
	affichageListeEmplacement(empl,tailleEmplacement);
	
	printf ("%s",Accent("Entrez l'id de l'emplacement que vous souhaitez modifier\n\n"));
	printf("Votre choix : ");
	
	i=0;
	do{
		if(i!=0){
			printf("Veuillez entrer un nombre correct! Votre choix : ");
		}
		choix = lire(tmp, 3);
		i++;
	}while(choix<1||choix>nb);
	
	
	system("cls");
	printf("========================================================\n");
	printf("============= Modification d'un emplacement ============\n");
	printf("========================================================\n\n");
	printf("Confirmez-vous la modification de l'emplacement suivant?\n\n");
	
	
	printf("|| Id |   Type   | Elec | taille (m%c) | prix (en euros) ||\n",x);
	printf("||----|----------|------|-------------|-----------------||\n");
	printf("|| %2d | ",empl[choix].id);	
	if(empl[choix].type==1){
		printf("  tente  | ");
	}
	else{
		if(empl[choix].type==2){printf("caravane | ");}
		else{ printf("bungalow | ");}
	}
	
	if(empl[choix].electricite==0){ printf(" non | "); }
	else{ printf(" oui | ");  }
	
	printf("   %05.2f    |     %06.2f      ||\n",empl[choix].taille,empl[choix].prix);
	
	
	int indice=choix;
	printf("\n\n1 : non \n");
	printf("2 : oui \n");
	printf("Votre choix :");
	
	i=0;
	do{
		if(i!=0){
			printf("Veuillez entrer un nombre correct! Votre choix :");
		}
		choix2 = lire(tmp2, 2);
		i++;
	}while(choix2<1||choix2>2);
	
	if(choix2==2){
		system("cls");
		printf("========================================================\n");
		printf("============= Modification d'un emplacement ============\n");
		printf("========================================================\n\n");
		//type
		printf("Type de l'emplacement ?\n\n");
		printf("1 : tente \n");
		printf("2 : caravane \n");
		printf("3 : bungalow \n\n");
		printf("Votre choix : ");
		float valeur;
		emplacement nouvEmpl;
		nouvEmpl.id=empl[indice].id;
		
		
		i=0;
		do{
			if(i!=0){
				printf("Veuillez entrer un nombre correct! Votre choix : ");
			}
			choix = lire(tmp, 2);
			i++;
		}while(choix<1||choix>3);
		nouvEmpl.type=choix;
		
		//elec
		system("cls");
		printf("========================================================\n");
		printf("============= Modification d'un emplacement ============\n");
		printf("========================================================\n\n");
		printf ("%s",Accent("L'emplacement possède-t-il un accès à l'électricité ?\n\n"));
		printf("1 : non \n");
		printf("2 : oui \n");
		printf("Votre choix : ");
		
		i=0;
		do{
			if(i!=0){
				printf("Veuillez entrer un nombre correct! Votre choix : ");
			}
			choix = lire(tmp, 2);
			i++;
		}while(choix<1||choix>2);
		nouvEmpl.electricite =choix-1;
		
		//taille
		system("cls");
		printf("========================================================\n");
		printf("============= Modification d'un emplacement ============\n");
		printf("========================================================\n\n");
		printf ("%s",Accent("Quelle est la superficie de l'emplacement (en m"));
		printf("%c)?\n\n",x);
		printf("Superficie : ");
		
		i=0;
		do{
			if(i!=0){
				printf("Veuillez entrer un nombre correct! (compris entre 0.01 et 99.99) Votre choix : ");
			}
			valeur = lireFloat(tmp3, 6);
			i++;
		}while(valeur>99.99||valeur<=0);
		nouvEmpl.taille=valeur;
		
		//prix
		system("cls");
		printf("========================================================\n");
		printf("============= Modification d'un emplacement ============\n");
		printf("========================================================\n\n");
		printf ("%s",Accent("Quel est le prix de l'emplacement(en euros)?\n\n",x));
		printf("prix : ");
		
		i=0;
		do{
			if(i!=0){
				printf("Veuillez entrer un nombre correct! (compris entre 0.01 et 999.99) Votre choix : ");
			}
			valeur = lireFloat(tmp3, 7);
			i++;
		}while(valeur>999.99||valeur<=0);
		nouvEmpl.prix=valeur;
		
		system("cls");
		printf("========================================================\n");
		printf("============= Modification d'un emplacement ============\n");
		printf("========================================================\n\n");
		printf ("%s",Accent("Voulez-vous remplacer cet emplacement \n\n"));
		
		printf("|| Id |   Type   | Elec | taille (m%c) | prix (en euros) ||\n",x);
		printf("||----|----------|------|-------------|-----------------||\n");
		printf("|| %2d | ",empl[indice].id);	
		if(empl[indice].type==1){
			printf("  tente  | ");
		}
		else{
			if(empl[indice].type==2){printf("caravane | ");}
			else{ printf("bungalow | ");}
		}
		
		if(empl[indice].electricite==0){ printf(" non | "); }
		else{ printf(" oui | ");  }
		
		printf("   %05.2f    |     %06.2f      ||\n\n",empl[indice].taille,empl[indice].prix);
		
		printf ("%s",Accent("par celui-ci ? \n\n"));
		
		printf("|| Id |   Type   | Elec | taille (m%c) | prix (en euros) ||\n",x);
		printf("||----|----------|------|-------------|-----------------||\n");
		printf("|| %2d | ",nouvEmpl.id);	
		if(nouvEmpl.type==1){
			printf("  tente  | ");
		}
		else{
			if(nouvEmpl.type==2){printf("caravane | ");}
			else{ printf("bungalow | ");}
		}
		
		if(nouvEmpl.electricite==0){ printf(" non | "); }
		else{ printf(" oui | ");  }
		
		printf("   %05.2f    |     %06.2f      ||\n\n",nouvEmpl.taille,nouvEmpl.prix);
		
		printf("1 : non \n");
		printf("2 : oui \n");
		printf("Votre choix : ");
		
		i=0;
		do{
			if(i!=0){
				printf("Veuillez entrer un nombre correct! Votre choix : ");
			}
			choix = lire(tmp, 2);
			i++;
		}while(choix<1||choix>2);
		
		if(choix==2){
			empl[indice]=nouvEmpl;
		
			FILE *fEmplacement;
			fEmplacement = fopen("data/emplacements.dat","w");
			for(i=1;i<nb;i++){
				fprintf(fEmplacement,"%2d %1d %1d %5.2f %6.2f\n",empl[i].id,empl[i].type,empl[i].electricite,empl[i].taille,empl[i].prix);
			}
			fclose(fEmplacement);
			system("cls");
			printf ("%s",Accent("Emplacement modifié avec succès!\n"));
			system("PAUSE");
			system("cls");
		}
		else{
			system("cls");
			printf ("%s",Accent("Emplacement non modifié!\n"));
			system("PAUSE");
			system("cls");
		}
	}
	else{
		system("cls");
		printf ("%s",Accent("Emplacement non modifié!\n"));
		system("PAUSE");
		system("cls");
	}	
	
}



void switchMenuEmplacement(int choix,int taille, emplacement empl[]){
	switch(choix){
		case 1 : 
			printf("==========================================================\n");
			printf("=============== Liste des emplacements ===================\n");
			printf("==========================================================\n");
			affichageListeEmplacement(empl,taille);
			system("PAUSE");
			system("cls");
			break;
		case 2 :
			nouvelEmplacement(empl,taille);
			system("cls");
			break;
		case 3:
			supprimerEmplacement(empl,taille);
			break;
		case 4:
			modifierEmplacement(empl,taille);
			break;
	}
}


