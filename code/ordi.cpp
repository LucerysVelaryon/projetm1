#include <iostream>
#include <math.h>
#include <stdlib.h>   // nb Aléatoires
#include <time.h>     // pour avoir un point de départ différent à chaque fois


using namespace std;


class ordiAleatoire	: public humain			// hérite de humain, choisit un coup aléatoire parmis les coups possibles de sa couleur
{
  public:
    void choixCoups(grille, int*, int*) ;
};

void ordiAleatoire::choixCoups(grille ma_grille, int* coup_x, int* coup_y) 	// On utlise des pointeurs car le c++ ne peut pas renvoyer de couple...
{
	int nbCoupsPossibles = 0 ;
	if (couleur == blanc)
		nbCoupsPossibles = ma_grille.nb_licites_b;
	else
		nbCoupsPossibles = ma_grille.nb_licites_n;

  	int alea = rand() % nbCoupsPossibles + 1;		// donne un entier entre 1 et nbCoupsPossibles
	int compt = 1;									// on numérote les coups possibles de 1 à nbCoupsPossibles

//	cout << "couleur ordi: " << couleur << endl;

	for (size_t i = 0 ; i < 8 ; i++)
	{
		for (size_t j = 0 ; j < 8 ; j++)
		{
			if (licite(couleur, ma_grille.g[i][j][0]))
			{
				if (compt == alea)
				{
					*coup_x = i ;
					*coup_y = j ;
				//	cout << endl << "L'ordi a joué en : " << *coup_x << ' ' << *coup_y << endl;
					goto fin_de_la_boucle;
				}
				else
					compt++ ;
			}
		}
	}
	fin_de_la_boucle: ;
}

/* ---------------------------------------------------------------------------------------------------------------------------------------- */

class ordiRetourneMax	: public humain			// hérite de humain, choisit un coup qui retourne un max de pions adverses
{
  public:
    void choixCoups(grille, int*, int*) ;

    void meilleurCoups(grille, int*, int*) ;
} ;

void ordiRetourneMax::choixCoups(grille ma_grille, int* coup_x, int* coup_y)
{
  meilleurCoups(ma_grille, coup_x, coup_y) ;
}

void ordiRetourneMax::meilleurCoups(grille ma_grille, int* coup_x, int* coup_y) 		// On utlise des pointeurs car le c++ ne peut pas renvoyer de couple...
{
	int max = 0, xmax = 0, ymax = 0 ;
	int val = 0 ;

	for (size_t i = 0 ; i < 8 ; i++)
	{
		for (size_t j = 0 ; j < 8 ; j++)
		{
			if (licite(couleur, ma_grille.g[i][j][0]))
			{
				val = ma_grille.g[i][j][couleur/11] ;
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
	//cout << endl << "L'ordi a joué en : " << *coup_x << ' ' << *coup_y << endl;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------- */

class ordiMinMax : public ordiRetourneMax
{
  public:
    void initProfondeur(int) ;

    void choixCoups(grille, int*, int*) ;

  private:
    int profondeur_max ;

    int fonctionMinMax(grille, int, int*, int*) ;
} ;

void ordiMinMax::initProfondeur(int prof)
{
  profondeur_max = prof ;
}

void ordiMinMax::choixCoups(grille ma_grille, int* coup_x, int* coup_y)
{
  int meilleur_coup = fonctionMinMax(ma_grille, profondeur_max, coup_x, coup_y) ;
}

int ordiMinMax::fonctionMinMax(grille ma_grille, int profondeur, int* coup_x, int* coup_y)
{
  grille nouvelle_grille = ma_grille ;
  int coul ;

  if ((profondeur_max - profondeur) % 2 == 0)
    coul = couleur ;
  else
    coul = changeCouleur(couleur) ;

  if (nouvelle_grille.jeuFini() || profondeur == 0 || nouvelle_grille.nb_licites(coul) == 0)
    meilleurCoups(nouvelle_grille, coup_x, coup_y) ;
    return nouvelle_grille.g[*coup_x][*coup_y][coul/11] ;

  int plus_haut_score ;

  if ((nouvelle_grille.numero_tour % 2 == 0))
  {
    plus_haut_score = -2147483648 ;

    for (size_t i = 0 ; i < 8 ; i++)
  	{
  		for (size_t j = 0 ; j < 8 ; j++)
  		{
  			if (licite(coul, nouvelle_grille.g[i][j][0]))
  			{
  				nouvelle_grille.retournerPlacer(i, j, coul) ;
          int score = this->fonctionMinMax(nouvelle_grille, profondeur-1, coup_x, coup_y) ;
          nouvelle_grille = ma_grille ;
          if (score > plus_haut_score)
          {
            plus_haut_score = score ;
            *coup_x = i ;
            *coup_y = j ;
          }
  			}
  		}
  	}
  }

  else
  {
    plus_haut_score = + 2147483647 ;

    for (size_t i = 0 ; i < 8 ; i++)
  	{
  		for (size_t j = 0 ; j < 8 ; j++)
  		{
  			if (licite(coul, nouvelle_grille.g[i][j][0]))
  			{
  				nouvelle_grille.retournerPlacer(i, j, coul) ;
          int score = this->fonctionMinMax(nouvelle_grille, profondeur-1, coup_x, coup_y) ;
          nouvelle_grille = ma_grille ;
          if (score < plus_haut_score)
          {
            plus_haut_score = score ;
            *coup_x = i ;
            *coup_y = j ;
          }
  			}
  		}
    }
  }

  return plus_haut_score ;
}
