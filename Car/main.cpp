#include <iostream>
#include "Car.h"
#include "CarMenu.h"

int main()
{
	CCar car;

	CCarMenu carMenu(car);

	std::string command;
	std::cout << std::endl
			  << ">";
	while (getline(std::cin, command))
	{		
		carMenu.RunCommand(command);
		std::cout << std::endl
				  << ">";
	}
	return 0;
}
