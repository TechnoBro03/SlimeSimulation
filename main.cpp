#include "Simulation.h"

int main()
{
	Settings settings("Settings.txt");
	Simulation simulation(&settings);
	simulation.run();

	return 0;
}