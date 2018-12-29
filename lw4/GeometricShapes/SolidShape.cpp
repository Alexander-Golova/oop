#include "stdafx.h"
#include "SolidShape.h"

using namespace std;

CSolidShape::CSolidShape(const string & type, const string & outlineColor, const string & fillColor)
	: m_type(type)
	, m_fillColor(fillColor)
{
	SetOutlineColor(outlineColor);
}

void CSolidShape::SetFillColor(string & color)
{
	m_fillColor = color;
}

string CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

void CSolidShape::SetOutlineColor(const std::string & color)
{
	CShape::SetOutlineColor(color);
}

string CSolidShape::GetOutlineColor() const
{
	return CShape::GetOutlineColor();
}

string CSolidShape::ToString() const
{
	ostringstream strm;
	strm << fixed << setprecision(2);
	strm << m_type << ":" << endl
		<< "\tarea = " << GetArea() << endl
		<< "\tperimeter = " << GetPerimeter() << endl
		<< "\toutline color = #" << GetOutlineColor() << endl
		<< "\tfill color = #" << GetFillColor() << endl;
	AppendProperties(strm);
	return strm.str();
}
