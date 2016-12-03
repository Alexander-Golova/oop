#pragma once
#include "ISolidShape.h"
#include "Shape.h"

class CSolidShape
	:public ISolidShape
	, public CShape
{
public:
	CSolidShape() = default;
	virtual ~CSolidShape() = default;

	std::string GetFillColor() const override;
	std::string GetOutlineColor() const override;

protected:
	std::string m_fillColor;
};
