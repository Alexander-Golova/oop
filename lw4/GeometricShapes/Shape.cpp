#include "stdafx.h"
#include "Shape.h"

using namespace std;

void CShape::SetOutlineColor(const std::string & color)
{
	m_outlineColor = color;
}

string CShape::GetOutlineColor() const
{
	return m_outlineColor;
}
