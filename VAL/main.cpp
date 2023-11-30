#include "VAL.hpp"
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

int main()
{
	locale::global(locale{ "fr-FR" });
	/*
	Rame rameA;
	rameA.setRame();
	rameA.printRame_stats();
	Rame rameB(22, 5.4f, 5.6f, 50.4f, 34);
	rameB.printRame_stats();
	*/
	Station stationA;
	stationA.setStation();
	stationA.printStation_stats();
	//Station stationB("Gare Lille Flandres", )






	return EXIT_SUCCESS;
}