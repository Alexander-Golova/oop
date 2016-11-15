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
	CTriangle(SPoint const & Vertex1, SPoint const & Vertex2, SPoint const & Vertex3,
	          std::string const & outlineColor, std::string const & fillColor);
	
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

class CRectangle final
	: public ISolidShape
{
public:
	CRectangle(SPoint const & LeftTop, SPoint const & RightBottom,
		        std::string const & outlineColor, std::string const & fillColor);
	double GetArea() const { return 0.0; };
	double GetPerimeter() const override;
	std::string ToString() const { return "x"; };
	std::string GetOutlineColor() const { return "x"; };

	std::string GetFillColor() const { return "x"; };

	SPoint GetLeftTop() const;
	SPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	SPoint m_LeftTop;
	SPoint m_RightBottom;
	std::string m_outlineColor;
	std::string m_fillColor;
};
