#include <iostream>     // entree/sorties
#include <math.h>

using namespace std ;

// déclaration des variables globales

int noir = 22 ;
int blanc = 11 ;

// inclusion des classes et fonctions

#include "annexes.cpp"			// fonctions					// On a un pb de double inclusion de fichier car grille et annexes sont dans ordi
#include "grille.cpp"				// classe
#include "humain.cpp"				// classe
#include "ordi.cpp"					// classe

const int nombre_joueurs = 1 ;
string joueurs[nombre_joueurs] = {"humain"} ;
//type classes[nombre_joueurs] = {humain} ;

// éxecution du programme final en C++

int main()
{
	srand48(time(NULL)); 		//Inititialise la graine, pour l'aléatoire de l'ordi

	int num_joueur1, num_joueur2 ;
	grille grille_de_jeu ;
	grille_de_jeu.init() ;

	cout << "OTHELLO -- par Elianor et Pierre" << endl << endl ;

	/*cout << "Qui sera le joueur 1 (noir) ?" << endl ;			// 2 humains
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
	joueur2.init(blanc) ;*/

	humain joueur1 ;											// 1 humain (noir) ; 1 ordi (blanc)
	aleatoire joueur2 ;
	joueur1.init(noir) ;
	joueur2.init(blanc) ;

	int coup_x = 0, coup_y = 0 ;
	while (!grille_de_jeu.jeuFini())
	{
		if ((grille_de_jeu.numero_tour % 2 == 0) && (grille_de_jeu.nb_licites_n != 0))
		{
			grille_de_jeu.affichageJeu() ;
			joueur1.choixCoups(grille_de_jeu, &coup_x, &coup_y) ;
			grille_de_jeu.retournerPlacer(coup_x, coup_y, joueur1.couleur) ;
		}
		else if ((grille_de_jeu.numero_tour % 2 != 0) && (grille_de_jeu.nb_licites_b != 0))
		{
			grille_de_jeu.affichageJeu() ;
			joueur2.choixCoups(grille_de_jeu, &coup_x, &coup_y) ;
			grille_de_jeu.retournerPlacer(coup_x, coup_y, joueur2.couleur) ;
		}
		grille_de_jeu.numero_tour++ ;
	}
	grille_de_jeu.affichageJeu() ;

	return 0 ;
}
