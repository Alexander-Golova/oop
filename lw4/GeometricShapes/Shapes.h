#pragma once

#include "IShape.h"

struct SPoint
{
public:
	double x;
	double y;
};

class CTriangle final
	:public ISolidShape
{
public:
	CTriangle(SPoint Vertex1, Vertex2, Vertex3);
	double GetPerimetr();
	double GetArea();
private:
	SPoint m_Vertex1, m_Vertex2, m_Vertex3;
};
