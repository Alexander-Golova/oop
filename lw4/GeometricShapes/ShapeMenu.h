#pragma once

#include "IShape.h"
#include "Shapes.h"
#include <memory>
#include <boost/algorithm/string.hpp>
#include <vector>

class CShapeMenu
{
public:
	CShapeMenu(const std::string & shape);
	~CShapeMenu() = default;

	void ReadShapes(std::string shape);

private:
	bool CheckArgumentsTriangle(const std::vector<std::string> & shapes);
	void AddTriangle(const std::vector<std::string> & shapes);


	std::vector<std::shared_ptr<IShape>> m_shapesList;
};
