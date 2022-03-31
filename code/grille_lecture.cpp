#include <iostream>			// entrée/sorties
#include <math.h>

using namespace std ;

// fonctions de déclaration et de lecture de la grille de jeu en C++

void grille_init()
{
	for (int i = 0 ; i < 8 ; i++)
		for (int j = 0 ; j < 8 ; j++)
			grille[i][j] = -1 ;			// cases vides

	grille[3][3] = 11 ; grille[4][4] = 11 ;			// pions init blancs
	grille[3][4] = 22 ; grille[4][3] = 22 ;			// pions init noirs
	grille[2][4] = 1 ; grille[3][5] = 1 ; grille[5][3] = 1 ; grille[4][2] = 1 ;			// cases licites blancs
	grille[2][3] = 2 ; grille[3][2] = 2 ; grille[5][4] = 2 ; grille[4][5] = 2 ;			// cases licites noirs
}

void affichageBrut()			// affichage valeurs réelles matrice
{
	cout <<  endl << "     0    1    2    3    4    5    6    7  " ;
	cout << endl << "  -----------------------------------------" << endl ;
	for (int i = 0 ; i < 8 ; i++)
	{
		cout << i << " | " ;
		for (int j = 0 ; j < 8 ; j++)
		{
			if (grille[i][j] == 1)
				cout << "01" << " | " ;
			else if (grille[i][j] == 2)
				cout << "02" << " | " ;
			else
				cout << grille[i][j] << " | " ;
		}
		cout << endl << "  -----------------------------------------" << endl ;
	}
}

void affichageJeu()			// affichage grille avec cases vides, blanches ou noires
{
	cout << endl << "    0   1   2   3   4   5   6   7  " ;
	cout << endl << "  ---------------------------------" << endl ;
	for (int i = 0 ; i < 8 ; i++)
	{
		cout << i << " | " ;
		for (int j = 0 ; j < 8 ; j++)
		{
			if (estVide(grille[i][j]))
				cout << ' ' << " | " ;
			else if (estB(grille[i][j]))
				cout << 'B' << " | " ;
			else if (estN(grille[i][j]))
				cout << 'N' << " | " ;
		}
		cout << endl << "  ---------------------------------" << endl ;
	}
}
