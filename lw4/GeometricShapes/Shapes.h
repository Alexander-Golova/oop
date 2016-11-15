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
	CTriangle(SPoint const & vertex1, SPoint const & vertex2, SPoint const & vertex3,
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
	SPoint m_vertex1;
	SPoint m_vertex2;
	SPoint m_vertex3;
	std::string m_outlineColor;
	std::string m_fillColor;
};

class CRectangle final
	: public ISolidShape
{
public:
	CRectangle(SPoint const & leftTop, SPoint const & rightBottom,
		        std::string const & outlineColor, std::string const & fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	std::string GetOutlineColor() const override;

	std::string GetFillColor() const override;

	SPoint GetLeftTop() const;
	SPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	SPoint m_leftTop;
	SPoint m_rightBottom;
	std::string m_outlineColor;
	std::string m_fillColor;
};


class CCircle final
	: public ISolidShape
{
public:
	CCircle(SPoint const & center, SPoint const & radius, std::string const & outlineColor, std::string const & fillColor);
	double GetArea() const { return 0.0; };//override;
	double GetPerimeter() const { return 0.0; };//override;
	std::string ToString() const { return "";  };//override;
	std::string GetOutlineColor() const { return ""; };//override;

	std::string GetFillColor() const { return ""; };//override;

	SPoint GetCenter() const {};
	SPoint GetRadius() const {};

private:
	SPoint m_center;
	SPoint m_radius;
	std::string m_outlineColor;
	std::string m_fillColor;
};
