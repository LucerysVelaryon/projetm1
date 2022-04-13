#include <iostream>
#include <math.h>
#include <stdlib.h>   // nb Aléatoires
#include <time.h>     // pour avoir un point de départ différent à chaque fois

#include "classes.h"

using namespace std ;

extern int blanc ; 
extern int noir ;

void grille::init()
{
  for (size_t i = 0 ; i < 8 ; i++)
		for (size_t j = 0 ; j < 8 ; j++)
    {
      g[i][j][0] = -1 ;			// cases vides
      g[i][j][1] = 0 ;
      g[i][j][2] = 0 ;
    }

	g[3][3][0] = 11 ; g[4][4][0] = 11 ;			// pions init blancs
	g[3][4][0] = 22 ; g[4][3][0] = 22 ;			// pions init noirs
	g[2][4][0] = 1 ; g[3][5][0] = 1 ; g[5][3][0] = 1 ; g[4][2][0] = 1 ;			// cases licites blancs
	g[2][3][0] = 2 ; g[3][2][0] = 2 ; g[5][4][0] = 2 ; g[4][5][0] = 2 ;			// cases licites noirs

  g[4][2][1] = 1 ; g[3][5][1] = 1 ; g[2][4][1] = 1 ; g[5][3][1] = 1 ;
  g[5][4][2] = 1 ; g[4][5][2] = 1 ; g[3][2][2] = 1 ; g[2][3][2] = 1 ;

  numero_tour = 0 ;
  nb_licites_b = 4 ;
  nb_licites_n = 4 ;
}

void grille::affichageJeu() const
{
	cout << endl << "    0   1   2   3   4   5   6   7  " ;
	cout << endl << "  ---------------------------------" << endl ;
	for (size_t i = 0 ; i < 8 ; i++)
	{
		cout << i << " | " ;
		for (size_t j = 0 ; j < 8 ; j++)
		{
      if (estVide(g[i][j][0]))
      {
        if (numero_tour % 2 == 0)
        {
          if (licite(noir, g[i][j][0]))
            cout << 'O' << " | " ;
          else
            cout << ' ' << " | " ;
        }
        else if (numero_tour % 2 != 0)
        {
          if (licite(blanc, g[i][j][0]))
            cout << 'O' << " | " ;
          else
            cout << ' ' << " | " ;
        }
      }
			else if (estB(g[i][j][0]))
				cout << 'B' << " | " ;
			else if (estN(g[i][j][0]))
				cout << 'N' << " | " ;
    }
		cout << endl << "  ---------------------------------" << endl ;
	}
}

void grille::affichageBrut() const			// affichage valeurs réelles matrice
{
	cout <<  endl << "     0    1    2    3    4    5    6    7  " ;
	cout << endl << "  -----------------------------------------" << endl ;
	for (size_t i = 0 ; i < 8 ; i++)
	{
		cout << i << " | " ;
		for (size_t j = 0 ; j < 8 ; j++)
		{
			if (g[i][j][0] == 1)
				cout << "01" << " | " ;
			else if (g[i][j][0] == 2)
				cout << "02" << " | " ;
			else if (g[i][j][0] == 3)
				cout << "33" << " | " ;
			else
				cout << g[i][j][0] << " | " ;
		}
		cout << endl << "  -----------------------------------------" << endl ;
	}
}

