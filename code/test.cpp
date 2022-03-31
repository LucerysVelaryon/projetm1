#include <iostream>
#include <math.h>

using namespace std;

#include "annexes.cpp"

class grille {
  public:
    int g ;

    void init() ;

    void affichage() const ;
};

void grille::init()
{
  g = 4 ;
}

void grille::affichage() const
{
	cout << endl << g << endl;
}
