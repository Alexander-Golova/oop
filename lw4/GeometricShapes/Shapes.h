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
	CTriangle::CTriangle(SPoint const & Vertex1, SPoint const & Vertex2, SPoint const & Vertex3, std::string const & outlineColor, std::string const & fillColor);
	
	double GetArea() const override;
	double GetPerimeter() const override;
	
	std::string ToString() const override;	
	std::string GetOutlineColor() const override;
	std::string GetFillColor() const override;

	SPoint GetVertex1() const;
	SPoint GetVertex2() const;
	SPoint GetVertex3() const;

private:
	std::tuple<double, double, double> GetSides() const;
	SPoint m_Vertex1;
	SPoint m_Vertex2;
	SPoint m_Vertex3;
	std::string m_outlineColor;
	std::string m_fillColor;
};
