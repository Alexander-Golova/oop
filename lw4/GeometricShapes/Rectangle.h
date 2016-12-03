#pragma once

#include "SolidShape.h"

class CRectangle final
	: public CSolidShape
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
