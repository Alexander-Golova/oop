#include "stdafx.h"

#include "Car.h"
#include "CarMenu.h"

using namespace std;

int main(int, char *[])
{
	CCar car;
	CCarMenu carMenu(car);

	string command;
	cout << endl << ">";
	while (getline(cin, command))
	{
		carMenu.RunCommand(command);
		cout << endl << ">";
	}
	return 0;
}
