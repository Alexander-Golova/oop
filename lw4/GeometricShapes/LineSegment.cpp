#include "stdafx.h"

#include "LineSegment.h"

using namespace std;

CLineSegment::CLineSegment(SPoint const & startPoint, SPoint const & endPoint, std::string const & outlineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(outlineColor)
{
}

SPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

SPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	SPoint first = GetStartPoint();
	SPoint second = GetEndPoint();
	return hypot(first.x - second.x, first.y - second.y);
}

string CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

string CLineSegment::ToString() const
{
	ostringstream strm;
	strm << fixed << setprecision(2);

	strm << "LineSegment: "
		<< "startPoint(" << m_startPoint.x << ", " << m_startPoint.y << "); "
		<< "endPoint(" << m_endPoint.x << ", " << m_endPoint.y << "); "
		<< "P = " << GetPerimeter() << "; "
		<< "Border Color = " << GetOutlineColor() << ".";

	return strm.str();
}
