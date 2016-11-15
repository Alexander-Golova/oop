#include "stdafx.h"
#include "Shapes.h"

using namespace std;

CTriangle::CTriangle(SPoint const & Vertex1, SPoint const & Vertex2, SPoint const & Vertex3, string const & outlineColor, string const & fillColor)
	: m_Vertex1(Vertex1)
	, m_Vertex2(Vertex2)
	, m_Vertex3(Vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
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
	     << "Vertex1(" << m_Vertex1.x << ", " << m_Vertex1.y << "); "
	     << "Vertex2(" << m_Vertex2.x << ", " << m_Vertex2.y << "); "
	     << "Vertex3(" << m_Vertex3.x << ", " << m_Vertex3.y << "); "
	     << "P = " << GetPerimeter() << "; "
	     << "S = " << GetArea() << ".";

	return strm.str();
}

CRectangle::CRectangle(SPoint const & LeftTop, SPoint const & RightBottom, std::string const & outlineColor, std::string const & fillColor)
	: m_LeftTop(LeftTop)
	, m_RightBottom(RightBottom)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

SPoint CRectangle::GetLeftTop() const
{
	return m_LeftTop;
}

SPoint CRectangle::GetRightBottom() const
{
	return m_RightBottom;
}

double CRectangle::GetWidth() const
{
	return abs(m_LeftTop.y - m_RightBottom.y);
}

double CRectangle::GetHeight() const
{
	return abs(m_LeftTop.x - m_RightBottom.x);
}

double CRectangle::GetPerimeter() const
{
	return 2 * (GetWidth() + GetHeight());
}
