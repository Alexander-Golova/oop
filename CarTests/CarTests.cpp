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
		// у включённой машины можно выбрать первую передачу и скорость
		WHEN("When the car is switched on, you can select first gear and speed")
		{
			REQUIRE(car.SetGear(1));
			CHECK(car.GetSpeed() == 0);
			REQUIRE(car.GetDirection() == Direction::Forward);
			REQUIRE(car.SetSpeed(10));
			CHECK(car.GetSpeed() == 10);
			REQUIRE(!car.SetSpeed(40));
			REQUIRE(car.SetSpeed(30));
			CHECK(car.GetSpeed() == 30);
		}
		// можно выбрать вторую передачу 
		WHEN("You can select the second gear")
		{
			REQUIRE(car.SetGear(1));
			REQUIRE(car.SetSpeed(30));
			REQUIRE(car.SetGear(2));
			REQUIRE(car.GetDirection() == Direction::Forward);
			REQUIRE(car.SetSpeed(50));
			CHECK(car.GetSpeed() == 50);
			REQUIRE(!car.SetSpeed(150));
		}
		// можно выбрать третью передачу 
		WHEN("You can choose the third gear")
		{
			REQUIRE(car.SetGear(1));
			REQUIRE(car.SetSpeed(30));
			REQUIRE(car.SetGear(3));
			REQUIRE(car.SetSpeed(60));
			CHECK(car.GetSpeed() == 60);
			REQUIRE(!car.SetSpeed(100));
		}
		// можно выбрать четвёртую  передачу
		WHEN("You can choose the fourth  gear")
		{
			REQUIRE(car.SetGear(1));
			REQUIRE(car.SetSpeed(30));
			REQUIRE(car.SetGear(2));
			REQUIRE(car.SetSpeed(50));
			REQUIRE(car.SetGear(4));
			REQUIRE(car.SetSpeed(80));
			CHECK(car.GetSpeed() == 80);
			REQUIRE(!car.SetSpeed(100));
		}
		// можно выбрать пятую  передачу
		WHEN("You can choose the fifth gear")
		{
			REQUIRE(car.SetGear(1));
			REQUIRE(car.SetSpeed(30));
			REQUIRE(car.SetGear(2));
			REQUIRE(car.SetSpeed(50));
			REQUIRE(car.SetGear(5));
			REQUIRE(car.SetSpeed(120));
			CHECK(car.GetSpeed() == 120);
			REQUIRE(!car.SetSpeed(160));
		}
		// на скорости нельзя включить задний ход
		WHEN("You can't reverse at speed")
		{	
			REQUIRE(car.SetGear(1));
			REQUIRE(car.SetSpeed(30));
			REQUIRE(!car.SetGear(-1));
		}
		// у стоящей машины можно включить задний ход
		WHEN("When the car is parked, you can turn on the reverse gear")
		{
			REQUIRE(car.SetGear(1));
			REQUIRE(car.SetSpeed(30));
			REQUIRE(car.SetGear(0));
			REQUIRE(car.SetSpeed(0));
			CHECK(car.GetSpeed() == 0);
			REQUIRE(car.SetGear(-1));
			REQUIRE(car.SetSpeed(10));
			CHECK(car.GetSpeed() == 10);
			REQUIRE(!car.SetGear(-1));
			REQUIRE(!car.SetSpeed(25));
		}
		// у движущейся назад машины нельзя включить первую передачу
		WHEN("You can't put the car in first gear when it's moving backwards")
		{
			REQUIRE(car.SetGear(-1));
			REQUIRE(car.SetSpeed(10));
			REQUIRE(car.GetDirection() == Direction::Back);
			REQUIRE(!car.SetGear(1));
		}

	}
	
}
