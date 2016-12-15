#include "stdafx.h"

#include "Rectangle.h"

using namespace std;

CRectangle::CRectangle(SPoint const & leftTop, SPoint const & rightBottom,
	string const & outlineColor, string const & fillColor)
	: m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
	, CSolidShape("Rectangle", outlineColor, fillColor)
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

void CRectangle::AppendProperties(std::ostream & strm) const
{
	strm << fixed << setprecision(2);

	strm << "\tLeftTop(" << m_leftTop.x << ", " << m_leftTop.y << ")" << endl
	     << "\tRightBottom(" << m_rightBottom.x << ", " << m_rightBottom.y << ")" << endl;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (GetWidth() + GetHeight());
}

double CRectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}
