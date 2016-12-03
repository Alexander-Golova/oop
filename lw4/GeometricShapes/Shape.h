#pragma once
#include "IShape.h"

struct SPoint
{
public:
	double x;
	double y;
};

class CShape
	:public IShape
{
public:
	CShape() = default;
	virtual ~CShape() = default;

	std::string GetOutlineColor() const override;

protected:
	std::string m_outlineColor;
};
