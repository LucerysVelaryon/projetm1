#include <iostream>			// entrée/sorties
#include <math.h>

using namespace std ;

// fonctions de modifications des grilles après pose de pions

void retournerPions(int x, int y, int coul)     // fonction qui retourne les pions capturés, pour une couleur donnée
{
    grille[x][y] = coul ;     // on place le pion joué

    int var_x ; int var_y ; int compt ;

    for (size_t pas_x = 0 ; pas_x <= 2 ; pas_x++)
    {
      for (size_t pas_y = 0 ; pas_y <= 2 ; pas_y++)
      {
        var_x = x ; var_y = y ; compt = 0 ;
        while (dedans(var_x, var_y))
        {
          var_x += (pas_x - 1) ;
          var_y += (pas_y - 1) ;
          compt += 1 ;

          if (grille[var_x][var_y] == coul)
          {
              for (size_t i = 1 ; i < compt ; i++)
              {
                grille[x + (pas_x - 1) * i][y + (pas_y - 1) * i] = coul ;
              }
            break ;
          }
          else if (estVide(grille[var_x][var_y]))
          {
            break ;
          }
        }
      }
    }
}
