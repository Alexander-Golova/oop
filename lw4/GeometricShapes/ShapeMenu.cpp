#include "stdafx.h"

#include "ShapeMenu.h"
#include <boost/algorithm/string.hpp>

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

void CShapeMenu::CheckTriangleArguments(const vector<string> & parametersList)
{
	if ((parametersList.size() != 7 && parametersList.size() != 9))
	{
		throw invalid_argument("Incorrect amount arguments! Must will be 7 or 9!");
	}
}

void CShapeMenu::CheckRectangleArguments(const std::vector<std::string> & parametersList)
{
	if ((parametersList.size() != 5 && parametersList.size() != 7))
	{
		throw invalid_argument("Incorrect amount arguments! Must will be 5 or 7!");
	}
}

void CShapeMenu::CheckCircleArguments(const std::vector<std::string> & parametersList)
{
	if ((parametersList.size() != 4 && parametersList.size() != 6))
	{
		throw invalid_argument("Incorrect amount arguments! Must will be 4 or 6!");
	}
}

void CShapeMenu::CheckLineSegmentArguments(const std::vector<std::string> & parametersList)
{
	if ((parametersList.size() != 5 && parametersList.size() != 6))
	{
		throw invalid_argument("Incorrect amount arguments! Must will be 5 or 6!");
	}
}

void CShapeMenu::AddTriangle(const vector<string> & parametersList)
{
	CheckTriangleArguments(parametersList);

	SPoint vertex1 = { stod(parametersList[1]), stod(parametersList[2]) };
	SPoint vertex2 = { stod(parametersList[3]), stod(parametersList[4]) };
	SPoint vertex3 = { stod(parametersList[5]), stod(parametersList[6]) };
	string outlineColor = "000000";
	string fillColor = "ffffff";

	if (parametersList.size() == 9)
	{
		outlineColor = parametersList[7];
		fillColor = parametersList[8];
	}
	auto triangle = make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
	m_shapesList.push_back(triangle);
}

void CShapeMenu::AddRectangle(const std::vector<std::string> & parametersList)
{
	CheckRectangleArguments(parametersList);

	SPoint leftTop = { stod(parametersList[1]), stod(parametersList[2]) };
	SPoint rightBottom = { stod(parametersList[3]), stod(parametersList[4]) };
	string outlineColor = "000000";
	string fillColor = "ffffff";

	if (parametersList.size() == 7)
	{
		outlineColor = parametersList[5];
		fillColor = parametersList[6];
	}
	auto rectangle = make_shared<CRectangle>(leftTop, rightBottom, outlineColor, fillColor);
	m_shapesList.push_back(rectangle);
}

void CShapeMenu::AddCircle(const std::vector<std::string> & parametersList)
{
	CheckCircleArguments(parametersList);

	SPoint center = { stod(parametersList[1]), stod(parametersList[2]) };
	double radius = stod(parametersList[3]);
	string outlineColor = "000000";
	string fillColor = "ffffff";

	if (parametersList.size() == 6)
	{
		outlineColor = parametersList[4];
		fillColor = parametersList[5];
	}
	auto circle = make_shared<CCircle>(center, radius, outlineColor, fillColor);
	m_shapesList.push_back(circle);
}

void CShapeMenu::AddLineSegment(const std::vector<std::string> & parametersList)
{
	CheckLineSegmentArguments(parametersList);

	SPoint startPoint = { stod(parametersList[1]), stod(parametersList[2]) };
	SPoint endPoint = { stod(parametersList[3]), stod(parametersList[4]) };
	string outlineColor = "000000";

	if (parametersList.size() == 6)
	{
		outlineColor = parametersList[5];
	}
	auto lineSegment = make_shared<CLineSegment>(startPoint, endPoint, outlineColor);
	m_shapesList.push_back(lineSegment);
}

void CShapeMenu::PrintInfo() const
{
	for (const auto shape : m_shapesList)
	{
		cout << shape->ToString() << endl;
	}
}


void CShapeMenu::ReadShape(string shape)
{
	boost::to_lower(shape);
	vector<string> parametersList;
	boost::split(parametersList, shape, boost::is_any_of(" "));
	if (parametersList[0] == "triangle")
	{
		AddTriangle(parametersList);
	}
	else if (parametersList[0] == "rectangle")
	{
		AddRectangle(parametersList);
	}
	else if (parametersList[0] == "circle")
	{
		AddCircle(parametersList);
	}
	else if (parametersList[0] == "linesegment")
	{
		AddLineSegment(parametersList);
	}
	else if (parametersList[0] == "info")
	{
		PrintInfo();
	}
	else
	{
		throw invalid_argument("Incorrect command.");
	}
}
