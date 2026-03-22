#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch/catch.hpp>

#include "../Bodies/Sphere.h"

TEST_CASE("CSphere GetRadius", "[sphere][radius]")
{
	SECTION("Radius returns correct value")
	{
		CSphere sphere(2.5, 7.3);
		CHECK(sphere.GetRadius() == Approx(7.3));
	}

	SECTION("Radius preserved after construction")
	{
		double radius = 10.5;
		CSphere sphere(1.0, radius);
		CHECK(sphere.GetRadius() == Approx(radius));
	}
}

TEST_CASE("CSphere GetVolume", "[sphere][volume]")
{
	SECTION("Volume formula: 4/3 * π * r³")
	{
		double radius = 3.0;
		CSphere sphere(1.0, radius);
		double expected = (4.0 / 3.0) * std::numbers::pi * std::pow(radius, 3);
		CHECK(sphere.GetVolume() == Approx(expected));
	}
	
	SECTION("Volume for radius = 0")
	{
		CSphere sphere(1.0, 0.0);
		CHECK(sphere.GetVolume() == Approx(0.0));
	}

	SECTION("Volume scales with cube of radius")
	{
		CSphere sphere1(1.0, 2.0);
		CSphere sphere2(1.0, 4.0);		
		CHECK(sphere2.GetVolume() == Approx(sphere1.GetVolume() * 8.0));
	}

	SECTION("Volume is independent of density")
	{
		CSphere sphere1(1.0, 5.0);
		CSphere sphere2(10.0, 5.0);
		CHECK(sphere1.GetVolume() == Approx(sphere2.GetVolume()));
	}
}

TEST_CASE("CBody GetDensity", "[body][density]")
{
	SECTION("Returns correct density value")
	{
		CSphere sphere(2.5, 5.0);
		CHECK(sphere.GetDensity() == Approx(2.5));
	}

	SECTION("Density is independent of radius")
	{
		CSphere sphere1(2.5, 1.0);
		CSphere sphere2(2.5, 10.0);
		CHECK(sphere1.GetDensity() == Approx(sphere2.GetDensity()));
	}
}


TEST_CASE("CSphere Polymorphism", "[sphere][polymorphism]")
{
	SECTION("Can be stored as CBody pointer")
	{
		std::unique_ptr<CBody> body = std::make_unique<CSphere>(1.0, 5.0);
		CHECK(body != nullptr);
	}

	SECTION("Virtual GetVolume() works through base pointer")
	{
		std::unique_ptr<CBody> body = std::make_unique<CSphere>(1.0, 3.0);
		double expected = (4.0 / 3.0) * std::numbers::pi * std::pow(3.0, 3);
		CHECK(body->GetVolume() == Approx(expected));
	}
}

TEST_CASE("CBody GetVolume (Polymorphic)", "[body][volume][polymorphism]")
{
	SECTION("Virtual GetVolume works through base pointer")
	{
		std::unique_ptr<CBody> body = std::make_unique<CSphere>(1.0, 3.0);
		double expected = (4.0 / 3.0) * std::numbers::pi * std::pow(3.0, 3);
		CHECK(body->GetVolume() == Approx(expected));
	}

	SECTION("Virtual GetVolume works through base reference")
	{
		CSphere sphere(1.0, 3.0);
		CBody& bodyRef = sphere;
		double expected = (4.0 / 3.0) * std::numbers::pi * std::pow(3.0, 3);
		CHECK(bodyRef.GetVolume() == Approx(expected));
	}

	SECTION("GetVolume returns 0 for zero radius")
	{
		CSphere sphere(1.0, 0.0);
		CHECK(sphere.GetVolume() == Approx(0.0));
	}
}

TEST_CASE("CBody GetMass", "[body][mass]")
{
	SECTION("Mass = density * volume")
	{
		double density = 2.0;
		double radius = 3.0;
		CSphere sphere(density, radius);
		double expectedMass = density * (4.0 / 3.0) * std::numbers::pi * std::pow(radius, 3);
		CHECK(sphere.GetMass() == Approx(expectedMass));
	}
	SECTION("Mass with zero density is zero")
	{
		CSphere sphere(0.0, 5.0);
		CHECK(sphere.GetMass() == Approx(0.0));
	}
	SECTION("Mass with zero radius is zero")
	{
		CSphere sphere(5.0, 0.0);
		CHECK(sphere.GetMass() == Approx(0.0));
	}
	SECTION("Mass scales linearly with density")
	{
		CSphere sphere1(1.0, 5.0);
		CSphere sphere2(2.0, 5.0);
		CHECK(sphere2.GetMass() == Approx(sphere1.GetMass() * 2.0));
	}
	SECTION("Mass scales with cube of radius")
	{
		CSphere sphere1(1.0, 2.0);
		CSphere sphere2(1.0, 4.0);
		CHECK(sphere2.GetMass() == Approx(sphere1.GetMass() * 8.0));
	}
}

TEST_CASE("CBody ToString", "[body][tostring]")
{
	SECTION("ToString returns non-empty string")
	{
		CSphere sphere(1.0, 5.0);
		std::string str = sphere.ToString();
		std::string expected = "Sphere:\n\tdensity = 1.00\n\tvolume = 523.60\n\tmass = 523.60\n\tradius = 5.00\n";
		CHECK(str == expected);
	}
}
