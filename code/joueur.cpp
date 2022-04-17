#include <iostream>
#include <math.h>
#include <stdlib.h>   // nb Aléatoires
#include <time.h>     // pour avoir un point de départ différent à chaque fois

#include "classes.h"

using namespace std;

extern int blanc ;
extern int noir ;

void humain::init(int coul)
{
  couleur = coul ;
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

/* --------------------------------------------------------------------------------------------------------------------------------- */

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

/* --------------------------------------------------------------------------------------------------------------------------------- */

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

/* --------------------------------------------------------------------------------------------------------------------------------- */

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