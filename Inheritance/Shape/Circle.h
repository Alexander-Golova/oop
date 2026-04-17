#pragma once
#include "AdditionalFunction.h"
#include "ISolidShape.h"
#include "Point.h"
#include <numbers>

class CCircle final
	: public ISolidShape
{
public:
	CCircle(CPoint const& centre, double const& radius,
		std::string const& outlineColor, std::string const& fillColor);

	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetCentre() const;
	double GetRadius() const;

	// std::string ToString() const override;

	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;

private:	
	CPoint m_centre;
	double m_radius;

	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};
