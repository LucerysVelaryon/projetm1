#include <iostream>     // entree/sorties
#include <math.h>

using namespace std ;

bool jeuFini(grille ma_grille)
{
	for (size_t i = 0 ; i < 8 ; i++)
		for (size_t j = 0 ; j < 8 ; j++)
			if (liciteB(ma_grille.g[i][j]) || liciteN(ma_grille.g[i][j]) || estVide(ma_grille.g[i][j]))
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

void jouer(grille ma_grille)			// humain vs humain pour l'instant
{
	int couleur = noir ;
	int coup_x = 0, coup_y = 0 ;
	ma_grille.affichageJeu() ;
	while (!jeuFini(ma_grille))
	{
		demanderCoups(couleur, &coup_x, &coup_y) ;
		ma_grille.retournerPlacer(coup_x, coup_y, couleur) ;
		ma_grille.affichageJeu() ;
		couleur = changeCouleur(couleur) ;
	}
}
