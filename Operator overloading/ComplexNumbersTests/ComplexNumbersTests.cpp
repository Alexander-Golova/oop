#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch/catch.hpp>

#include "../ComplexNumbers/Complex.h"

TEST_CASE("CComplex Arithmetic Operators", "[complex][arithmetic]")
{
	CComplex a(3.0, 4.0);
	CComplex b(1.0, -2.0);
	double c = 0.5;

	SECTION("Addition Operator (+)")
	{
		CComplex res = a + b;	
		CHECK(res.Re() == Approx(4.0));
		CHECK(res.Im() == Approx(2.0));
		res = a + c;
		CHECK(res.Re() == Approx(3.5));
		CHECK(res.Im() == Approx(4.0));
	}
	SECTION("Subtraction Operator (-)")
	{
		CComplex res = a - b;
		CHECK(res.Re() == Approx(2.0));
		CHECK(res.Im() == Approx(6.0));
		res = a - c;
		CHECK(res.Re() == Approx(2.5));
		CHECK(res.Im() == Approx(4.0));
	}
	SECTION("Multiplication Operator (*)")
	{
		CComplex res = a * b;
		CHECK(res.Re() == Approx(11.0));
		CHECK(res.Im() == Approx(-2.0));
		res = a * c;
		CHECK(res.Re() == Approx(1.5));
		CHECK(res.Im() == Approx(2.0));
	}
	SECTION("Division Operator (/)")
	{
		CComplex res = a / b;
		CHECK(res.Re() == Approx(-1.0));
		CHECK(res.Im() == Approx(2.0));
		res = a / c;
		CHECK(res.Re() == Approx(6.0));
		CHECK(res.Im() == Approx(8.0));
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
	SECTION("Divide Equals (/=)")
	{
		a /= b;
		CHECK(a.Re() == Approx(0.9230769231));
		CHECK(a.Im() == Approx(0.3846153846));
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

TEST_CASE("CComplex Comparison Operators", "[complex][comparison]")
{
	SECTION("Equality Operator (==)")
	{
		CComplex a(5.0, 5.0);
		CComplex b(5.0, 5.0);
		CComplex c(5.0, 5.0000001);

		CHECK(a == b);
		CHECK_FALSE(a == c);
		
		CComplex d(5.0, 0.0);
		double e = 5.0;
		CHECK(d == e);
	}
	SECTION("Inequality Operator (!=)")
	{
		CComplex a(0.0, 0.0);
		CComplex b(0.0, 1.0);
		double c = 5.0;

		CHECK(a != b);
		CHECK_FALSE(a != a);
		CHECK(a != c);
	}
}
