#include "stdafx.h"

#include "Rectangle.h"

using namespace std;

CRectangle::CRectangle(SPoint const & leftTop, SPoint const & rightBottom,
	string const & outlineColor, string const & fillColor)
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
		<< "S = " << GetArea() << "; "
		<< "Border Color = " << GetOutlineColor() << "; "
		<< "Fill color = " << GetFillColor() << ".";

	return strm.str();
}
