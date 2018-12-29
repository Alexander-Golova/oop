#include "stdafx.h"

#include "Circle.h"

using namespace std;

CCircle::CCircle(SPoint const & center, double const & radius, string const & outlineColor, string const & fillColor)
	: m_center(center)
	, m_radius(radius)
	, CSolidShape("Circle", outlineColor, fillColor)
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

void CCircle::AppendProperties(std::ostream & strm) const
{
	strm << fixed << setprecision(2);

	strm << "\tCenter(" << m_center.x << ", " << m_center.y << ")" << endl
	     << "\tRadius = " << m_radius << endl;
}

double CCircle::GetArea() const
{
	return M_PI * pow(m_radius, 2);
}

double CCircle::GetPerimeter() const
{
	return M_PI * 2 * m_radius;
}
