#pragma 

#include "stdafx.h"
#include "ShapeMenu.h"
#include "Shape.h"
#include "IShape.h"


using namespace std;

void CShapeMenu::PrintShapeMinPerimeter()
{
	if (m_shapesList.empty())
	{
		return;
	}
	auto shapeMinPerimeter = min_element(m_shapesList.cbegin(), m_shapesList.cend(), [](const auto & arg1, const auto & arg2) {
		 return arg1->GetPerimeter() < arg2->GetPerimeter();
	});
	cout << "Shape with small perimetr: " << (*shapeMinPerimeter)->ToString() << endl;
}

void CShapeMenu::PrintShapeMaxAreaShape()
{
	if (m_shapesList.empty())
	{
		return;
	}
	auto shapeMaxArea = max_element(m_shapesList.cbegin(), m_shapesList.cend(), [](const auto & arg1, const auto & arg2) {
		 return arg1->GetArea() < arg2->GetArea();
	});
	cout << "Shape with large area: " << (*shapeMaxArea)->ToString() << endl;
}

void CShapeMenu::CheckArgumentsTriangle(const vector<string> & listParameters)
{
	if ((listParameters.size() != 7 && listParameters.size() != 9))
	{
		throw invalid_argument("Incorrect amount arguments! Must will be 7 or 9!");
	}
}

void CShapeMenu::CheckArgumentsRectangle(const std::vector<std::string> & listParameters)
{
	if ((listParameters.size() != 5 && listParameters.size() != 7))
	{
		throw invalid_argument("Incorrect amount arguments! Must will be 5 or 7!");
	}
}

void CShapeMenu::CheckArgumentsCircle(const std::vector<std::string> & listParameters)
{
	if ((listParameters.size() != 4 && listParameters.size() != 6))
	{
		throw invalid_argument("Incorrect amount arguments! Must will be 4 or 6!");
	}
}

void CShapeMenu::CheckArgumentsLineSegment(const std::vector<std::string> & listParameters)
{
	if ((listParameters.size() != 5 && listParameters.size() != 6))
	{
		throw invalid_argument("Incorrect amount arguments! Must will be 5 or 6!");
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

	if (listParameters.size() == 9)
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

	if (listParameters.size() == 7)
	{
		outlineColor = listParameters[5];
		fillColor = listParameters[6];
	}
	shared_ptr<CRectangle> addRectangle(new CRectangle(leftTop, rightBottom, outlineColor, fillColor));
	m_shapesList.push_back(addRectangle);
}

void CShapeMenu::AddCircle(const std::vector<std::string> & listParameters)
{
	CheckArgumentsCircle(listParameters);

	SPoint center = { stod(listParameters[1]), stod(listParameters[2]) };
	double radius = stod(listParameters[3]);
	string outlineColor = "000000";
	string fillColor = "ffffff";

	if (listParameters.size() == 6)
	{
		outlineColor = listParameters[4];
		fillColor = listParameters[5];
	}
	shared_ptr<CCircle> addCircle(new CCircle(center, radius, outlineColor, fillColor));
	m_shapesList.push_back(addCircle);
}

void CShapeMenu::AddLineSegment(const std::vector<std::string> & listParameters)
{
	CheckArgumentsLineSegment(listParameters);

	SPoint startPoint = { stod(listParameters[1]), stod(listParameters[2]) };
	SPoint endPoint = { stod(listParameters[3]), stod(listParameters[4]) };
	string outlineColor = "000000";

	if (listParameters.size() == 6)
	{
		outlineColor = listParameters[5];
	}
	shared_ptr<CLineSegment> addLineSegment(new CLineSegment(startPoint, endPoint, outlineColor));
	m_shapesList.push_back(addLineSegment);
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
	else if (listParameters[0] == "circle")
	{
		AddCircle(listParameters);
	}
	else if (listParameters[0] == "linesegment")
	{
		AddLineSegment(listParameters);
	}
	else
	{
		throw invalid_argument("Incorrect command.");
	}
}
