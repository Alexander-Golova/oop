#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch/catch.hpp>

#include "../TV/TVSet.h"

// Телевизор изначально выключен
TEST_CASE("is turned off by default")
{
	CTVSet tv;
	CHECK(!tv.IsTurnedOn());
}
