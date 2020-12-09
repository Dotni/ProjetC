#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "employe.h"
#include "util.h"

employe *premierEmpl, *courantEmpl, *suivantEmpl, *intercaleEmpl;

void viderEmploye(){
	while(courantEmpl->nxtEmpl != NULL) {
		courantEmpl = courantEmpl->nxtEmpl;
	}
}





void afficherListeEmploye(){
	
}



void switchMenuEmploye(int choix){
	switch(choix){
		case 1 : 
			afficherListeEmploye();
			break;
		case 2 :
			
			break;
		case 3:
		
			break;
		case 4:
		
			break;
		case 5:
		
			break;
		case 6:
		
			break;
	}
}
