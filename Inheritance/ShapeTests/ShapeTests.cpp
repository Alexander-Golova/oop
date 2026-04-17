#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <../catch/catch.hpp>

#include "../Shape/IShape.h"
#include "../Shape/LineSegment.h"
#include "../Shape/Point.h"
#include "../Shape/AdditionalFunction.h"
#include "../Shape/Rectangle.h"
#include "../Shape/Triangle.h"
#include "../Shape/Circle.h"


// отрезок
TEST_CASE("segment")
{
	CLineSegment line({0.0, 0.0}, { 3.0, 4.0 }, "ff0000");

	// отрезок имеет координаты
	SECTION("segment has coordinates")
	{
		CHECK(line.GetStartPoint().x == 0);
		CHECK(line.GetStartPoint().y == 0);
		CHECK(line.GetEndPoint().x == 3);
		CHECK(line.GetEndPoint().y == 4);
	}
	// у отрезка нулевая площадь
	SECTION("segment has zero area")
	{
		CHECK(line.GetArea() == 0);
	}
	// у отрезка есть длина
	SECTION("segment has a length")
	{
		CHECK(line.GetPerimeter() == Approx(5.0));
	}
	// у отрезка есть цвет
	SECTION("segment has a color")
	{
		CHECK(line.GetOutlineColor() == FromStringToUint32("ff0000"));
	}
	// отрезок имеет строковое представление
//	SECTION("segment has a string representation")
//	{
//		CHECK(line.ToString() == R"(LineSegment:
//	startPoint(0.00, 0.00)
//	endPoint(3.00, 4.00)
//	P = 5.00
//	Border Color = 16711680
//)");
//	}
}

// треугольник
TEST_CASE("triangle")
{
	CTriangle triangle({ 7, 8 }, { -4, 5 }, { 1, -4 }, "ffffff", "ffff00");

	// треугольник имеет координаты
	SECTION("triangle has coordinates")
	{
		CHECK(triangle.GetVertex1().x == 7);
		CHECK(triangle.GetVertex1().y == 8);
		CHECK(triangle.GetVertex2().x == -4);
		CHECK(triangle.GetVertex2().y == 5);
		CHECK(triangle.GetVertex3().x == 1);
		CHECK(triangle.GetVertex3().y == -4);
	}
	// у треугольника можно найти площадь
	SECTION("triangle has area")
	{
		CHECK(static_cast<int>(triangle.GetArea()) == 57);
	}
	// у треугольника можно найти периметр
	SECTION("triangle has perimeter")
	{
		CHECK(static_cast<int>(triangle.GetPerimeter()) == 35);
	}
	// у треугольника есть цвет границы
	SECTION("triangle has a line color")
	{
		CHECK(triangle.GetOutlineColor() == FromStringToUint32("ffffff"));
	}
	// у треугольника есть заливка
	SECTION("triangle has a fill color")
	{
		CHECK(triangle.GetFillColor() == FromStringToUint32("ffff00"));
	}
	// треугольник имеет строковое представление
//	SECTION("triangle has a string representation")
//	{
//		CHECK(triangle.ToString() == R"(Triangle:
//	area = 57.00
//	perimeter = 35.11
//	outline color = 16777215
//	fill color = 16776960
//	Vertex1 = (7.00, 8.00)
//	Vertex2 = (-4.00, 5.00)
//	Vertex3 = (1.00, -4.00)
//)");
//	}
}

// прямоугольник
TEST_CASE("rectangle")
{
	CRectangle rectangle({ 1, 7 }, { 3, 1 }, "ffffff", "ffff00");

	// прямоугольник имеет координаты
	SECTION("rectangle has coordinates")
	{
		CHECK(rectangle.GetVertex1().x == 1);
		CHECK(rectangle.GetVertex1().y == 7);
		CHECK(rectangle.GetVertex2().x == 3);
		CHECK(rectangle.GetVertex2().y == 1);
	}
	// у прямоугольника можно найти площадь
	SECTION("rectangle has area")
	{
		CHECK(static_cast<int>(rectangle.GetArea()) == 12);
	}
	// у прямоугольника можно найти периметр
	SECTION("triangle has perimeter")
	{
		CHECK(static_cast<int>(rectangle.GetPerimeter()) == 16);
	}
	// у прямоугольника есть цвет границы
	SECTION("rectangle has a line color")
	{
		CHECK(rectangle.GetOutlineColor() == FromStringToUint32("ffffff"));
	}
	// у прямоугольника есть заливка
	SECTION("rectangle has a fill color")
	{
		CHECK(rectangle.GetFillColor() == FromStringToUint32("ffff00"));
	}
	// прямоугольника имеет строковое представление
	//	SECTION("triangle has a string representation")
	//	{
	//		CHECK(triangle.ToString() == R"(Triangle:
	//	area = 57.00
	//	perimeter = 35.11
	//	outline color = 16777215
	//	fill color = 16776960
	//	Vertex1 = (7.00, 8.00)
	//	Vertex2 = (-4.00, 5.00)
	//	Vertex3 = (1.00, -4.00)
	//)");
	//	}
}

// круг
TEST_CASE("circle")
{
	CCircle circle({ 3, 4 }, 5, "ffffff", "ffff00");

	// у круга есть центр и радиус
	SECTION("circle has centre and radius")
	{
		CHECK(circle.GetCentre().x == 3);
		CHECK(circle.GetCentre().y == 4);
		CHECK(circle.GetRadius() == 5);
	}
	// у круга можно найти площадь
	SECTION("circle has area")
	{
		CHECK(circle.GetArea() == Approx(std::numbers::pi * 25));
	}
	// у круга можно найти периметр
	SECTION("circle has perimeter")
	{
		CHECK(circle.GetPerimeter() == Approx(std::numbers::pi * 10));
	}
	// у круга есть цвет границы
	SECTION("circle has a line color")
	{
		CHECK(circle.GetOutlineColor() == FromStringToUint32("ffffff"));
	}
	// у круга есть заливка
	SECTION("circle has a fill color")
	{
		CHECK(circle.GetFillColor() == FromStringToUint32("ffff00"));
	}
	// прямоугольника имеет строковое представление
	//	SECTION("triangle has a string representation")
	//	{
	//		CHECK(triangle.ToString() == R"(Triangle:
	//	area = 57.00
	//	perimeter = 35.11
	//	outline color = 16777215
	//	fill color = 16776960
	//	Vertex1 = (7.00, 8.00)
	//	Vertex2 = (-4.00, 5.00)
	//	Vertex3 = (1.00, -4.00)
	//)");
	//	}
}