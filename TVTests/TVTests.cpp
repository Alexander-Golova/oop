#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch/catch.hpp>

#include "../TV/TVSet.h"


SCENARIO("TV", "[tv]")
{
	GIVEN("A new TV has been created")
	{
		CTVSet tv;
		// Телевизор изначально выключен
		WHEN("TV is turned off by default")
		{
			REQUIRE(!tv.IsTurnedOn());

			// не может переключать канал в выключенном состоянии
			THEN("cant select channel when turned off")
			{
				CHECK(!tv.SelectChannel(87));
			}
			// изначально отображает 0 канал
			THEN("displays channel 0 by default")
			{
				CHECK(tv.GetChannel() == 0);
			}
		}

		// может быть включен
		WHEN("TV can be turned on")
		{
			tv.TurnOn();
			THEN("displays channel 0 by default")
			{
				CHECK(tv.IsTurnedOn());
			}
		}
	}

	GIVEN("The TV is on")
	{
		CTVSet tv;
		// Включаем телевизор
		WHEN("Turn on the TV")
		{
			tv.TurnOn();
			// ТВ отображает канал 1
			THEN("displays channel one")
			{
				CHECK(tv.GetChannel() == 1);
			}
		}
		// Включённый телевизор можно выключить
		WHEN("You can turn off the TV when it is on.")
		{
			tv.TurnOn();
			tv.TurnOff();
			THEN("can be turned off")
			{			
				CHECK(!tv.IsTurnedOn());
			}
		}

		tv.TurnOn();
		WHEN("can select 1 channel")
		{
			tv.SelectChannel(1);
			THEN("channel on TV 1")
			{
				CHECK(tv.GetChannel() == 1);
			}
		}
		WHEN("can select 99 channel")
		{
			tv.SelectChannel(99);
			THEN("channel on TV 99")
			{
				CHECK(tv.GetChannel() == 99);
			}
		}
		WHEN("can select 48 channel")
		{
			tv.SelectChannel(48);
			THEN("channel on TV 48")
			{
				CHECK(tv.GetChannel() == 48);
			}
			tv.SelectChannel(100);
			THEN("channel on TV 100")
			{
				CHECK(tv.GetChannel() == 48);
			}
			tv.SelectChannel(0);
			THEN("channel on TV 0")
			{
				CHECK(tv.GetChannel() == 48);
			}
		}
	}
}
