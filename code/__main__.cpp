#include <iostream>     // entree/sorties
#include <math.h>


using namespace std ;

#include "annexes.cpp"
#include "grille.cpp"

// déclaration des variables globales

int noir = 22 ;
int blanc = 11 ;

// éxecution du programme final en C++

bool jeuFini()
{
	for (size_t i = 0 ; i < 8 ; i++)
		for (size_t j = 0 ; j < 8 ; j++)
			if (liciteB(grille[i][j]) || liciteN(grille[i][j]) || estVide(grille[i][j]))
				return false ;
	return true ;
}

void demanderCoups(int couleur, int* coup_x, int* coup_y)		// On utlise des pointeurs car le c++ ne peut pas renvoyer de couple...
{
	if (couleur == blanc)
		cout << "Au tour de blanc: " << endl ;
	else
		cout << "Au tour de noir: " << endl ;
	cout <<  "Entrer la position en x (ligne): " ;
	cin >> *coup_x ;
	cout <<  "Entrer la position en y (colonne): " ;
	cin >> *coup_y ;
}

int jouer()			// humain vs humain pour l'instant
{
	int couleur = noir ;
	int coup_x = 0, coup_y = 0 ;
	affichageJeu() ;
	while (!jeuFini())
	{
		demanderCoups(couleur, &coup_x, &coup_y) ;
		retournerPlacer(coup_x, coup_y, couleur) ;
		affichageJeu() ;
		couleur = changeCouleur(couleur) ;
	}
}


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
