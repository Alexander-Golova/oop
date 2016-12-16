#pragma once

#include <memory>
#include <vector>

#include "Shape.h"
#include "SolidShape.h"
#include "Circle.h"
#include "LineSegment.h"
#include "Rectangle.h"
#include "Triangle.h"

class CShapeMenu
{
public:
	CShapeMenu() = default;
	~CShapeMenu() = default;

	void ReadShape(std::string shape);
	void PrintShapeMinPerimeter();
	void PrintShapeMaxAreaShape();
	void PrintInfo() const;

private:
	void CheckTriangleArguments(const std::vector<std::string> & parametersList);
	void CheckRectangleArguments(const std::vector<std::string> & parametersList);
	void CheckCircleArguments(const std::vector<std::string> & parametersList);
	void CheckLineSegmentArguments(const std::vector<std::string> & parametersList);

	void AddTriangle(const std::vector<std::string> & parametersList);	
	void AddRectangle(const std::vector<std::string> & parametersList);
	void AddCircle(const std::vector<std::string> & parametersList);
	void AddLineSegment(const std::vector<std::string> & parametersList);

	std::vector<std::shared_ptr<IShape>> m_shapesList;
};
