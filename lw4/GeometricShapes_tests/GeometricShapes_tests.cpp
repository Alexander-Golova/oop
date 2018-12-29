#include "stdafx.h"

#include "../GeometricShapes/IShape.h"
#include "../GeometricShapes/ISolidShape.h"
#include "../GeometricShapes/Shape.h"
#include "../GeometricShapes/SolidShape.h"
#include "../GeometricShapes/Circle.h"
#include "../GeometricShapes/LineSegment.h"
#include "../GeometricShapes/Rectangle.h"
#include "../GeometricShapes/Triangle.h"

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
		BOOST_CHECK_EQUAL(triangle.GetVertex3().x, 0);
		BOOST_CHECK_EQUAL(triangle.GetVertex3().y, 3);
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
	BOOST_AUTO_TEST_CASE(has_a_line_color)
	{
		BOOST_CHECK_EQUAL(triangle.GetOutlineColor(), "ff0000");
	}
	// имеет цвет заливки
	BOOST_AUTO_TEST_CASE(has_a_fill_color)
	{
		BOOST_CHECK_EQUAL(triangle.GetFillColor(), "00ff00");
	}
	// имеет строковое представление
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		auto str = "Triangle:\n"
		           "\tarea = 6.00\n"
		           "\tperimeter = 12.00\n"
		           "\toutline color = #ff0000\n"
		           "\tfill color = #00ff00\n"
		           "\tVertex1 = (0.00, 0.00)\n"
		           "\tVertex2 = (4.00, 0.00)\n"
		           "\tVertex3 = (0.00, 3.00)\n";
		BOOST_CHECK_EQUAL(triangle.ToString(), str);
	}
	
BOOST_AUTO_TEST_SUITE_END()

struct RectangleFixture_
{
	const SPoint leftTop = { 0, 6 };
	const SPoint rightBottom = { 5, 0 };
	const string outlineColor = "ff0000";
	const string fillColor = "00ff00";

	const CRectangle rectangle;
	RectangleFixture_()
		: rectangle(leftTop, rightBottom, outlineColor, fillColor)
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
	// можно найти площадь
	BOOST_AUTO_TEST_CASE(can_find_area)
	{
		BOOST_CHECK_EQUAL(static_cast<int>(rectangle.GetArea()), 30);
	}
	// имеет цвет границы
	BOOST_AUTO_TEST_CASE(has_a_line_color)
	{
		BOOST_CHECK_EQUAL(rectangle.GetOutlineColor(), "ff0000");
	}
	// имеет цвет заливки
	BOOST_AUTO_TEST_CASE(has_a_fill_color)
	{
		BOOST_CHECK_EQUAL(rectangle.GetFillColor(), "00ff00");
	}
	// имеет строковое представление
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		auto str = "Rectangle:\n"
			"\tarea = 30.00\n"
			"\tperimeter = 22.00\n"
			"\toutline color = #ff0000\n"
			"\tfill color = #00ff00\n"
			"\tLeftTop(0.00, 6.00)\n"
			"\tRightBottom(5.00, 0.00)\n";
		BOOST_CHECK_EQUAL(rectangle.ToString(), str);
	}

BOOST_AUTO_TEST_SUITE_END()


struct CircleFixture_
{
	const SPoint center = { 0, 0 };
	const double radius = 10;
	const string outlineColor = "ff0000";
	const string fillColor = "00ff00";

	const CCircle сircle;
	CircleFixture_()
		: сircle(center, radius, outlineColor, fillColor)
	{}
};

// у круга
BOOST_FIXTURE_TEST_SUITE(Circle, CircleFixture_)
	// есть центр
	BOOST_AUTO_TEST_CASE(has_a_center)
	{
		BOOST_CHECK_EQUAL(сircle.GetCenter().x, 0);
		BOOST_CHECK_EQUAL(сircle.GetCenter().x, 0);
	}
	// есть радиус
	BOOST_AUTO_TEST_CASE(has_a_radius)
	{
		BOOST_CHECK_EQUAL(сircle.GetRadius(), 10);
	}
	// можно найти площадь
	BOOST_AUTO_TEST_CASE(can_find_area)
	{
		BOOST_CHECK_EQUAL(static_cast<int>(сircle.GetArea()), 314);
	}
	// можно найти периметр
	BOOST_AUTO_TEST_CASE(can_find_perimeter)
	{
		BOOST_CHECK_EQUAL(static_cast<int>(сircle.GetPerimeter()), 62);
	}
	// имеет цвет границы
	BOOST_AUTO_TEST_CASE(has_a_line_color)
	{
		BOOST_CHECK_EQUAL(сircle.GetOutlineColor(), "ff0000");
	}
	// имеет цвет заливки
	BOOST_AUTO_TEST_CASE(has_a_fill_color)
	{
		BOOST_CHECK_EQUAL(сircle.GetFillColor(), "00ff00");
	}
	// имеет строковое представление
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		auto str = "Circle:\n"
			"\tarea = 314.16\n"
			"\tperimeter = 62.83\n"
			"\toutline color = #ff0000\n"
			"\tfill color = #00ff00\n"
			"\tCenter(0.00, 0.00)\n"
			"\tRadius = 10.00\n";
		BOOST_CHECK_EQUAL(сircle.ToString(), str);
	}

BOOST_AUTO_TEST_SUITE_END()

struct LineSegmentFixture_
{
	const SPoint startPoint = { 0, 0 };
	const SPoint endPoint = { 3, 4 };
	const string outlineColor = "ff0000";

	const CLineSegment line;
	LineSegmentFixture_()
		: line(startPoint, endPoint, outlineColor)
	{}
};

// у отрезка
BOOST_FIXTURE_TEST_SUITE(LineSegment, LineSegmentFixture_)

	// есть начало
	BOOST_AUTO_TEST_CASE(has_a_start_point)
	{
		BOOST_CHECK_EQUAL(line.GetStartPoint().x, 0);
		BOOST_CHECK_EQUAL(line.GetStartPoint().y, 0);
	}
	// есть конец
	BOOST_AUTO_TEST_CASE(has_a_end_point)
	{
		BOOST_CHECK_EQUAL(line.GetEndPoint().x, 3);
		BOOST_CHECK_EQUAL(line.GetEndPoint().y, 4);
	}
	// нулевая площадь
	BOOST_AUTO_TEST_CASE(line_has_zero_area)
	{
		BOOST_CHECK_EQUAL(line.GetArea(), 0);
	}
	// есть периметр, равный длине отрезка
	BOOST_AUTO_TEST_CASE(perimeter_is_equal_length_of_segment)
	{
		SPoint first = line.GetStartPoint();
		SPoint second = line.GetEndPoint();
		BOOST_CHECK_EQUAL(line.GetPerimeter(), hypot(first.x - second.x, first.y - second.y));
	}
	// имеет цвет границы
	BOOST_AUTO_TEST_CASE(has_a_line_color)
	{
		BOOST_CHECK_EQUAL(line.GetOutlineColor(), "ff0000");
	}
	// имеет строковое представление
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		auto str = "LineSegment:\n"
		           "\tstartPoint(0.00, 0.00)\n"
		           "\tendPoint(3.00, 4.00)\n"
		           "\tP = 5.00\n"
		           "\tBorder Color = ff0000\n";
		BOOST_CHECK_EQUAL(line.ToString(), str);
	}

BOOST_AUTO_TEST_SUITE_END()
