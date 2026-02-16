// Namen: Jordy van Brakel en Thorsten Hopman
// Naam bestanden: OthelloHoofd.cc, Othello4.cc, Othello4.h
// De C++ code is gemaakt in gedit
// En is gecompileerd met G++
// Datum 10-12-2018
// Dit programma maakt het spel Othello
// Het spel kan gespeeld worden tussen 2 menselijke spelers, maar ook met 1 of 2 computers
// Ook kan de gebruiker het othellobord aanpassen
// En creeert het programma relevate statistieken voor een experiment

#include <iostream>
#include <cstdlib>
#include "oth.h"
using namespace std;

void infoblokje ();
void menu ();

int main()
{
	infoblokje ();
	menu (); //Menu, handelt de rest van het programma af

 	return 0;
}
