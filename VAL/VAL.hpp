#pragma once

#include <iostream>
#include <cstdlib>
#include <locale>

#define NB_MAX_RAME 10

using namespace std;


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
		
		// Stats
		void setRame_xy();
		float getRame_x();
		float getRame_y();
		void setRame_id();
		int getRame_id();
		void setRame_speed();
		float getRame_speed();
		void setRame_nb_passenger();
		int getRame_nb_passenger();
		void printRame_stats();
		
		// Action
		float Rame_acceleration(float vitesse, float distance);
		float Rame_deceleration(float vitesse, float distance);
};

class Superviseur {

};

class Station {
	private:
		string noun;
		int id;
		int pos_x;
		int pos_y;
		int nb_people;
	public:
		// Construtor
		Station() {};
		Station(string noun, int id, int x, int y, int, int nb_people);

		// Setter / Getters
		void setStation_noun();
		string getStation_noun();
		void setStation_id();
		int getStation_id();
		void setStation_xy();
		int getStation_x();
		int getStation_y();
		void setStation_nb_people();
		int getStation_nb_people();
};