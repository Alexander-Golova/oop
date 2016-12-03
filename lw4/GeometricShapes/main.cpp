#include "stdafx.h"

#include "IShape.h"
#include "ShapeMenu.h"

using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count" << endl
             << "Usage: Shapes.exe <file with commands>" << endl;
		return 1;
	}
	CShapeMenu menu;
	string shape;
	ifstream input(argv[1]);
	try
	{
		while (!input.eof() && !input.fail())
		{
			getline(input, shape);
			menu.ReadShape(shape);
		}
		menu.PrintShapeMinPerimeter();
		menu.PrintShapeMaxAreaShape();
	}	
	catch (const exception & e)
	{
		cout << e.what() << endl;
	}
    return 0;
}
