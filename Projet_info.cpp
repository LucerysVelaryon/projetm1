#include <iostream>     // entrée/sorties
#include <math.h>

using namespace std;

int grille[8][8];		//Déclaration grille


void grille_init()		
{
	for (int i=0; i<8; i++)
		for (int j=0; j<8; j++)
			grille[i][j] = -1;

	grille[3][3] = 11 ; grille[4][4] = 11;
	grille[3][4] = 22 ; grille[4][3] = 22;
	grille[2][4] = 1 ; grille[3][5] = 1 ; grille[5][3] = 1 ; grille[4][2] = 1;
	grille[2][3] = 2 ; grille[3][2] = 2 ; grille[5][4] = 2 ; grille[4][5] = 2;
}

void affichageBrut()
{
	for (int i=0; i<8; i++)
	{	
		cout << " | " ;
		for (int j=0; j<8; j++)
			if (grille[i][j] == 1)
				cout << "01" << " | " ;
			else if (grille[i][j] == 2)
				cout << "02" << " | " ;
			else
				cout << grille[i][j] << " | " ;
		cout << endl;
	}
}

int main()
{
	grille_init();
	affichageBrut();

	return 0;
}