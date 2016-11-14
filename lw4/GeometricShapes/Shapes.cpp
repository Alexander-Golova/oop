#include "stdafx.h"
#include "Shapes.h"


CTriangle::CTriangle(SPoint const & Vertex1, SPoint const & Vertex2, SPoint const & Vertex3)
	: m_Vertex1(Vertex1)
	, m_Vertex2(Vertex2)
	, m_Vertex3(Vertex3)
{
}

double CTriangle::GetPerimeter()const
{
	auto side0 = std::hypot(m_Vertex1.x - m_Vertex2.x, m_Vertex1.y - m_Vertex2.y);
	double side1 = sqrt((m_Vertex1.x - m_Vertex2.x)*(m_Vertex1.x - m_Vertex2.x) + 
		                 (m_Vertex1.y - m_Vertex2.y)*(m_Vertex1.y - m_Vertex2.y));
	double side2 = sqrt((m_Vertex1.x - m_Vertex3.x)*(m_Vertex1.x - m_Vertex3.x) +
		                 (m_Vertex1.y - m_Vertex3.y)*(m_Vertex1.y - m_Vertex3.y));
	double side3 = sqrt((m_Vertex2.x - m_Vertex3.x)*(m_Vertex2.x - m_Vertex3.x) +
		                 (m_Vertex2.y - m_Vertex3.y)*(m_Vertex2.y - m_Vertex3.y));

	return side1 + side2 + side3;
}


/*
double CTriangle::GetArea()
{
	double semiperimeter = 0.5 * CTriangle::GetPerimetr();
	double area = semiperimeter;
}
*/
