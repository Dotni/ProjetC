//d�finition d'un emplacement
typedef struct emplacement{
	short type;							//1 pour tente , 2 pour caravane, 3 pour bungalow
	short electricite;							//1 s'il y a la possibilit� d'avoir l'�lectricit�, 0 si non
	float taille;						//taille de l'emplacement 
	float prix;							//prix de l'emplacement
}emplacement;
