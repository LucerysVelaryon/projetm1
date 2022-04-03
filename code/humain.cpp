#include <iostream>
#include <math.h>

using namespace std;

class humain {
  public:
    int couleur ;

    void init(int) ;

    void choixCoups(grille, int*, int*) ;
};

void humain::init(int coul)
{
  couleur = coul ;
}

void humain::choixCoups(grille ma_grille, int* coup_x, int* coup_y)		// On utlise des pointeurs car le c++ ne peut pas renvoyer de couple...
{																		// On rajoute un argument qui sert à rien pour avoir la même structure que ordi::choixCoups
	if (couleur == blanc)
		cout << "Au tour de blanc (joueur 2) : " << endl ;
	else
		cout << "Au tour de noir (joueur 1) : " << endl ;
	cout <<  "Entrer la position en x (ligne): " ;
	cin >> *coup_x ;
	cout <<  "Entrer la position en y (colonne): " ;
	cin >> *coup_y ;

	if (!dedans(*coup_x, *coup_y) || !licite(couleur, ma_grille.g[*coup_x][*coup_y][0]))
	{
		cout << endl << "Coup non licite, veuillez rentrer à nouveau des coordonnées : \n" << endl ;
		choixCoups(ma_grille, coup_x, coup_y) ;
	}

}