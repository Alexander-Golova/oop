#include "Circle.h"


CCircle::CCircle(CPoint const& centre, double const& radius,
	std::string const& outlineColor, std::string const& fillColor)
	: m_centre(centre)
	, m_radius(radius)
	, m_outlineColor(FromStringToUint32(outlineColor))
	, m_fillColor(FromStringToUint32(fillColor))
{
}

double CCircle::GetPerimeter() const
{
	return 2 * std::numbers::pi * m_radius;
}

double CCircle::GetArea() const
{
	return std::numbers::pi * m_radius * m_radius;
}

CPoint CCircle::GetCentre() const
{
	return m_centre;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}
