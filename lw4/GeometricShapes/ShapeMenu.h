#pragma once

#include "Shape.h"
#include "SolidShape.h"
#include "Circle.h"
#include "LineSegment.h"
#include "Rectangle.h"
#include "Triangle.h"

#include <memory>
#include <boost/algorithm/string.hpp>
#include <vector>

class CShapeMenu
{
public:
	CShapeMenu() = default;
	~CShapeMenu() = default;

	void ReadShape(std::string shape);
	void PrintShapeMinPerimeter();
	void PrintShapeMaxAreaShape();

private:
	void CheckArgumentsTriangle(const std::vector<std::string> & listParameters);
	void CheckArgumentsRectangle(const std::vector<std::string> & listParameters);
	void CheckArgumentsCircle(const std::vector<std::string> & listParameters);
	void CheckArgumentsLineSegment(const std::vector<std::string> & listParameters);
	

	void AddTriangle(const std::vector<std::string> & listParameters);	
	void AddRectangle(const std::vector<std::string> & listParameters);
	void AddCircle(const std::vector<std::string> & listParameters);
	void AddLineSegment(const std::vector<std::string> & listParameters);
		
	std::vector<std::shared_ptr<CShape>> m_shapesList;
};
