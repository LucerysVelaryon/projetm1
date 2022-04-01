#include <iostream>
#include <math.h>

using namespace std;

class ordi1				// choisit un coup aléatoire parmis les coups possibles de sa couleur
{
  public:
    int couleur ;

    void init(int) ;

    void choixCoups(int*, int*) ;
};

void ordi1::init(int coul)
{
  couleur = coul ;
}

void ordi1::choixCoups(int* coup_x, int* coup_y)		// On utlise des pointeurs car le c++ ne peut pas renvoyer de couple...
{
	
}