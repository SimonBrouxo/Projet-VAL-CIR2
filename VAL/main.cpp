#include "VAL.hpp"


int main()
{
	locale::global(locale{ "fr-FR" });

	Rame rameA;
	rameA.setRame();
	rameA.printRame_stats();
	Rame rameB(22, 5.4f, 5.6f, 50.4f, 34);
	rameB.printRame_stats();





	return EXIT_SUCCESS;
}