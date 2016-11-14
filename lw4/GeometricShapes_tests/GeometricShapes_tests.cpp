#include "stdafx.h"

#include "../GeometricShapes/Shapes.h"

using namespace std;

struct TriangleFixture_
{
	const SPoint Vertex1 = { 0, 0 };
	const SPoint Vertex2 = { 4, 0 };
	const SPoint Vertex3 = { 0, 3 };
	const CTriangle triangle;
	TriangleFixture_()
		: triangle(Vertex1, Vertex2, Vertex3)
	{}
};

// у треугольника
BOOST_FIXTURE_TEST_SUITE(Triangle, TriangleFixture_)
	// первая вершина треугольник имеет координаты
	BOOST_AUTO_TEST_CASE(first_vertex_of_triangle_has_a_position)
	{
	BOOST_CHECK_EQUAL(triangle.GetVertex1().x, 0);
	BOOST_CHECK_EQUAL(triangle.GetVertex1().y, 0);
	}
	// впервая вершина треугольник имеет координаты
	BOOST_AUTO_TEST_CASE(second_vertex_of_triangle_has_a_position)
	{
		BOOST_CHECK_EQUAL(triangle.GetVertex2().x, 4);
		BOOST_CHECK_EQUAL(triangle.GetVertex2().y, 0);
	}
	// третья вершина треугольник имеет координаты
	BOOST_AUTO_TEST_CASE(third_vertex_of_triangle_has_a_position)
	{
		BOOST_CHECK_EQUAL(triangle.GetVertex2().x, 4);
		BOOST_CHECK_EQUAL(triangle.GetVertex2().y, 0);
	}
	// можно найти периметр
	BOOST_AUTO_TEST_CASE(can_find_perimeter)
	{
		BOOST_CHECK_EQUAL(static_cast<int>(triangle.GetPerimeter()), 12);
	}
	// можно найти площадь
	BOOST_AUTO_TEST_CASE(can_find_area)
	{
		BOOST_CHECK_EQUAL(static_cast<int>(triangle.GetArea()), 6);
	}

	
BOOST_AUTO_TEST_SUITE_END()
