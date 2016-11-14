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
	double GetArea() const override;

	SPoint GetVertex1() const;
	SPoint GetVertex2() const;
	SPoint GetVertex3() const;

private:
	std::tuple<double, double, double> GetSides() const;
	SPoint m_Vertex1;
	SPoint m_Vertex2;
	SPoint m_Vertex3;
};
