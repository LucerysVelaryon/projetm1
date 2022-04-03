#include <iostream>
#include <math.h>
#include <stdlib.h>   // nb Aléatoires
#include <time.h>     // pour avoir un point de départ différent à chaque fois


using namespace std;


class ordi_aleatoire	: public humain			// hérite de humain, choisit un coup aléatoire parmis les coups possibles de sa couleur
{
  public:
    void choixCoups(grille, int*, int*) ;
};

void ordi_aleatoire::choixCoups(grille ma_grille, int* coup_x, int* coup_y) 	// On utlise des pointeurs car le c++ ne peut pas renvoyer de couple...
{
	int nbCoupsPossibles = 0 ;
	if (couleur == blanc)
		nbCoupsPossibles = ma_grille.nb_licites_b;
	else
		nbCoupsPossibles = ma_grille.nb_licites_n;

  	int alea = rand() % nbCoupsPossibles + 1;		// donne un entier entre 1 et nbCoupsPossibles
	int compt = 1;									// on numérote les coups possibles de 1 à nbCoupsPossibles

	cout << "coul " << couleur << " alea: " << nbCoupsPossibles << ' ' << alea << endl;

	for (size_t i = 0 ; i < 8 ; i++)
	{
		for (size_t j = 0 ; j < 8 ; j++)
		{
			if (licite(couleur, ma_grille.g[i][j]))
			{
				if (compt == alea)
				{
					*coup_x = i ;
					*coup_y = j ;
					cout << endl << "L'ordi a joué en : " << *coup_x << ' ' << *coup_y << endl;
					goto fin_de_la_boucle;
				}
				else
					compt++ ;
			}
		}
	}
	fin_de_la_boucle: ;
}


class ordi_retourneMax	: public humain			// hérite de humain, choisit un coup qui retourne un max de pions adverses
{
  public:
    void choixCoups(grille, int*, int*) ;
};


class ordi_retourneMax	: public humain			// hérite de humain, choisit un coup qui retourne un max de pions adverses
{
  public:
    void choixCoups(grille, int*, int*) ;
};

void ordi_retourneMax::choixCoups(grille ma_grille, int* coup_x, int* coup_y) 		// On utlise des pointeurs car le c++ ne peut pas renvoyer de couple...
{	
	int max = 0, xmax = 0, ymax = 0 ;
	int val = 0 ;

	for (size_t i = 0 ; i < 8 ; i++)
	{
		for (size_t j = 0 ; j < 8 ; j++)
		{
			if (licite(couleur, ma_grille.g[i][j][0]))
			{
				val = grilleRetourne[i][j][couleur/11] ;
				cout << "valeur testée" << val << endl ;
				if (val > max)
				{
					max = val ;
					xmax = i ;
					ymax = j ;
				}
			}
		}
	}
	*coup_x = xmax ;
	*coup_y = ymax ;
	cout << endl << "L'ordi a joué en : " << *coup_x << ' ' << *coup_y << endl;
}

