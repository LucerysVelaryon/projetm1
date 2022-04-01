#include <iostream>
#include <math.h>

using namespace std;

class joueur {
  public:
    int couleur ;

    void init() ;

    void demanderCoups(int, int*, int*) ;
};

void joueur::init()
{
  int var_coul ;
  cout << "Quelle couleur (B=1, N=2) ?" << endl ;
  cin >> var_coul ;
  if (var_coul == 1)
    couleur = blanc ;
  else if (var_coul == 2)
    couleur = noir ;
  else
    this->init() ;
}

void joueur::demanderCoups(int couleur, int* coup_x, int* coup_y)		// On utlise des pointeurs car le c++ ne peut pas renvoyer de couple...
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
