#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch/catch.hpp>

#include "../ComplexNumbers/Complex.h"

TEST_CASE("CComplex Arithmetic Operators", "[complex][arithmetic]")
{
	CComplex a(3.0, 4.0);
	CComplex b(1.0, -2.0);

	SECTION("Addition Operator (+)")
	{
		CComplex res = a + b;	
		CHECK(res.Re() == Approx(4.0));
		CHECK(res.Im() == Approx(2.0));
	}
	SECTION("Subtraction Operator (-)")
	{
		CComplex res = a - b;
		CHECK(res.Re() == Approx(2.0));
		CHECK(res.Im() == Approx(6.0));
	}
	SECTION("Multiplication Operator (*)")
	{
		CComplex res = a * b;
		CHECK(res.Re() == Approx(11.0));
		CHECK(res.Im() == Approx(-2.0));
	}
	SECTION("Division Operator (/)")
	{
		CComplex res = a / b;
		CHECK(res.Re() == Approx(-1.0));
		CHECK(res.Im() == Approx(2.0));
	}	
}

TEST_CASE("CComplex Compound Assignment", "[complex][assignment]")
{
	CComplex a(2.0, 3.0);
	CComplex b(3.0, 2.0);

	SECTION("Plus Equals (+=)")
	{
		a += b;
		CHECK(a.Re() == Approx(5.0));
		CHECK(a.Im() == Approx(5.0));
	}
	SECTION("Minus Equals (-=)")
	{
		a -= b;
		CHECK(a.Re() == Approx(-1.0));
		CHECK(a.Im() == Approx(1.0));
	}
	SECTION("Multiply Equals (*=)")
	{
		a *= b;
		CHECK(a.Re() == Approx(0.0));
		CHECK(a.Im() == Approx(13.0));
	}
}

TEST_CASE("CComplex Unary Operators", "[complex][unary]")
{
	SECTION("Unary Minus (-)") {
		CComplex a(3.0, -4.0);
		CComplex res = -a;
		CHECK(res.Re() == Approx(-3.0));
		CHECK(res.Im() == Approx(4.0));
	}
	SECTION("Unary Plus (+)")
	{
		CComplex a(3.0, -4.0);
		CComplex res = a;
		CHECK(res.Re() == Approx(3.0));
		CHECK(res.Im() == Approx(-4.0));
	}
}
