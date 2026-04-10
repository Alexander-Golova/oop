#pragma once
#include "ISolidShape.h"
#include "Point.h"
#include "AdditionalFunction.h"

class CTriangle final
	: public ISolidShape
{
public:
	CTriangle(CPoint const& vertex1, CPoint const& vertex2, CPoint const& vertex3,
		std::string const& outlineColor, std::string const& fillColor);

	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

	//std::string ToString() const override;

	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;

private:
	std::tuple<double, double, double> GetSides() const;
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;

	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};
