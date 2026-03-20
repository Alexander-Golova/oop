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
