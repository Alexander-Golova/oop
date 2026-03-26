#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch/catch.hpp>

#include "../SolvingQuadraticEquation/Equation.h"

TEST_CASE("Solve - Two distinct real roots", "[quadratic]")
{
	auto result = Solve(1.0, -5.0, 6.0);
	CHECK(result.numRoots == 2);
	CHECK((result.roots[0] == Approx(2.0) || result.roots[0] == Approx(3.0)));
	CHECK((result.roots[1] == Approx(2.0) || result.roots[1] == Approx(3.0)));
}

TEST_CASE("Solve - One repeated root", "[quadratic]")
{
	auto result = Solve(1.0, -4.0, 4.0);
	CHECK(result.numRoots == 1);
	CHECK(result.roots[0] == Approx(2.0));
}

TEST_CASE("Solve - a = 0 throws invalid_argument", "[quadratic][error]")
{
	REQUIRE_THROWS_AS(Solve(0.0, 2.0, 3.0), std::invalid_argument);
}

TEST_CASE("Solve - Negative discriminant throws domain_error", "[quadratic][error]")
{
	REQUIRE_THROWS_AS(Solve(1.0, 0.0, 1.0), std::domain_error);
}

TEST_CASE("Solve - Large coefficients", "[quadratic]")
{
	auto result = Solve(1e6, -2e6, 1e6);
	CHECK(result.numRoots == 1);
	CHECK(result.roots[0] == Approx(1.0));
}

TEST_CASE("Solve - Small coefficients", "[quadratic]")
{
	auto result = Solve(1e-6, 2e-6, 1e-6);
	CHECK(result.numRoots == 1);
	CHECK(result.roots[0] == Approx(-1.0));
}

TEST_CASE("Solve - Roots order doesn't matter", "[quadratic]")
{
	auto result = Solve(1.0, 0.0, -1.0);
	REQUIRE(result.numRoots == 2);
	bool hasPlusOne = (result.roots[0] == Approx(1.0)) || (result.roots[1] == Approx(1.0));
	bool hasMinusOne = (result.roots[0] == Approx(-1.0)) || (result.roots[1] == Approx(-1.0));
	REQUIRE(hasPlusOne);
	REQUIRE(hasMinusOne);
}
