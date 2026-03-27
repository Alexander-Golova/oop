#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <../catch/catch.hpp>

#include "../Car/Car.h"

SCENARIO("Car", "[car]")
{
	GIVEN("Car is Turned Off")
	{
		CCar car;
		// Машина изначально выключена
		WHEN("Car is turned off by default")
		{
			REQUIRE(!car.IsTurnedOn());
			CHECK(car.GetDirection() == Direction::Stop);
			CHECK(car.GetSpeed() == 0);
			CHECK(car.GetGear() == Gear::Neutral);
		}
		// машина может быть включена
		WHEN("Car is turned on")
		{
			REQUIRE(car.TurnOnEngine());
			CHECK(car.IsTurnedOn());
		}
		// включённая машина может быть выключена
		WHEN("Car is turned off")
		{
			REQUIRE(car.TurnOnEngine());
			REQUIRE(car.TurnOffEngine());
			CHECK(!car.IsTurnedOn());
		}
	}
	GIVEN("Car is Turned On")
	{
		CCar car;
		REQUIRE(car.TurnOnEngine());
		// тестируем передачи
		WHEN("Car is turned off")
		{
			REQUIRE(car.SetGear(1));
			CHECK(car.GetSpeed() == 0);
			REQUIRE(car.SetSpeed(10));
			CHECK(car.GetSpeed() == 10);
			REQUIRE(!car.SetSpeed(40));
			REQUIRE(car.SetSpeed(30));

			REQUIRE(car.SetGear(2));
			REQUIRE(car.SetSpeed(50));
			CHECK(car.GetSpeed() == 50);
			REQUIRE(!car.SetSpeed(150));
			
			REQUIRE(car.SetGear(3));
			REQUIRE(car.SetSpeed(60));
			CHECK(car.GetSpeed() == 60);
			REQUIRE(!car.SetSpeed(100));

			REQUIRE(car.SetGear(4));
			REQUIRE(car.SetSpeed(80));
			CHECK(car.GetSpeed() == 80);
			REQUIRE(!car.SetSpeed(100));

			REQUIRE(car.SetGear(5));
			REQUIRE(car.SetSpeed(120));
			CHECK(car.GetSpeed() == 120);
			REQUIRE(!car.SetSpeed(160));
			REQUIRE(!car.SetGear(-1));

			REQUIRE(car.SetGear(0));
			REQUIRE(car.SetSpeed(0));
			CHECK(car.GetSpeed() == 0);
			REQUIRE(car.SetGear(-1));
			REQUIRE(car.SetSpeed(10));
			CHECK(car.GetSpeed() == 10);
			REQUIRE(!car.SetSpeed(25));

			REQUIRE(!car.SetGear(1));
		}

	}
	
}
