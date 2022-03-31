#include <iostream>			// entrée/sorties
#include <math.h>

using namespace std ;

// fonctions de modifications des grilles après pose de pions

void parcoursGrille(int x, int y, int coul, int methode)
{
  int var_x ; int var_y ; int compt ;
  bool licite_blanc  = false ; bool licite_noir = false ;

  for (size_t pas_x = 0 ; pas_x <= 2 ; pas_x++)
  {
    for (size_t pas_y = 0 ; pas_y <= 2 ; pas_y++)
    {
      var_x = x ; var_y = y ; compt = 0 ;

      while (dedans(var_x, var_y) && (pas_x != 1 || pas_y != 1))
      {
        var_x += (pas_x - 1) ;
        var_y += (pas_y - 1) ;
        compt += 1 ;

        if (methode == 1)     // retourner les pions capturés
        {
          if (grille[var_x][var_y] == coul)
          {
              for (size_t i = 1 ; i < compt ; i++)
              {
                grille[x + (pas_x - 1) * i][y + (pas_y - 1) * i] = coul ;
                parcoursGrille(x + (pas_x - 1) * i, y + (pas_y - 1) * i, coul, 2) ;
              }
            break ;
          }

          else if (estVide(grille[var_x][var_y]))
            break ;
        }

        else if (methode == 2)      // cases vides à pointer
        {
          if (estVide(grille[var_x][var_y]))
          {
            grille[var_x][var_y] = 3 ;
            break ;
          }
        }

        else if (methode == 3)      // cases vides à vérifier
        {
          if (compt == 1)
            coul = grille[var_x][var_y] ;

          if (estVide(grille[var_x][var_y]))
            break ;

          else if (grille[var_x][var_y] != coul)
          {
            if (coul == 11)
              licite_noir = true ;
            else
              licite_blanc = true ;
            break ;
          }
        }
      }
    }
  }

  if (methode == 3)
  {
    if (licite_blanc && licite_noir)
      grille[x][y] = 0 ;
    else if (licite_blanc)
      grille[x][y] = 1 ;
    else if (licite_noir)
      grille[x][y] = 2 ;
    else
      grille[x][y] = -1 ;
  }
}

void retournerPions(int x, int y, int coul)     // fonction qui retourne les pions capturés, pour une couleur donnée
{
  int var_x ; int var_y ; int compt ;

  grille[x][y] = coul ;     // on place le pion joué

  parcoursGrille(x, y, coul, 1) ;

  parcoursGrille(x, y, coul, 2) ;

  for (size_t i = 0 ; i <= 7 ; i++)
  {
    for (size_t j = 0 ; j <= 7 ; j++)
    {
      if (grille[i][j] == 3)
        parcoursGrille(i, j, coul, 3) ;
    }
  }
}
