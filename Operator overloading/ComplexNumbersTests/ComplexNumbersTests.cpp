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

TEST_CASE("CComplex operator<< - Basic Output", "[complex][output]")
{
	std::stringstream ss;

	SECTION("Positive Real and Positive Imaginary")
	{
		CComplex c(3.5, 4.2);
		ss << c;
		CHECK(ss.str() == "3.5+4.2i");
	}

	SECTION("Positive Real and Negative Imaginary")
	{
		CComplex c(5.0, -2.5);
		ss << c;
		CHECK(ss.str() == "5.0-2.5i");
	}

	SECTION("Negative Real and Positive Imaginary")
	{
		CComplex c(-1.5, 3.7);
		ss << c;
		CHECK(ss.str() == "-1.5+3.7i");
	}

	SECTION("Negative Real and Negative Imaginary")
	{
		CComplex c(-2.3, -4.8);
		ss << c;
		CHECK(ss.str() == "-2.3-4.8i");
	}
}

TEST_CASE("CComplex operator>> - Valid Input (All Sign Combinations)", "[complex][input][valid]")
{
	CComplex c;

	SECTION("Positive Real + Positive Imaginary (3.5+4.2i)")
	{
		std::stringstream ss("3.5+4.2i");
		ss >> c;
		CHECK(!ss.fail());
		CHECK(c.Re() == Approx(3.5));
		CHECK(c.Im() == Approx(4.2));
	}
	SECTION("Positive Real + Negative Imaginary (5.0-2.5i)")
	{
		std::stringstream ss("5.0-2.5i");
		ss >> c;
		CHECK(!ss.fail());
		CHECK(c.Re() == Approx(5.0));
		CHECK(c.Im() == Approx(-2.5));
	}
	SECTION("Negative Real + Positive Imaginary (-1.5+3.7i)")
	{
		std::stringstream ss("-1.5+3.7i");
		ss >> c;
		CHECK(!ss.fail());
		CHECK(c.Re() == Approx(-1.5));
		CHECK(c.Im() == Approx(3.7));
	}
	SECTION("Negative Real + Negative Imaginary (-2.3-4.8i)")
	{
		std::stringstream ss("-2.3-4.8i");
		ss >> c;
		CHECK(!ss.fail());
		CHECK(c.Re() == Approx(-2.3));
		CHECK(c.Im() == Approx(-4.8));
	}

	SECTION("Uppercase I (1.0+2.0I)")
	{
		std::stringstream ss("1.0+2.0I");
		ss >> c;
		CHECK(!ss.fail());
		CHECK(c.Im() == Approx(2.0));
	}
}

TEST_CASE("CComplex operator>> - Zero Values", "[complex][input][zero]")
{
	CComplex c;

	SECTION("Zero Complex (0.0+0.0i)")
	{
		std::stringstream ss("0.0+0.0i");
		ss >> c;
		CHECK(!ss.fail());
		CHECK(c.Re() == Approx(0.0));
		CHECK(c.Im() == Approx(0.0));
	}

	SECTION("Zero Real Part (0.0+5.5i)")
	{
		std::stringstream ss("0.0+5.5i");
		ss >> c;
		CHECK(!ss.fail());
		CHECK(c.Re() == Approx(0.0));
		CHECK(c.Im() == Approx(5.5));
	}

	SECTION("Zero Imaginary Part (7.2+0.0i)")
	{
		std::stringstream ss("7.2+0.0i");
		ss >> c;
		CHECK(!ss.fail());
		CHECK(c.Re() == Approx(7.2));
		CHECK(c.Im() == Approx(0.0));
	}

	SECTION("Negative Zero Imaginary (1.0+-0.0i)")
	{
		std::stringstream ss("1.0+-0.0i");
		ss >> c;
		CHECK(!ss.fail());
		CHECK(c.Re() == Approx(1.0));
		CHECK(c.Im() == Approx(0.0));
	}
}

TEST_CASE("CComplex operator>> - Invalid Input (Error Handling)", "[complex][input][error]")
{
	CComplex c(99.0, 99.0);
	SECTION("Missing 'i' at End (3.5+4.2)")
	{
		std::stringstream ss("3.5+4.2");
		ss >> c;
		CHECK(ss.fail());
		CHECK(c.Re() == Approx(0.0));
		CHECK(c.Im() == Approx(0.0));
	}
	SECTION("Wrong Sign Character (3.5*4.2i)")
	{
		std::stringstream ss("3.5*4.2i");
		ss >> c;
		CHECK(ss.fail());
		CHECK(c.Re() == Approx(0.0));
		CHECK(c.Im() == Approx(0.0));
	}
	SECTION("Missing Imaginary Part (3.5+i)")
	{
		std::stringstream ss("3.5+i");
		ss >> c;
		CHECK(ss.fail());
		CHECK(c.Re() == Approx(0.0));
	}
	SECTION("Text Instead of Numbers (abc+defi)")
	{
		std::stringstream ss("abc+defi");
		ss >> c;
		CHECK(ss.fail());
		CHECK(c.Re() == Approx(0.0));
	}
	SECTION("Empty String")
	{
		std::stringstream ss("");
		ss >> c;
		CHECK(ss.fail());
		CHECK(c.Re() == Approx(0.0));
	}
	SECTION("Only Real Part (5.0)")
	{
		std::stringstream ss("5.0");
		ss >> c;
		CHECK(ss.fail());
		CHECK(c.Re() == Approx(0.0));
	}

	SECTION("Wrong Character Instead of 'i' (3.5+4.2x)")
	{
		std::stringstream ss("3.5+4.2x");
		ss >> c;
		CHECK(ss.fail());
		CHECK(c.Re() == Approx(0.0));
	}

}
