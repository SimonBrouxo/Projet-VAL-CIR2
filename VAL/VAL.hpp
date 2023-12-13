#pragma once
#include <iostream>
#include <cstdlib>
#include <locale>
#include <string>
#include <map>
#include <vector>

#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>


using namespace std;
using namespace sf;

#define _PATH_IMG_ "C:/Program Files/SFML/img/"
const string path_image(_PATH_IMG_);

const int WIN_WIDTH = 1200;
const int WIN_HEIGHT = 800;

class Rame {
	private:
		int id;
		float pos_x;
		float pos_y;
		float speed;
		int nb_passenger;
	public:

		// Constructor
		Rame() {};
		Rame(int id, float x, float y, float speed, int nb_passenger);
		
		// Setter / Getter
		void setRame_xy();
		float getRame_x();
		float getRame_y();
		void setRame_id();
		int getRame_id();
		void setRame_speed();
		float getRame_speed();
		void setRame_nb_passenger();
		int getRame_nb_passenger();
		void setRame();
		void printRame_stats();
		
		// Méthodes
		float Rame_acceleration(float vitesse, float distance);
		float Rame_deceleration(float vitesse, float distance);
};

class Superviseur {
	private:
		int nbStation;
		int nbRame;
	public:

		// Constructeur
		Superviseur() {};
		Superviseur(int nbStation, int nbRame);

		// Setter / getter
		int getNbStation();
		int getNbRame();
};

class Station {
	private:
		string noun;
		int id;
		float pos_x;
		float pos_y;
		int nb_people;
	public:
		// Construtor
		Station() {};
		Station(string noun, int id, float x, float y, int nb_people);

		// Setter / Getters
		void setStation_noun();
		string getStation_noun();
		void setStation_id();
		int getStation_id();
		void setStation_xy();
		float getStation_x();
		float getStation_y();
		Vector2f getStation_xy();
		void setStation_nb_people();
		int getStation_nb_people();
		void setStation();
		void printStation_stats();
};