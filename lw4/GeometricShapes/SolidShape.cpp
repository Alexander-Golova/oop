#include "stdafx.h"
#include "SolidShape.h"

using namespace std;

string CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

string CSolidShape::GetOutlineColor() const
{
	return CShape::GetOutlineColor();
}
