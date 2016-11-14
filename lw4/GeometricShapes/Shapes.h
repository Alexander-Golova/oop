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
	CTriangle(SPoint const & Vertex1, SPoint const & Vertex2, SPoint const & Vertex3);

	double GetPerimeter() const override;
	//double GetArea();

private:
	SPoint m_Vertex1;
	SPoint m_Vertex2;
	SPoint m_Vertex3;
};
