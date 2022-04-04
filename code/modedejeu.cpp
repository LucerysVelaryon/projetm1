#include <iostream>
#include <math.h>

using namespace std;

class modeDeJeu
{
  int modeDeJeu ;
  public:
    int choixModeJeu() ;

  private:
    int choixParticipants(int) ;
} ;

int choixParticipants(int num_joueur)
{
  int joueur ;
  cout << "Qui sera le joueur" ;
  if (num_joueur == 1)
    cout << " noir ? (premier " ;
  else if (num_joueur == 2)
    cout << " blanc ? (deuxième " ;
  cout << "à jouer)" << endl ;
  cout << "humain (1), ordiAleatoire (2), ordiRetourneMax (3)" << endl ;
  cin >> joueur ;
}

int choixModeJeu()
{

}
