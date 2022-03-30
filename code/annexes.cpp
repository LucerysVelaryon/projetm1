#include <iostream>     // entrée/sorties
#include <math.h>

using namespace std ;

bool estVide(int i) 
{
	return (i == 0 || i == -1 || i == 1 || i == 2) ;
}

bool permiseB(int i)
{
	return (i == 0 || i == 1) ;
}

bool permiseN(int i)
{
	return (i == 0 || i == 2) ;
}