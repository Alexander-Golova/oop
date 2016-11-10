#include "stdafx.h"
#include "Shapes.h"


CTriangle::CTriangle(SPoint Vertex1, Vertex2, Vertex3)
	: m_Vertex1(Vertex1),
	  m_Vertex2(Vertex2),
	  m_Vertex3(Vertex3)
{
}

double CTriangle::GetPerimetr()
{
	double side_1 = sqrt((m_Vertex1.x - m_Vertex2.x)*(m_Vertex1.x - m_Vertex2.x) + 
		                 (m_Vertex1.y - m_Vertex2.y)*(m_Vertex1.y - m_Vertex2.y));
	double side_2 = sqrt((m_Vertex1.x - m_Vertex3.x)*(m_Vertex1.x - m_Vertex3.x) +
		                 (m_Vertex1.y - m_Vertex3.y)*(m_Vertex1.y - m_Vertex3.y));
	double side_3 = sqrt((m_Vertex2.x - m_Vertex3.x)*(m_Vertex2.x - m_Vertex3.x) +
		                 (m_Vertex2.y - m_Vertex3.y)*(m_Vertex2.y - m_Vertex3.y));

	return side_1 + side_2 + side_3;
}



double CTriangle::GetArea()
{
	double semiperimeter = 0.5 * CTriangle::GetPerimetr();
	double area = semiperimeter;
}
