#pragma once
#include <iostream>
#include <cstdlib>
#include <locale>
#include <string>
#include <map>
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


using namespace std;
using namespace sf;

#define _PATH_IMG_ "C:/Program Files/SFML/img/"
const string path_image(_PATH_IMG_);

const int WIN_WIDTH = 1200;
const int WIN_HEIGHT = 800;

const int MAX_SPRITE_RAMES = 20;

const int NB_MAX_PERSONNE_STATION = 100;
const int NB_MAX_PERSONNE_RAME = 30;


/**********************************************************************************/
/*******************************    Station     ***********************************/
/**********************************************************************************/


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
		void setStation_nb_people(int new_nb_people);
		int getStation_nb_people();
		void setStation();
		void printStation_stats();
};


/**********************************************************************************/
/*******************************      Rame      ***********************************/
/**********************************************************************************/


class Rame {
	private:
		int id;
		float pos_x;
		float pos_y;
		float speed;
		int nb_passenger;
	public:

		// Constructor
		//Rame() {};
		Rame(int id, float x, float y, float speed, int nb_passenger);
		
		// Setter / Getter
		void setRame_xy(float new_x, float new_y);
		float getRame_x();
		float getRame_y();
		void setRame_id();
		int getRame_id();
		void setRame_speed(float new_speed);
		float getRame_speed();
		void setRame_nb_passenger(int new_nb_passenger);
		int getRame_nb_passenger();
		void setRame();
		void printRame_stats();
};


/**********************************************************************************/
/*****************************    Superviseur     *********************************/
/**********************************************************************************/


class Superviseur {
	private:
		int nbStation;
		int nbRame;
	public:

		// Constructeur
		//Superviseur() {};
		Superviseur(int nbStation, int nbRame);

		// Setter / getter
		int getNbStation();
		int getNbRame();
};


// Prototypes des fonctions
float distance(Vector2f& v1, Vector2f& v2);
void moveRame(int id, float x, float y, float speed, int nb_passenger, const vector<float>& coord_x_s, const vector<float>& coord_y_s, vector<Vector2f>& ramePositions);
void entrerPersonnesRame(Rame& rame);
void sortirPersonnesRame(Rame& rame);
void entrerPersonnesStation(Station& station);

