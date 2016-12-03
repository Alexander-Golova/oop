#pragma once

#include "SolidShape.h"

class CCircle final
	: public CSolidShape
{
public:
	CCircle(SPoint const & center, double const & radius, std::string const & outlineColor, std::string const & fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	std::string GetOutlineColor() const override;

	std::string GetFillColor() const override;

	SPoint GetCenter() const;
	double GetRadius() const;

private:
	SPoint m_center;
	double m_radius;
	std::string m_outlineColor;
	std::string m_fillColor;
};
