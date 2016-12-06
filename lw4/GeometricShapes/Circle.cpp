#include "stdafx.h"

#include "Circle.h"

using namespace std;

CCircle::CCircle(SPoint const & center, double const & radius, string const & outlineColor, string const & fillColor)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

SPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

double CCircle::GetArea() const
{
	return M_PI * pow(m_radius, 2);
}

double CCircle::GetPerimeter() const
{
	return M_PI * 2 * m_radius;
}

string CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

string CCircle::GetFillColor() const
{
	return m_fillColor;
}

string CCircle::ToString() const
{
	ostringstream strm;
	strm << fixed << setprecision(2);

	strm << "Circle: "
		<< "Center(" << m_center.x << ", " << m_center.y << "); "
		<< "Radius = " << m_radius << "; "
		<< "P = " << GetPerimeter() << "; "
		<< "S = " << GetArea() << "; "
		<< "Border Color = " << GetOutlineColor() << "; "
		<< "Fill color = " << GetFillColor() << ".";

	return strm.str();
}
