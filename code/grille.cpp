#include <iostream>
#include <math.h>

using namespace std;

class grille {
  public:
    int g[8][8] ;
    int numero_tour ;

    void init() ;

    void affichageJeu() const ;
    void affichageBrut() const ;

    void retournerPlacer(int x, int y, int coul) ;

  private:
    void rayonnement(int x, int y, int coul, int methode) ;
};

void grille::init()
{
  for (int i = 0 ; i < 8 ; i++)
		for (int j = 0 ; j < 8 ; j++)
			g[i][j] = -1 ;			// cases vides

	g[3][3] = 11 ; g[4][4] = 11 ;			// pions init blancs
	g[3][4] = 22 ; g[4][3] = 22 ;			// pions init noirs
	g[2][4] = 1 ; g[3][5] = 1 ; g[5][3] = 1 ; g[4][2] = 1 ;			// cases licites blancs
	g[2][3] = 2 ; g[3][2] = 2 ; g[5][4] = 2 ; g[4][5] = 2 ;			// cases licites noirs
}

void grille::affichageJeu() const
{
	cout << endl << "    0   1   2   3   4   5   6   7  " ;
	cout << endl << "  ---------------------------------" << endl ;
	for (int i = 0 ; i < 8 ; i++)
	{
		cout << i << " | " ;
		for (int j = 0 ; j < 8 ; j++)
		{
			if (estVide(g[i][j]))
				cout << ' ' << " | " ;
			else if (estB(g[i][j]))
				cout << 'B' << " | " ;
			else if (estN(g[i][j]))
				cout << 'N' << " | " ;
    }
		cout << endl << "  ---------------------------------" << endl ;
	}
}

void grille::affichageBrut() const			// affichage valeurs réelles matrice
{
	cout <<  endl << "     0    1    2    3    4    5    6    7  " ;
	cout << endl << "  -----------------------------------------" << endl ;
	for (int i = 0 ; i < 8 ; i++)
	{
		cout << i << " | " ;
		for (int j = 0 ; j < 8 ; j++)
		{
			if (g[i][j] == 1)
				cout << "01" << " | " ;
			else if (g[i][j] == 2)
				cout << "02" << " | " ;
			else if (g[i][j] == 3)
				cout << "33" << " | " ;
			else
				cout << g[i][j] << " | " ;
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

      while (dedans(var_x, var_y) && (pas_x != 1 || pas_y != 1))
      {
        var_x += (pas_x - 1) ;
        var_y += (pas_y - 1) ;
        compt += 1 ;

        if (methode == 1)     // retourner les pions capturés
        {
          if (g[var_x][var_y] == coul)
          {
              for (size_t i = 1 ; i < compt ; i++)
              {
                g[x + (pas_x - 1) * i][y + (pas_y - 1) * i] = coul ;
                this->rayonnement(x + (pas_x - 1) * i, y + (pas_y - 1) * i, coul, 2) ;
              }
            break ;
          }

          else if (estVide(g[var_x][var_y]))
            break ;
        }

        else if (methode == 2)      // cases vides à pointer
        {
          if (estVide(g[var_x][var_y]))
          {
            g[var_x][var_y] = 3 ;
            break ;
          }
        }

        else if (methode == 3)      // cases vides à vérifier
        {
          if (compt == 1)
            coul = g[var_x][var_y] ;

          if (estVide(g[var_x][var_y]))
            break ;

          else if (g[var_x][var_y] != coul)
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
      g[x][y] = 0 ;
    else if (licite_blanc)
      g[x][y] = 1 ;
    else if (licite_noir)
      g[x][y] = 2 ;
    else
      g[x][y] = -1 ;
  }
}

void grille::retournerPlacer(int x, int y, int coul)     // fonction qui retourne les pions capturés, pour une couleur donnée
{
  g[x][y] = coul ;     // on place le pion joué

  this->rayonnement(x, y, coul, 1) ;

  this->rayonnement(x, y, coul, 2) ;

  for (size_t i = 0 ; i <= 7 ; i++)
  {
    for (size_t j = 0 ; j <= 7 ; j++)
    {
      if (g[i][j] == 3)
        this->rayonnement(i, j, coul, 3) ;
    }
  }
}