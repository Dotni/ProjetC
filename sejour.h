//d�finition d'un s�jour
typedef struct sejour{
	short formule;						//1 pour tente , 2 pour caravane, 3 pour bungalow
	short nbPersonne;					//nombre de personnes pour qui
	char date[11];						//sous le format dd/mm/yyyy
	float prix;							//prix du s�jour
	short electricite;					//1 si il faut de l'�lectricit�, 0 si non
	struct sejour *nxtSej;
}sejour;
