#pragma once

#include <string>

class IShape
{
public:
	IShape() = default;
	virtual ~IShape() = default;

	/*virtual double GerArea() const = 0;*/
	virtual double GetPerimeter() const = 0;
	/*virtual std::string ToString() const = 0;
	virtual std::string GetOutlineColor() const = 0;*/

private:
};

class ISolidShape
	:public IShape
{
public:
	ISolidShape() = default;
	virtual ~ISolidShape() = default;

	/*virtual std::string GetFillColor() const = 0;*/

private:
};