void grille::rayonnement(int x, int y, int coul, int methode)
{
  int var_x ; int var_y ; int compt ;
  bool licite_blanc  = false ; bool licite_noir = false ;

  for (size_t pas_x = 0 ; pas_x <= 2 ; pas_x++)
  {
    for (size_t pas_y = 0 ; pas_y <= 2 ; pas_y++)
    {
      var_x = x ; var_y = y ; compt = 0 ;

      if (pas_x != 1 || pas_y != 1)
      {
        var_x += (pas_x - 1) ;
        var_y += (pas_y - 1) ;

        while (dedans(var_x, var_y))
        {
          compt++ ;

          if (methode == 1)     // retourner les pions capturés
          {
            if (g[var_x][var_y][0] == coul)
            {
                for (size_t i = 1 ; i < compt ; i++)
                {
                  if (dedans(x + (pas_x - 1) * i, y + (pas_y - 1) * i))
                  {
                    g[x + (pas_x - 1) * i][y + (pas_y - 1) * i][0] = coul ;
                    this->rayonnement(x + (pas_x - 1) * i, y + (pas_y - 1) * i, coul, 2) ;
                  }
                }
              break ;
            }

            else if (estVide(g[var_x][var_y][0]))
              break ;
          }

          else if (methode == 2)      // cases vides à pointer
          {
            if (estVide(g[var_x][var_y][0]))
            {
              this->majNbCoupsLicite(var_x, var_y, -1) ;
              g[var_x][var_y][0] = 3 ;
              g[var_x][var_y][1] = 0 ;
              g[var_x][var_y][2] = 0 ;
              break ;
            }
          }

          else if (methode == 3)      // cases vides à vérifier
          {
            if (compt == 1)
              coul = g[var_x][var_y][0] ;

            if (estVide(g[var_x][var_y][0]))
              break ;

            else if (g[var_x][var_y][0] != coul)
            {
              if (coul == blanc)
              {
                licite_noir = true ;
                g[x][y][2] += compt - 1 ;
              }
              else
              {
                licite_blanc = true ;
                g[x][y][1] += compt - 1;
              }
              break ;
            }
          }

            var_x += (pas_x - 1) ;
            var_y += (pas_y - 1) ;
        }
      }
    }
  }

  if (methode == 3)
  {
    if (licite_blanc && licite_noir)
      g[x][y][0] = 0 ;
    else if (licite_blanc)
      g[x][y][0] = 1 ;
    else if (licite_noir)
      g[x][y][0] = 2 ;
    else
      g[x][y][0] = -1 ;
    this->majNbCoupsLicite(x, y, 1) ;
  }
}

void grille::retournerPlacer(int x, int y, int coul)     // fonction qui retourne les pions capturés et update la licité des cases vides concernées, pour une couleur donnée
{
  this->majNbCoupsLicite(x, y, -1) ;
  g[x][y][0] = coul ;                      // on place le pion joué

  this->rayonnement(x, y, coul, 1) ;    // On retourne les pions capturés et on marque les cases vides concernées comme "à vérifier" (=3)
  this->rayonnement(x, y, coul, 2) ;    // (cas particulier pour optimisé tps: marque les cases vides autour du pion placé)

  for (size_t i = 0 ; i <= 7 ; i++)
  {
    for (size_t j = 0 ; j <= 7 ; j++)
    {
      if (g[i][j][0] == 3)
        this->rayonnement(i, j, coul, 3) ;    // On update la licité des cases 3
    }
  }
}

bool grille::jeuFini()
{
	return (nb_licites_n == 0 && nb_licites_b == 0) ;
}

void grille::majNbCoupsLicite(int x, int y, int pas)
{
  if (g[x][y][0] == 0)
  {
    nb_licites_n += pas ;
    nb_licites_b += pas ;
  }
  else if (g[x][y][0] == 1)
    nb_licites_b += pas ;
  else if (g[x][y][0] == 2)
    nb_licites_n += pas ;
}

void grille::gagnant(int* nb_blancs, int* nb_noirs, int* gagnant)
{
  for (size_t i = 0 ; i <= 7 ; i++)
  {
    for (size_t j = 0 ; j <= 7 ; j++)
    {
      if (g[i][j][0] == blanc)
        *nb_blancs += 1 ;
      else if (g[i][j][0] == noir)
        *nb_noirs += 1 ;
    }
  }

  if (*nb_noirs > *nb_blancs)
  {
    //cout << "Joueur Noir a gagné ! " << *nb_noirs << " contre "  << *nb_blancs << " pour Joueur Blanc" << endl ;
    *gagnant = 2 ;
  }
  else if (*nb_noirs < *nb_blancs)
  {
    //cout << "Joueur Blanc a gagné ! " << *nb_blancs << " contre "  << *nb_noirs << " pour Joueur Noir" << endl ;
    *gagnant = 1 ;
  }
  else
  {
    //cout << "Egalité ! " << *nb_blancs << " partout !" << endl ;
    *gagnant = 0 ;
  }
}

int grille::nb_licites(int coul)
{
  if (coul == blanc)
    return nb_licites_b ;
  else
    return nb_licites_n ;
}


void humain::init(int coul)
{
  couleur = coul ;
}

