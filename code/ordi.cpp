#include <iostream>
#include <math.h>
#include <stdlib.h>   // nb Aléatoires
#include <time.h>     // pour avoir un point de départ différent à chaque fois


using namespace std;


class aleatoire	: public humain			// hérite de humain, choisit un coup aléatoire parmis les coups possibles de sa couleur
{
  public:
    void choixCoups(grille, int*, int*) ;
};

void aleatoire::choixCoups(grille ma_grille, int* coup_x, int* coup_y) //(int* coup_x, int* coup_y)		// On utlise des pointeurs car le c++ ne peut pas renvoyer de couple...
{
	int nbCoupsPossibles = 0 ;
	if (couleur == blanc)
		nbCoupsPossibles = ma_grille.jouable_blanc;
	else
		nbCoupsPossibles = ma_grille.jouable_noir;

	int alea = round(nbCoupsPossibles*drand48()) ;		// donne un entier entre 0 et nbCoupsPossibles
	int compt = 0;

	for (size_t i = 0 ; i < 8 ; i++)
		for (size_t j = 0 ; j < 8 ; j++)
			if (licite(couleur, ma_grille.g[i][j]))
			{
				if (compt == alea)
				{
					*coup_x = i ;
					*coup_y = j ;
					goto fin_de_la_boucle;
				}
				else
					compt++ ;
			}

	fin_de_la_boucle: ;
}
