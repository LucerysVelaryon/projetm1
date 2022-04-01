#include <iostream>     // entree/sorties
#include <math.h>

using namespace std ;

#include "annexes.cpp"
#include "grille.cpp"

// éxecution du programme final en C++

int main()
{
	grille my_grille ;
	my_grille.init() ;
	my_grille.affichageJeu() ;
	my_grille.retournerPlacer(5,4,22) ;
	my_grille.affichageJeu() ;
	my_grille.affichageBrut() ;

	return 0 ;
}