void ordiAleatoire::init(int coul)
{
  couleur = coul ;
  srand(time(NULL));    //Inititialise la graine, pour l'aléatoire de l'ordi
}

void ordiAleatoire::choixCoups(grille ma_grille, int* coup_x, int* coup_y)  // On utlise des pointeurs car le c++ ne peut pas renvoyer de couple...
{
  int nbCoupsPossibles = 0 ;
  if (couleur == blanc)
    nbCoupsPossibles = ma_grille.nb_licites_b;
  else
    nbCoupsPossibles = ma_grille.nb_licites_n;

    int alea = rand() % nbCoupsPossibles + 1;   // donne un entier entre 1 et nbCoupsPossibles
  int compt = 1;                  // on numérote les coups possibles de 1 à nbCoupsPossibles

  //  cout << "couleur ordi: " << couleur << endl;

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
        //  cout << endl << "L'ordi a joué en : " << *coup_x << ' ' << *coup_y << endl;
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



void ordiRetourneMax::choixCoups(grille ma_grille, int* coup_x, int* coup_y)
{
  int score = meilleurCoups(ma_grille, coup_x, coup_y, false) ;
}

int ordiRetourneMax::meilleurCoups(grille ma_grille, int* coup_x, int* coup_y, bool couleur_joueur)     // On utlise des pointeurs car le c++ ne peut pas renvoyer de couple...
{
  int max = 0, xmax = 0, ymax = 0 ;
  int val = 0 ;

  int coul = couleur ;
  if (couleur_joueur)
    coul = changeCouleur(coul) ;

  for (size_t i = 0 ; i < 8 ; i++)
  {
    for (size_t j = 0 ; j < 8 ; j++)
    {
      if (licite(coul, ma_grille.g[i][j][0]))
      {
        val = ma_grille.g[i][j][coul/11] ;
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
  return max ;
  //cout << endl << "L'ordi a joué en : " << *coup_x << ' ' << *coup_y << endl;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------- */


void ordiMinMax::initProfondeur(int prof)
{
  profondeur_max = prof ;
}

void ordiMinMax::choixCoups(grille ma_grille, int* coup_x, int* coup_y)
{
  int* point_x ; int* point_y ;
  int score = fonctionMinMax(ma_grille, profondeur_max, coup_x, coup_y) ;
}

int ordiMinMax::fonctionMinMax(grille ma_grille, int profondeur, int* coup_x, int* coup_y)
{
  grille nouvelle_grille = ma_grille ;
  int var_x ; int var_y ;
  int coul ;

  if ((profondeur_max - profondeur) % 2 == 0)
    coul = couleur ;
  else
    coul = changeCouleur(couleur) ;

  if (nouvelle_grille.jeuFini() || profondeur == 0 || nouvelle_grille.nb_licites(coul) == 0)
  {
    return this->meilleurCoups(nouvelle_grille, coup_x, coup_y, (coul != couleur)) ;
  }

  int plus_haut_score ;

  if ((profondeur_max - profondeur) % 2 == 0)
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
            var_x = i ;
            var_y = j ;
          }
        }
      }
    }

    if (profondeur == profondeur_max)
    {
      *coup_x = var_x ;
      *coup_y = var_y ;
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
            var_x = i ;
            var_y = j ;
          }
        }
      }
    }
  }

  return plus_haut_score ;
}

void humain::choixCoups(grille ma_grille, int* coup_x, int* coup_y)   // On utlise des pointeurs car le c++ ne peut pas renvoyer de couple...
{                                   // On rajoute un argument qui sert à rien pour avoir la même structure que ordi::choixCoups
  if (couleur == blanc)
    cout << "Au tour de blanc (joueur 2) : " << endl ;
  else
    cout << "Au tour de noir (joueur 1) : " << endl ;
  cout <<  "Entrer la position en x (ligne): " ;
  cin >> *coup_x ;
  cout <<  "Entrer la position en y (colonne): " ;
  cin >> *coup_y ;

  if (!dedans(*coup_x, *coup_y) || !licite(couleur, ma_grille.g[*coup_x][*coup_y][0]))
  {
    cout << endl << "Coup non licite, veuillez rentrer à nouveau des coordonnées : \n" << endl ;
    choixCoups(ma_grille, coup_x, coup_y) ;
  }

}
