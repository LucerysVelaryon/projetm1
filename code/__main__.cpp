#include <iostream>     // entree/sorties
#include <math.h>

using namespace std ;

// déclaration des variables globales

// int grille[8][8] ;		// déclaration grille

#include "grille.cpp"
// #include "test.cpp"
// #include "annexes.cpp"
// #include "grille_lecture.cpp"
// #include "grille_modif.cpp"


// éxecution du programme final en C++

int main()
{
	grille my_grille ;
	my_grille.init() ;
	my_grille.affichageJeu() ;

	return 0 ;
}
