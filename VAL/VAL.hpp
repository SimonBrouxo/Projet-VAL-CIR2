// VAL.h : fichier d'en-tête de votre cible.

#pragma once

#include <iostream>

using namespace std;

class Metro {
	private:
	Rame rame;
	Superviseur superviseur;
	Station station;
};

class Rame : Metro {
	private:
		int num;
		int pos_x;
		int pos_y;
		int vitesse;
		int nb_passagers;
	public:

};

class Superviseur {

};

class Station {

};