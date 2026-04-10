#include "Triangle.h"

CTriangle::CTriangle(CPoint const& vertex1, CPoint const& vertex2, CPoint const& vertex3,
	std::string const& outlineColor, std::string const& fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColor(FromStringToUint32(outlineColor))
	, m_fillColor(FromStringToUint32(fillColor))
{}

std::tuple<double, double, double> CTriangle::GetSides() const
{
	double side1 = sqrt(pow(m_vertex1.x - m_vertex2.x, 2) + pow(m_vertex1.y - m_vertex2.y, 2));
	double side2 = sqrt(pow(m_vertex1.x - m_vertex3.x, 2) + pow(m_vertex1.y - m_vertex3.y, 2));
	double side3 = sqrt(pow(m_vertex2.x - m_vertex3.x, 2) + pow(m_vertex2.y - m_vertex3.y, 2));
	return std::make_tuple(side1, side2, side3);
}

double CTriangle::GetPerimeter() const
{
	double side1;
	double side2;
	double side3;
	std::tie(side1, side2, side3) = GetSides();
	return side1 + side2 + side3;
}

double CTriangle::GetArea() const
{
	double side1;
	double side2;
	double side3;
	std::tie(side1, side2, side3) = GetSides();
	double p = 0.5 * GetPerimeter();
	return sqrt(p * (p - side1) * (p - side2) * (p - side3));
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;	
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}
