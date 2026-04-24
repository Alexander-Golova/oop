#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch/catch.hpp>

#include "../RationalNumber/Rational.h"

TEST_CASE("RationalNumber Operators", "[rational][arithmetic]")
{
	CRational a(5, 12);
	CRational b(7, 18);
	
	SECTION("Addition Operator (+)")
	{
		CRational res = a + b;
		CHECK(res.GetNumerator() == 29);
		CHECK(res.GetDenominator() == 36);
		res = b + a;
		CHECK(res.GetNumerator() == 29);
		CHECK(res.GetDenominator() == 36);
	}
	SECTION("Subtraction Operator (-)")
	{
		CRational res = a - b;
		CHECK(res.GetNumerator() == 1);
		CHECK(res.GetDenominator() == 36);
		res = b - a;
		CHECK(res.GetNumerator() == -1);
		CHECK(res.GetDenominator() == 36);
	}
	CRational d(6, 25);
	CRational e(20, 9);
	SECTION("Multiplication Operator (*)")
	{
		CRational res = a * b;
		CHECK(res.GetNumerator() == 35);
		CHECK(res.GetDenominator() == 216);
		int c = 5;
		res = a * c;
		CHECK(res.GetNumerator() == 25);
		CHECK(res.GetDenominator() == 12);
		res = d * e;
		CHECK(res.GetNumerator() == 8);
		CHECK(res.GetDenominator() == 15);
		res = e * d;
		CHECK(res.GetNumerator() == 8);
		CHECK(res.GetDenominator() == 15);		
	}
	SECTION("Division Operator (/)")
	{
		CRational res = a / b;
		CHECK(res.GetNumerator() == 15);
		CHECK(res.GetDenominator() == 14);
		res = b / a;
		CHECK(res.GetNumerator() == 14);
		CHECK(res.GetDenominator() == 15);
	}
	SECTION("Operator unary minus (-)")
	{
		CRational res = -a;
		CHECK(res.GetNumerator() == -5);
		CHECK(res.GetDenominator() == 12);
	}
	SECTION("Operator unary minus (+)")
	{
		CRational res = a;
		CHECK(res.GetNumerator() == 5);
		CHECK(res.GetDenominator() == 12);
	}
	SECTION("Addition Operator (+=)")
	{
		CRational res(3, 4);
		res += a;
		CHECK(res.GetNumerator() == 7);
		CHECK(res.GetDenominator() == 6);
	}
	SECTION("Subtraction Operator (-=)")
	{
		CRational res(3, 4);
		res -= a;
		CHECK(res.GetNumerator() == 1);
		CHECK(res.GetDenominator() == 3);
	}
	SECTION("Multiplication Operator (*=)")
	{
		CRational res(3, 4);
		res *= a;
		CHECK(res.GetNumerator() == 5);
		CHECK(res.GetDenominator() == 16);
	}
	SECTION("Division Operator (/=)")
	{
		CRational res(3, 4);
		res /= a;
		CHECK(res.GetNumerator() == 9);
		CHECK(res.GetDenominator() == 5);
	}
	SECTION("Operator equality (==)")
	{
		CRational res(5, 12);
		CHECK(res == a);
		CHECK(!(res == b));
	}
}
