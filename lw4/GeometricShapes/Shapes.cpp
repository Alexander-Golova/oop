#include "stdafx.h"
#include "Shapes.h"

#define _USE_MATH_DEFINES
#include <math.h> 

using namespace std;

CTriangle::CTriangle(SPoint const & vertex1, SPoint const & vertex2, SPoint const & vertex3, string const & outlineColor, string const & fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

tuple<double, double, double> CTriangle::GetSides()const
{
	auto side1 = hypot(m_vertex1.x - m_vertex2.x, m_vertex1.y - m_vertex2.y);
	auto side2 = hypot(m_vertex1.x - m_vertex3.x, m_vertex1.y - m_vertex3.y);
	auto side3 = hypot(m_vertex3.x - m_vertex2.x, m_vertex3.y - m_vertex2.y);
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
	return m_vertex1;
}

SPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

SPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

string CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

string CTriangle::GetFillColor() const
{
	return m_fillColor;
}

string CTriangle::ToString() const
{
	ostringstream strm;
	strm << fixed << setprecision(2);

	strm << "Triangle: "
	     << "Vertex1(" << m_vertex1.x << ", " << m_vertex1.y << "); "
	     << "Vertex2(" << m_vertex2.x << ", " << m_vertex2.y << "); "
	     << "Vertex3(" << m_vertex3.x << ", " << m_vertex3.y << "); "
	     << "P = " << GetPerimeter() << "; "
	     << "S = " << GetArea() << ".";

	return strm.str();
}

CRectangle::CRectangle(SPoint const & leftTop, SPoint const & rightBottom, std::string const & outlineColor, std::string const & fillColor)
	: m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

SPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

SPoint CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}

double CRectangle::GetWidth() const
{
	return abs(m_leftTop.y - m_rightBottom.y);
}

double CRectangle::GetHeight() const
{
	return abs(m_leftTop.x - m_rightBottom.x);
}

double CRectangle::GetPerimeter() const
{
	return 2 * (GetWidth() + GetHeight());
}

double CRectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

string CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

string CRectangle::GetFillColor() const
{
	return m_fillColor;
}

string CRectangle::ToString() const
{
	ostringstream strm;
	strm << fixed << setprecision(2);

	strm << "Rectangle: "
		<< "LeftTop(" << m_leftTop.x << ", " << m_leftTop.y << "); "
		<< "RightBottom(" << m_rightBottom.x << ", " << m_rightBottom.y << "); "
		<< "P = " << GetPerimeter() << "; "
		<< "S = " << GetArea() << ".";

	return strm.str();
}


CCircle::CCircle(SPoint const & center, double const & radius, std::string const & outlineColor, std::string const & fillColor)
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
	return static_cast<double>(M_PI) * pow(m_radius, 2);
}

double CCircle::GetPerimeter() const
{
	return static_cast<double>(M_PI) * 2 * m_radius;
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
		<< "S = " << GetArea() << ".";

	return strm.str();
}

CLineSegment::CLineSegment(SPoint const & startPoint, SPoint const & endPoint, std::string const & outlineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(outlineColor)
{
}

