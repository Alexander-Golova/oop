#include "stdafx.h"

#include "../GeometricShapes/Shapes.h"

using namespace std;

struct TriangleFixture_
{
	const SPoint Vertex1 = { 0, 0 };
	const SPoint Vertex2 = { 4, 0 };
	const SPoint Vertex3 = { 0, 3 };
	const string outlineColor = "ff0000";
	const string fillColor = "00ff00";

	const CTriangle triangle;
	TriangleFixture_()
		: triangle(Vertex1, Vertex2, Vertex3, outlineColor, fillColor)
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
	// имеет цвет границы
	BOOST_AUTO_TEST_CASE(triangle_has_a_line_color)
	{
		BOOST_CHECK_EQUAL(triangle.GetOutlineColor(), "ff0000");
	}
	// имеет цвет заливки
	BOOST_AUTO_TEST_CASE(triangle_has_a_fill_color)
	{
		BOOST_CHECK_EQUAL(triangle.GetFillColor(), "00ff00");
	}
	// имеет строковое представление
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		auto str = "Triangle: Vertex1(0.00, 0.00); Vertex2(4.00, 0.00); Vertex3(0.00, 3.00); P = 12.00; S = 6.00.";
		BOOST_CHECK_EQUAL(triangle.ToString(), str);
	}
	
BOOST_AUTO_TEST_SUITE_END()

struct RectangleFixture_
{
	const SPoint m_LeftTop = { 0, 6 };
	const SPoint m_RightBottom = { 5, 0 };
	const string outlineColor = "ff0000";
	const string fillColor = "00ff00";

	const CRectangle rectangle;
	RectangleFixture_()
		: rectangle(m_LeftTop, m_RightBottom, outlineColor, fillColor)
	{}
};

// у прямоугольника
BOOST_FIXTURE_TEST_SUITE(Rectangle, RectangleFixture_)

	// левая верхняя вершина имеет координаты
	BOOST_AUTO_TEST_CASE(left_top_vertex_has_a_position)
	{
		BOOST_CHECK_EQUAL(rectangle.GetLeftTop().x, 0);
		BOOST_CHECK_EQUAL(rectangle.GetLeftTop().y, 6);
	}
	// правая нижняя вершина имеет координаты
	BOOST_AUTO_TEST_CASE(right_bottom_left_top_vertex_has_a_position)
	{
		BOOST_CHECK_EQUAL(rectangle.GetRightBottom().x, 5);
		BOOST_CHECK_EQUAL(rectangle.GetRightBottom().y, 0);
	}
	// есть ширина
	BOOST_AUTO_TEST_CASE(has_a_width)
	{
		BOOST_CHECK_EQUAL(rectangle.GetWidth(), 6);
	}
	// есть длина
	BOOST_AUTO_TEST_CASE(has_a_height)
	{
		BOOST_CHECK_EQUAL(rectangle.GetHeight(), 5);
	}
	// можно найти периметр
	BOOST_AUTO_TEST_CASE(can_find_perimeter)
	{
		BOOST_CHECK_EQUAL(static_cast<int>(rectangle.GetPerimeter()), 22);
	}

BOOST_AUTO_TEST_SUITE_END()
