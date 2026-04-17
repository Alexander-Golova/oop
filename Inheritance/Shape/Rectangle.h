#pragma once
#include "AdditionalFunction.h"
#include "ISolidShape.h"
#include "Point.h"

class CRectangle final
	: public ISolidShape
{
public:
	CRectangle(CPoint const& vertex1, CPoint const& vertex2,
		std::string const& outlineColor, std::string const& fillColor);

	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;

	// std::string ToString() const override;

	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;

private:
	std::tuple<double, double> GetSides() const;
	CPoint m_vertex1;
	CPoint m_vertex2;
	
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};
