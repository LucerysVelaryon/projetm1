#include <iostream>     // entree/sorties
#include <math.h>
#include <fstream>

#include "classes.h"

using namespace std ;

// déclaration des variables globales

int blanc = 11 ;
int noir = 22 ;

// éxecution du programme final en C++

int main()
{
	cout << "OTHELLO -- par Elianor et Pierre" << endl << endl ;

	grille grille_de_jeu ;

	int mode_de_jeu ;
	cout << "Quel sera le mode de jeu ?" << endl ;
	cout << "Mode jeu (1), Mode Stats (2)" << endl ;
	cin >> mode_de_jeu ;
	cout << endl ;

	string nom_fichier = "vide" ;
	

	int nb_generations = 1, nb_parties = 1 ;
	if (mode_de_jeu == 2) 
	{
		cout << "Combien de générations ?" << endl ;
		cin >> nb_generations ;
		cout << endl ;
		cout << "Combien de parties ?" << endl ;
		cin >> nb_parties ;
		cout << endl ;
		cout << "Quel nom pour le fichier ?" << endl ;
		cin >> nom_fichier ;
		cout << endl ;
	}

	fstream fich ;
	fich.open("data/"+nom_fichier+".dat", ios::out) ;
	
	humain *joueur1, *joueur2 ;

	humain h1, h2 ;
	ordiAleatoire oa1, oa2 ;
	ordiRetourneMax orm1, orm2 ;
	ordiMinMaxRapide omm1, omm2 ;
	int profondeur_max1, profondeur_max2 ;

	int num_joueur1, num_joueur2 ;
	cout << "Qui sera le joueur noir ? (premier à jouer)" << endl ;
	cout << "humain (1), ordiAleatoire (2), ordiRetourneMax (3), ordiMinMax (4)" << endl ;
	cin >> num_joueur1 ;
	cout << endl ;
	cout << "Qui sera le joueur blanc ? (deuxième à jouer)" << endl ;
	cout << "humain (1), ordiAleatoire (2), ordiRetourneMax (3), ordiMinMax (4)" << endl ;
	cin >> num_joueur2 ;
	cout << endl ;
	
	if (num_joueur1 == 2)
		joueur1 = &oa1 ;
	else if (num_joueur1 == 3)
		joueur1 = &orm1 ;
	else if (num_joueur1 == 4)
	{
		joueur1 = &omm1 ;
		cout << "Quelle profondeur ? (stric. > 0)" << endl ;
		cin >> profondeur_max1 ;
	}
	else 
		joueur1 = &h1 ;

	if (num_joueur2 == 2)
		joueur2 = &oa2 ;
	else if (num_joueur2 == 3)
		joueur2 = &orm2 ;
	else if (num_joueur2 == 4)
	{
		joueur2 = &omm2 ;
		cout << "Quelle profondeur ? (stric. > 0)" << endl ;
		cin >> profondeur_max2 ;
	}
	else 
		joueur2 = &h2 ;

	if ((num_joueur1 != num_joueur2) && (mode_de_jeu == 2)) 
		nb_parties = int(nb_parties/2) ;

	int points_noir, points_blanc, gagnant = 0 ;	// gagnant: 0 = égalité ; 1 = blanc a gagné ; 2 = noir a gagné

	int temps = int(time(NULL)) ;
	cout << temps << endl ;

	for (size_t i = 0 ; i < unsigned(nb_generations) ; i++)
	{
		joueur1->init(noir, profondeur_max1) ;
		joueur2->init(blanc, profondeur_max2) ;
		for (size_t j = 0 ; j < unsigned(nb_parties) ; j++)	
		{	
			points_noir = 0 ; points_blanc = 0 ;						
			grille_de_jeu.init() ;
			int coup_x = 0, coup_y = 0 ;
			while (!grille_de_jeu.jeuFini())
			{
				if ((grille_de_jeu.recupNumeroTour() % 2 == 0) && (grille_de_jeu.recupNbLicites(noir) != 0))
				{
					if (mode_de_jeu == 1)
					{
						cout << endl ;
						cout << "Au tour de noir !" << endl ;
						grille_de_jeu.affichageJeu() ;
					}
					joueur1->choixCoups(grille_de_jeu, &coup_x, &coup_y) ;
					grille_de_jeu.retournerPlacer(coup_x, coup_y, noir) ;
				}
				else if ((grille_de_jeu.recupNumeroTour() % 2 != 0) && (grille_de_jeu.recupNbLicites(blanc) != 0))
				{
					if (mode_de_jeu == 1)
					{
						cout << endl ;
						cout << "Au tour de blanc !" << endl ;
						grille_de_jeu.affichageJeu() ;
					}
					joueur2->choixCoups(grille_de_jeu, &coup_x, &coup_y) ;
					grille_de_jeu.retournerPlacer(coup_x, coup_y, blanc) ;
				}
				grille_de_jeu.incrementNumeroTour() ;
			}
			grille_de_jeu.gagnant(&points_blanc, &points_noir, &gagnant) ;

			if (mode_de_jeu == 1)
			{
				cout << endl << endl ;
				cout << "Jeu Terminé !" << endl ;
				grille_de_jeu.affichageJeu() ;
				if (gagnant == 2)
					cout << "Joueur Noir a gagné ! " << points_noir << " contre "  << points_blanc << " pour Joueur Blanc" << endl ;
				else if (gagnant == 1)
					cout << "Joueur Blanc a gagné ! " << points_blanc << " contre "  << points_noir << " pour Joueur Noir" << endl ;
				else
					cout << "Egalité ! " << points_blanc << " partout !" << endl ;
				cout << endl ;
				cout << "Merci d'avoir joué !" << endl ;
			}
			else if (mode_de_jeu == 2)
				fich << points_blanc << ' ' << points_noir << ' ' << gagnant << endl ;
		}

		if ((num_joueur1 != num_joueur2) && (mode_de_jeu == 2))
		{
			joueur1->init(blanc, profondeur_max1) ;
			joueur2->init(noir, profondeur_max2) ;
			for (size_t j = 0 ; j < unsigned(nb_parties) ; j++)	
			{	
				points_noir = 0 ; points_blanc = 0 ;						
				grille_de_jeu.init() ;
				int coup_x = 0, coup_y = 0 ;
				while (!grille_de_jeu.jeuFini())
				{
					if ((grille_de_jeu.recupNumeroTour() % 2 == 0) && (grille_de_jeu.recupNbLicites(noir) != 0))
					{
						joueur2->choixCoups(grille_de_jeu, &coup_x, &coup_y) ;
						grille_de_jeu.retournerPlacer(coup_x, coup_y, noir) ;
					}
					else if ((grille_de_jeu.recupNumeroTour() % 2 != 0) && (grille_de_jeu.recupNbLicites(blanc) != 0))
					{
						joueur1->choixCoups(grille_de_jeu, &coup_x, &coup_y) ;
						grille_de_jeu.retournerPlacer(coup_x, coup_y, blanc) ;
					}
					grille_de_jeu.incrementNumeroTour() ;
				}
				grille_de_jeu.gagnant(&points_blanc, &points_noir, &gagnant) ;
				fich << points_noir << ' ' << points_blanc << ' ' << gagnant << endl ;
			}
		}

		cout << (100*i)/nb_generations << " %     " << endl ;
	}

	fich.close() ;

	cout << int(time(NULL))-temps << endl ;

	return 0 ;
}
