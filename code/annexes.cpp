#include <iostream>			// entrée/sorties
#include <math.h>

using namespace std ;

// fonctions simples et utiles partout, permettent une meilleure lisibilité du programme

bool estVide(int i) 			// test case vide
{
	return (i == -1 || i == 0 || i == 1 || i == 2 || i == 3) ;
}

bool estB(int i)			// case occupée par blanc
{
	return (i == 11) ;
}

bool estN(int i)			// case occupée par noir
{
	return (i == 22) ;
}

bool liciteB(int i)			// test case licite blanc
{
	return (i == 0 || i == 1) ;
}

bool liciteN(int i)			// test case licite noir
{
	return (i == 0 || i == 2) ;
}

bool licite(int couleur, int i)
{
	if (couleur == blanc)
		return (i == 0 || i == 1) ;
	else
		return (i == 0 || i == 2) ;
}

bool dedans(int x, int y)			// test case sur plateau
{
	return (x >= 0 && x <= 7 && y >= 0 && y <= 7) ;
}

int changeCouleur(int couleur)
{
	if (couleur == noir)
		return blanc ;
	else
		return noir ;
}

double arrondi(double value)
{
     return floor(value + 0.5);
}
