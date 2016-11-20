#pragma 

#include "stdafx.h"
#include "ShapeMenu.h"
#include "Shapes.h"

using namespace std;


CShapeMenu::CShapeMenu(const string & shape)
{
	ReadShape(shape);
}

void CShapeMenu::CheckArgumentsTriangle(const vector<string> & listParameters)
{
	if ((listParameters.size() != 6 && listParameters.size() != 8))
	{
		throw invalid_argument("Incorrect amount arguments! Must will be 6 or 8!");
	}
}

void CShapeMenu::CheckArgumentsRectangle(const std::vector<std::string> & listParameters)
{
	if ((listParameters.size() != 4 && listParameters.size() != 6))
	{
		throw invalid_argument("Incorrect amount arguments! Must will be 4 or 6!");
	}
}


void CShapeMenu::AddTriangle(const vector<string> & listParameters)
{
	CheckArgumentsTriangle(listParameters);

	SPoint vertex1 = { stod(listParameters[1]), stod(listParameters[2]) };
	SPoint vertex2 = { stod(listParameters[3]), stod(listParameters[4]) };
	SPoint vertex3 = { stod(listParameters[5]), stod(listParameters[6]) };
	string outlineColor = "000000";
	string fillColor = "ffffff";

	if (listParameters.size() == 8)
	{
		outlineColor = listParameters[7];
		fillColor = listParameters[8];
	}
	shared_ptr<CTriangle> addTriangle(new CTriangle(vertex1, vertex2, vertex3, outlineColor, fillColor));
	m_shapesList.push_back(addTriangle);
}

void CShapeMenu::AddRectangle(const std::vector<std::string> & listParameters)
{
	CheckArgumentsRectangle(listParameters);

	SPoint leftTop = { stod(listParameters[1]), stod(listParameters[2]) };
	SPoint rightBottom = { stod(listParameters[3]), stod(listParameters[4]) };
	string outlineColor = "000000";
	string fillColor = "ffffff";

	if (listParameters.size() == 6)
	{
		outlineColor = listParameters[5];
		fillColor = listParameters[6];
	}
	shared_ptr<CRectangle> addRectangle(new CRectangle(leftTop, rightBottom, outlineColor, fillColor));
	m_shapesList.push_back(addRectangle);
}



void CShapeMenu::ReadShape(string shape)
{
	boost::to_lower(shape);
	vector<string> listParameters;
	boost::split(listParameters, shape, boost::is_any_of(" "));
	if (listParameters[0] == "triangle")
	{
		AddTriangle(listParameters);
	}
	else if (listParameters[0] == "rectangle")
	{
		AddRectangle(listParameters);
	}
}
