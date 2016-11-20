#pragma 

#include "stdafx.h"
#include "ShapeMenu.h"
#include "Shapes.h"

using namespace std;


CShapeMenu::CShapeMenu(const string & shape)
{
	ReadShapes(shape);
}

bool CShapeMenu::CheckArgumentsTriangle(const vector<string> & shapes)
{
	if ((shapes.size() == 6 || shapes.size() == 8))
	{
		return true;
	}
	else
	{
		throw invalid_argument("Transferred not the correct parameters for a triangle");
		return false;
	}
}

void CShapeMenu::AddTriangle(const vector<string> & shapes)
{
	SPoint const & vertex1 = { stoi(shapes[1]), stoi(shapes[2]) };
	SPoint const & vertex2 = { stoi(shapes[3]), stoi(shapes[4]) };
	SPoint const & vertex3 = { stoi(shapes[5]), stoi(shapes[6]) };
	string outlineColor = "000000";
	string fillColor = "ffffff";

	if (shapes.size() == 8)
	{
		outlineColor = shapes[7];
		string fillColor = shapes[8];
	}
	shared_ptr<CTriangle> addTriangle(new CTriangle(vertex1, vertex2, vertex3, outlineColor, fillColor));
	m_shapesList.push_back(addTriangle);
}

void CShapeMenu::ReadShapes(string shape)
{
	boost::to_lower(shape);
	vector<string> shapes;
	boost::split(shapes, shape, boost::is_any_of(" "));
	if (shapes[0] == "triangle" && CheckArgumentsTriangle(shapes))
	{
		AddTriangle(shapes);
	}
}
