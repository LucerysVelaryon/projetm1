#include <iostream>     // entree/sorties
#include <math.h>

using namespace std ;

// déclaration des variables globales

int grille[8][8] ;		// déclaration grille

#include "annexes.cpp"
#include "grille_lecture.cpp"
#include "grille_modif.cpp"

// éxecution du programme final en C++

int main()
{
	grille_init() ;
	affichageJeu() ;
	retournerPions(5,4,22) ;
	affichageJeu() ;

	return 0 ;
}
