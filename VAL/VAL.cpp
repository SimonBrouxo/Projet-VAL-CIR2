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

void Station::setStation_noun() {
	cout << "Nom de la station : ";
	string noun;
	getline(cin,noun);
}

string Station::getStation_noun() {
	return noun;
}

void Station::setStation_id() {
	cout << "Numéro de la station : ";
	cin >> id;
}

int Station::getStation_id() {
	return id;
}

void Station::setStation_xy() {
	cout << "Position de la station : ";
	cin >> pos_x >> pos_y;
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

void Station::setStation_nb_people() {
	cout << "Nombre de personne dans la station : ";
	cin >> nb_people;
}

int Station::getStation_nb_people(){
	return nb_people;
}

void Station::setStation() {
	cout << "Nom de la station : ";
	cin >> noun;
	cout << "Numéro de la station : ";
	cin >> id;
	cout << "Position de la station : ";
	cin >> pos_x >> pos_y;
	cout << "Nombre de personne dans la station : ";
	cin >> nb_people;
	cout << endl;
}

void Station::printStation_stats() {
	cout << "La station " << getStation_noun() <<
		" numéro " << getStation_id() <<
		" en (" << getStation_x() << "," << getStation_y() << ")" <<
		" regroupe " << getStation_nb_people() << " personnes." << endl;
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

void Rame::setRame_id() {
	cout << "Numéro de la rame : ";
	cin >> id;
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

void Rame::setRame_nb_passenger() {
	cout << "Nombre de passagers : ";
	cin >> nb_passenger;
}

int Rame::getRame_nb_passenger() {
	return nb_passenger;
}

void Rame::setRame() {
	cout << "Numéro de la rame : ";
	cin >> id;
	/*
	cout << "Position de la rame : ";
	cin >> pos_x >> pos_y;
	cout << "Vitesse de la rame : ";
	cin >> speed;
	*/
	cout << "Nombre de passagers : ";
	cin >> nb_passenger;
	cout << endl;
}

void Rame::printRame_stats() {
	cout <<
		"La rame " << getRame_id() <<
		" en : (" << getRame_x() << "," << getRame_y() << ")" <<
		" se déplace à " << getRame_speed() << "km/h" <<
		" avec " << getRame_nb_passenger() << " passagers." << endl;
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




float distance(Vector2f& v1, Vector2f& v2) 
{
	float dx = v2.x - v1.x;
	float dy = v2.y - v1.y;
	return sqrt(dx * dx + dy * dy);
}