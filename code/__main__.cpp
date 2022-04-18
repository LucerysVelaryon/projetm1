#include <iostream>     // entree/sorties
#include <math.h>
#include <fstream>

#include "classes.h"

using namespace std ;

// déclaration des variables globales

int blanc = 11 ;
int noir = 22 ;

const int nombre_joueurs = 1 ;
string joueurs[nombre_joueurs] = {"humain"} ;
//type classes[nombre_joueurs] = {humain} ;

// éxecution du programme final en C++


int main()
{
	cout << "OTHELLO -- par Elianor et Pierre" << endl << endl ;

	grille grille_de_jeu ;

	/*
	int num_joueur1, num_joueur2 ;
	cout << "Qui sera le joueur 1 (noir) ?" << endl ;			// 2 humains
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

	fstream fich ;
	fich.open("data/MinMax_prof2.dat", ios::out) ;

	int points_noir, points_blanc, gagnant = 0 ;					// gagnant: 0 = égalité ; 1 = blanc a gagné ; 2 = noir a gagné


/*
	ordiAleatoire joueur1 ;											
	ordiMinMax joueur2 ;
	//ordiRetourneMax joueur2 ;
	joueur1.init(noir) ;
	joueur2.init(blanc) ;
	//joueur2.initProfondeur(3) ;

	for (size_t j = 0 ; j < 100 ; j++)
	{
		for (size_t i = 0 ; i < 1000 ; i++)							// Nombre de parties, Noir VS blanc
		{
			points_noir = 0 ; points_blanc = 0 ;						
			grille_de_jeu.init() ;
			int coup_x = 0, coup_y = 0 ;
			while (!grille_de_jeu.jeuFini())
			{
				if ((grille_de_jeu.recupNumeroTour() % 2 == 0) && (grille_de_jeu.recupNbLicites(noir) != 0))
				{
					//grille_de_jeu.affichageJeu() ;
					joueur1.choixCoups(grille_de_jeu, &coup_x, &coup_y) ;
					grille_de_jeu.retournerPlacer(coup_x, coup_y, joueur1.recupCouleur()) ;
				}
				else if ((grille_de_jeu.recupNumeroTour() % 2 != 0) && (grille_de_jeu.recupNbLicites(blanc) != 0))
				{
					//grille_de_jeu.affichageJeu() ;
					joueur2.choixCoups(grille_de_jeu, &coup_x, &coup_y) ;
					grille_de_jeu.retournerPlacer(coup_x, coup_y, joueur2.recupCouleur()) ;
				}
				grille_de_jeu.incrementNumeroTour() ;
			}
			//grille_de_jeu.affichageJeu() ;
			grille_de_jeu.gagnant(&points_blanc, &points_noir, &gagnant) ;
			fich << points_blanc << ' ' << points_noir << ' ' << gagnant << endl ;
		}
	}*/

	ordiAleatoire joueur1 ;											
	ordiMinMax joueur2 ;
	ordiMinMax joueur1_ ;											
	ordiAleatoire joueur2_ ;

	joueur1.init(noir) ;   		// joueur1 est forcément noir
	joueur2.init(blanc) ;
	joueur1_.init(noir) ;
	joueur2_.init(blanc) ;

	joueur2.initProfondeur(2) ;
	joueur1_.initProfondeur(2) ;

	for (size_t j = 0 ; j < 100 ; j++)				// joueur A est 50% blanc et 50% noir (le fichier est: [score joueur A, score joueur B, égalité (0) ou gagnant blanc (1) ou noir (2)])
	{
		for (size_t i = 0 ; i < 500 ; i++)								// joueur A est blanc
		{
			points_noir = 0 ; points_blanc = 0 ;						
			grille_de_jeu.init() ;
			int coup_x = 0, coup_y = 0 ;
			while (!grille_de_jeu.jeuFini())
			{
				if ((grille_de_jeu.recupNumeroTour() % 2 == 0) && (grille_de_jeu.recupNbLicites(noir) != 0))
				{
					//grille_de_jeu.affichageJeu() ;
					joueur1.choixCoups(grille_de_jeu, &coup_x, &coup_y) ;
					grille_de_jeu.retournerPlacer(coup_x, coup_y, joueur1.recupCouleur()) ;
				}
				else if ((grille_de_jeu.recupNumeroTour() % 2 != 0) && (grille_de_jeu.recupNbLicites(blanc) != 0))
				{
					//grille_de_jeu.affichageJeu() ;
					joueur2.choixCoups(grille_de_jeu, &coup_x, &coup_y) ;
					grille_de_jeu.retournerPlacer(coup_x, coup_y, joueur2.recupCouleur()) ;
				}
				grille_de_jeu.incrementNumeroTour() ;
			}
			//grille_de_jeu.affichageJeu() ;
			grille_de_jeu.gagnant(&points_blanc, &points_noir, &gagnant) ;
			fich << points_blanc << ' ' << points_noir << ' ' << gagnant << endl ;
		}

		for (size_t i = 0 ; i < 500 ; i++)								  // joueur A est noir
		{
			points_noir = 0 ; points_blanc = 0 ;						
			grille_de_jeu.init() ;
			int coup_x = 0, coup_y = 0 ;
			while (!grille_de_jeu.jeuFini())
			{
				if ((grille_de_jeu.recupNumeroTour() % 2 == 0) && (grille_de_jeu.recupNbLicites(noir) != 0))
				{
					//grille_de_jeu.affichageJeu() ;
					joueur1_.choixCoups(grille_de_jeu, &coup_x, &coup_y) ;
					grille_de_jeu.retournerPlacer(coup_x, coup_y, joueur1_.recupCouleur()) ;
				}
				else if ((grille_de_jeu.recupNumeroTour() % 2 != 0) && (grille_de_jeu.recupNbLicites(blanc) != 0))
				{
					//grille_de_jeu.affichageJeu() ;
					joueur2_.choixCoups(grille_de_jeu, &coup_x, &coup_y) ;
					grille_de_jeu.retournerPlacer(coup_x, coup_y, joueur2_.recupCouleur()) ;
				}
				grille_de_jeu.incrementNumeroTour() ;
			}
			//grille_de_jeu.affichageJeu() ;
			grille_de_jeu.gagnant(&points_blanc, &points_noir, &gagnant) ;
			fich << points_noir << ' ' << points_blanc << ' ' << gagnant << endl ;
		}
	}
  	fich.close() ;

	return 0 ;
}
