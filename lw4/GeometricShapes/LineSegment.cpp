#include "stdafx.h"

#include "LineSegment.h"

using namespace std;

CLineSegment::CLineSegment(SPoint const & startPoint, SPoint const & endPoint, string const & outlineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
{
	SetOutlineColor(outlineColor);
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

string CLineSegment::ToString() const
{
	ostringstream strm;
	strm << fixed << setprecision(2);

	strm << "LineSegment:" << endl
		<< "\tstartPoint(" << m_startPoint.x << ", " << m_startPoint.y << ")" << endl
		<< "\tendPoint(" << m_endPoint.x << ", " << m_endPoint.y << ")" << endl
		<< "\tP = " << GetPerimeter() << endl
		<< "\tBorder Color = " << GetOutlineColor() << endl;

	return strm.str();
}
