#include <iostream>
#include <math.h>

using namespace std;

class humain {
  public:
    int couleur ;

    void init(int) ;

    void demanderCoups(int*, int*) ;
};

void humain::init(int coul)
{
  couleur = coul ;
}

void humain::demanderCoups(int* coup_x, int* coup_y)		// On utlise des pointeurs car le c++ ne peut pas renvoyer de couple...
{
	if (couleur == blanc)
		cout << "Au tour de blanc (joueur 2) : " << endl ;
	else
		cout << "Au tour de noir (joueur 1) : " << endl ;
	cout <<  "Entrer la position en x (ligne): " ;
	cin >> *coup_x ;
	cout <<  "Entrer la position en y (colonne): " ;
	cin >> *coup_y ;
}