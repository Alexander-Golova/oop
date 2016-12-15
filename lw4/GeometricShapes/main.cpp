#include "stdafx.h"

#include "IShape.h"
#include "ShapeMenu.h"

using namespace std;

int main(int, char * [])
{
	CShapeMenu menu;
	string command;
	try
	{
		while (getline(cin, command))
		{
			menu.ReadShape(command);
		}
		menu.PrintShapeMinPerimeter();
		menu.PrintShapeMaxAreaShape();
		menu.PrintInfo();
	}	
	catch (const exception & e)
	{
		cerr << e.what() << endl;
	}
    return 0;
}
