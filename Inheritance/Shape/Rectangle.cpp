#include "Rectangle.h"

CRectangle::CRectangle(CPoint const& vertex1, CPoint const& vertex2,
	std::string const& outlineColor, std::string const& fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_outlineColor(FromStringToUint32(outlineColor))
	, m_fillColor(FromStringToUint32(fillColor))
{
}

std::tuple<double, double> CRectangle::GetSides() const
{
	double side1 = abs(m_vertex1.x - m_vertex2.x);
	double side2 = abs(m_vertex1.y - m_vertex2.y);
	return std::make_tuple(side1, side2);
}

double CRectangle::GetPerimeter() const
{
	double side1;
	double side2;
	std::tie(side1, side2) = GetSides();
	return 2 * (side1 + side2);
}

double CRectangle::GetArea() const
{
	double side1;
	double side2;
	std::tie(side1, side2) = GetSides();
	return side1 * side2;	
}

CPoint CRectangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CRectangle::GetVertex2() const
{
	return m_vertex2;
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}
