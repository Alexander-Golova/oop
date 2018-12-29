#pragma once

#include "IShape.h"

class ISolidShape
	:virtual public IShape
{
public:
	ISolidShape() = default;
	virtual ~ISolidShape() = default;

	virtual void SetFillColor(std::string & color) = 0;
	virtual std::string GetFillColor() const = 0;
};
