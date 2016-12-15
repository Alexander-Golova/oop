#pragma once

#include <string>

class IShape
{
public:
	IShape() = default;
	virtual ~IShape() = default;

	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual void SetOutlineColor(const std::string & color) = 0;
	virtual std::string GetOutlineColor() const = 0;

private:
};
