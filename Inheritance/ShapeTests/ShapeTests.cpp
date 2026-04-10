#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <../catch/catch.hpp>


#include "../Shape/IShape.h"
#include "../Shape/LineSegment.h"
#include "../Shape/Point.h"
#include "../Shape/AdditionalFunction.h"


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
