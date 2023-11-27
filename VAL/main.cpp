#include "VAL.hpp"


int main()
{
	locale::global(locale{ "fr-FR" });

	Rame rameA;
	rameA.setRame_id();
	rameA.setRame_xy();
	rameA.setRame_nb_passenger();
	rameA.setRame_speed();
	rameA.printRame_stats();





	return EXIT_SUCCESS;
}