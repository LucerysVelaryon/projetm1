#include <iostream>     // entree/sorties
#include <math.h>

#include "annexes.cpp"
#include "grille_lecture.cpp"
#include "grille_modif.cpp"

using namespace std ;

// declaration des variables globales

int grille[8][8] ;		// declaration grille

// execution du programme final en C++

int main()
{
	grille_init() ;
	affichageBrut() ;

	return 0 ;
}
