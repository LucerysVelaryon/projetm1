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
  cout << "humain (1), ordiAleatoire (2), ordiRetourneMax (3), ordiMinMax (4)" << endl ;
  cin >> joueur ;
  if (joueur == 4)
  {
    int profondeur ;
    cout << 
  }
}

int choixModeJeu()
{

}

grille unePartie(humain joueur1, humain joueur2)
{
  grille grille_de_jeu() ;
  grille_de_jeu.init() ;
  int coup_x = 0, coup_y = 0 ;

  while (!grille_de_jeu.jeuFini())
    {
      if ((grille_de_jeu.recupNumeroTour() % 2 == 0) && (grille_de_jeu.recupNbLicites(noir) != 0))
      {
        joueur1.choixCoups(grille_de_jeu, &coup_x, &coup_y) ;
        grille_de_jeu.retournerPlacer(coup_x, coup_y, joueur1.recupCouleur()) ;
      }
      else if ((grille_de_jeu.recupNumeroTour() % 2 != 0) && (grille_de_jeu.recupNbLicites(blanc) != 0))
      {
        joueur2.choixCoups(grille_de_jeu, &coup_x, &coup_y) ;
        grille_de_jeu.retournerPlacer(coup_x, coup_y, joueur2.recupCouleur()) ;
      }
      grille_de_jeu.incrementNumeroTour() ;
    }

  return grille_de_jeu ;
}

void modeHumain()
{
  cout << "Qui sera le joueur 1 (noir) ?" << endl ;     // 2 humains
  for (size_t i = 0 ; i < nombre_joueurs ; i++)
    cout << joueurs[i] << " : " << i << endl ;
  cin >> num_joueur1 ;
  humain joueur1 ;
  joueur1.init(noir) ;

  cout << "Qui sera le joueur 2 (blanc) ?" << endl ;
  for (size_t i = 0 ; i < nombre_joueurs ; i++)
    cout << joueurs[i] << " : " << i << endl ;
  cin >> num_joueur2 ;
  humain joueur2 ;
  joueur2.init(blanc) ;

  grille grille_de_jeu = unePartie(joueur1, joueur2) ;
} 

void modeStats(int nombre_parties)
{
  fstream fich ;
  fich.open("resultats.dat", ios::out) ;

  int points_noir, points_blanc, gagnant = 0 ;          // gagnant: 0 = égalité ; 1 = blanc a gagné ; 2 = noir a gagné

  for (size_t i = 0 ; i < unsigned(nombre_parties) ; i++)                // Nombre de parties
  {
    points_noir = 0 ; 
    points_blanc = 0 ;
    grille grille_de_jeu = unePartie(joueur1, joueur2) ;    
    grille_de_jeu.gagnant(&points_blanc, &points_noir, &gagnant) ;
    fich << points_blanc << ' ' << points_noir << ' ' << gagnant << endl ;
  }

  fich.close() ;
}