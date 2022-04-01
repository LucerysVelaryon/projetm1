#include <iostream>     // entree/sorties
#include <math.h>

using namespace std ;

// déclaration des variables globales

int noir = 22 ;
int blanc = 11 ;

// inclusion des classes et fonctions

#include "annexes.cpp"			// fonctions
#include "grille.cpp"				// classe
#include "jouer.cpp"				// fonctions

// éxecution du programme final en C++

int main()
{
	grille grille_de_jeu ;
	grille_de_jeu.init() ;

	jouer(grille_de_jeu) ;

	return 0 ;
}
