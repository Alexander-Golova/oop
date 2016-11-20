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

	void ReadShape(std::string shape);

private:
	void CheckArgumentsTriangle(const std::vector<std::string> & listParameters);
	void CheckArgumentsRectangle(const std::vector<std::string> & listParameters);
	void CheckArgumentsCircle(const std::vector<std::string> & listParameters);

	void AddTriangle(const std::vector<std::string> & listParameters);	
	void AddRectangle(const std::vector<std::string> & listParameters);
	void AddCircle(const std::vector<std::string> & listParameters);


	std::vector<std::shared_ptr<IShape>> m_shapesList;
};
