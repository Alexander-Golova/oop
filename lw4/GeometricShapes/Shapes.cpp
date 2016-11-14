#include "stdafx.h"
#include "Shapes.h"

using namespace std;

CTriangle::CTriangle(SPoint const & Vertex1, SPoint const & Vertex2, SPoint const & Vertex3)
	: m_Vertex1(Vertex1)
	, m_Vertex2(Vertex2)
	, m_Vertex3(Vertex3)
{
}

tuple<double, double, double> CTriangle::GetSides()const
{
	auto side1 = hypot(m_Vertex1.x - m_Vertex2.x, m_Vertex1.y - m_Vertex2.y);
	auto side2 = hypot(m_Vertex1.x - m_Vertex3.x, m_Vertex1.y - m_Vertex3.y);
	auto side3 = hypot(m_Vertex3.x - m_Vertex2.x, m_Vertex3.y - m_Vertex2.y);
	return make_tuple(side1, side2, side3);
}

double CTriangle::GetPerimeter()const
{
	double side1;
	double side2;
	double side3;
	tie(side1, side2, side3) = GetSides();
	return side1 + side2 + side3;
}


double CTriangle::GetArea()const
{
	double side1;
	double side2;
	double side3;
	tie(side1, side2, side3) = GetSides();

	double perimeterHalf = CTriangle::GetPerimeter()*0.5;
	return sqrt(perimeterHalf*(perimeterHalf - side1)*(perimeterHalf - side2)*(perimeterHalf - side3));
}


SPoint CTriangle::GetVertex1() const
{
	return m_Vertex1;
}

SPoint CTriangle::GetVertex2() const
{
	return m_Vertex2;
}

SPoint CTriangle::GetVertex3() const
{
	return m_Vertex3;
}