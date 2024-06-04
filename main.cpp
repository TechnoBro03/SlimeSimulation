#include "Simulation.h"

int main()
{
	try
	{
		Settings settings("Settings.txt");
		Simulation simulation(&settings);
		simulation.run();
	}
	catch (...)
	{
		std::cout << "There was an error." << std::endl;
	}
	
	return 0;
}