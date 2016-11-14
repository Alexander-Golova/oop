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


// треугольник
BOOST_FIXTURE_TEST_SUITE(Triangle, TriangleFixture_)
	// можно найти периметр
	BOOST_AUTO_TEST_CASE(can_find_perimeter)
	{
		//BOOST_CHECK_EQUAL(static_cast<int>(GetPerimetr()), 12);
	}
	// можно найти площадь


BOOST_AUTO_TEST_SUITE_END()
