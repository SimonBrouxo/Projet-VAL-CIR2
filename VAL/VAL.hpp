// VAL.h : fichier d'en-tête de votre cible.

#pragma once

#include <iostream>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;
class Metro {
	private:
	Rame rame;
	int Rame::Station ;
    public:
	  int number;
	  float position;
	  float speed;
	  int passangers;
};

class Rame : Metro {
	private:
		int num;
		int pos_x;
		int pos_y;
		int vitesse;
		int nb_passagers;
	public:
		int number;
		float position;
		float speed;
		int passengers;
		Rame::station * currentStation;

		Metro(int number& num, float pos, float spd, int pass, Station; int*Rame::station)
			: number(num), position(pos), speed(spd), passengers(pass), currentStation(station) {}

		void move() {
			while (true) {
				std::this_thread::
					std::this_thread::sleep_for

					sleep_for(std::chrono::seconds(1));

				std::lock_guard<std::mutex> lock

					std::lock_guard<std::mutex>
					std::lock_guard<std::mutex> lock(mtx);  // Verrouillage du mutex pour éviter les conflits
				position += vitesse;
				std::cout <<
					position += vitesse;
				std::cou


		};

class Superviseur {
public:
	void surveillerPositionRames(const Rame& rame1, const Rame& rame2) {
		while (true) {
			std::this_thread::sleep_for(std::chrono::seconds(2));

			std
};



class Station {
public:
	int passagers;
	int Rame::Station::station(); :passagers(0) {}
	void(); {
		while (true) {
			std::this_thread::
				std::t
				sleep_for(std::chrono::seconds(2));
			std::lock_guard<std::mutex> lock(mtx);
			if (rame.position >= 100 && rame.position <= 120) {

				rame.vitesse = 0;
				std::cout <<
					std::cout
					"Rame " << rame.numero << " - Arrêt à la station\n";






	}
};