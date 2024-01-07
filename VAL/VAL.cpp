﻿#include "VAL.hpp"


/**********************************************************************************/
/*******************************    Station     ***********************************/
/**********************************************************************************/


Station::Station(string noun, int id, float x, float y, int nb_people) {
	this->noun = noun;
	this->id = id;
	this->pos_x = x;
	this->pos_y = y;
	this->nb_people = nb_people;
}

void Station::setStation() {
	cout << "Nom de la station : ";
	cin >> noun;
	cout << "Numéro de la station : ";
	cin >> id;
	cout << "Position de la station : ";
	cin >> pos_x >> pos_y;
	/*cout << "Nombre de personne dans la station : ";
	cin >> nb_people;*/
	cout << endl;
}

string Station::getStation_noun() {
	return noun;
}

int Station::getStation_id() {
	return id;
}

float Station::getStation_x() {
	return pos_x;
}

float Station::getStation_y() {
	return pos_y;
}

Vector2f Station::getStation_xy() {
	return Vector2f(pos_x, pos_y);
}

//void Station::setStation_nb_people( int new_nb_people) {
//	nb_people = new_nb_people;
//}

int Station::getStation_nb_people(){
	return nb_people;
}



/**********************************************************************************/
/*******************************      Rame      ***********************************/
/**********************************************************************************/


Rame::Rame(int id, float x, float y, float speed, int nb_passenger) {
	this->id = id;
	this->pos_x = x;
	this->pos_y = y;
	this->speed = speed;
	this->nb_passenger = nb_passenger;
}

void Rame::setRame() {
	cout << "Numéro de la rame : ";
	cin >> id;
	cout << "Nombre de passagers : ";
	cin >> nb_passenger;
	cout << endl;
}

int Rame::getRame_id() {
	return id;
}

void Rame::setRame_xy(float new_x, float new_y) {
	pos_x = new_x;
	pos_y = new_y;
}

float Rame::getRame_x() {
	return pos_x;
}

float Rame::getRame_y() {
	return pos_y;
}

void Rame::setRame_speed(float new_speed) {
	speed = new_speed;
}

float Rame::getRame_speed() {
	return speed;
}

void Rame::setRame_nb_passenger(int new_nb_passenger) {
	nb_passenger = new_nb_passenger;
}

int Rame::getRame_nb_passenger() {
	return nb_passenger;
}



/**********************************************************************************/
/*****************************    Superviseur     *********************************/
/**********************************************************************************/


Superviseur::Superviseur(int nbStation, int nbRame) {
	this->nbStation = nbStation;
	this->nbRame = nbRame;
}

int Superviseur::getNbStation() {
	return nbStation;
}

int Superviseur::getNbRame() {
	return nbRame;
}


/**********************************************************************************/

// Fonction pour calculer la distance entre deux points
float distance(Vector2f& v1, Vector2f& v2) 
{
	float dx = v2.x - v1.x;
	float dy = v2.y - v1.y;
	return sqrt(dx * dx + dy * dy);
}

mutex peopleMutex;
// Fonction pour gérer l'entrée des passagers dans une rame
void entrerPersonnesRame(Rame& rame) 
{
	lock_guard<mutex> lock(peopleMutex);
	int nbPassagers = rand() % (NB_MAX_PERSONNE_RAME - rame.getRame_nb_passenger() + 1); // MAX - random pour ne pas dépassé la limite de passagers
	rame.setRame_nb_passenger(rame.getRame_nb_passenger() + nbPassagers);
	cout << "\tRame " << rame.getRame_id() << " : +" << nbPassagers << " passagers" << endl;
}

// Fonction pour gérer la sortie des passagers d'une rame
void sortirPersonnesRame(Rame& rame) 
{
	lock_guard<mutex> lock(peopleMutex);
	int nbPassagers = rand() % (rame.getRame_nb_passenger() + 1);rame.setRame_nb_passenger(rame.getRame_nb_passenger() - nbPassagers);
	cout << "\tRame " << rame.getRame_id() << " : -" << nbPassagers << " passagers" << endl;
}

// Fonction pour gérer l'entrée des personnes dans une station
//void entrerPersonnesStation(Station& station) 
//{
//	lock_guard<mutex> lock(peopleMutex);
//	int nbPersonnes = rand() % (NB_MAX_PERSONNE_STATION + 1); // Nombre aléatoire de personnes à entrer dans la station
//	station.setStation_nb_people(station.getStation_nb_people() + nbPersonnes);
//	cout << station.getStation_id() << " : +" << nbPersonnes << endl;
//}