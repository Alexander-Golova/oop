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
			// не может выбрать предыдущий канал
			THEN("can't select the previous channel")
			{
				CHECK(!tv.SelectPreviousChannel());
			}
			// изначально отображает 0 канал
			THEN("displays channel 0 by default")
			{
				CHECK(tv.GetChannel() == 0);
			}
			//нельзя задать имя для канала
			THEN("you can't set a name for the channel")
			{
				CHECK(!tv.SetChannelName(1, "ОРТ"));
			}
		}

		// может быть включен
		WHEN("can be turned off")
		{
			tv.TurnOn();
			THEN("TV can be turned on")
			{
				CHECK(tv.IsTurnedOn());
			}
			// не может выбрать предыдущий канал
			THEN("can't select the previous channel")
			{
				CHECK(tv.IsTurnedOn());
				CHECK(!tv.SelectPreviousChannel());
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
		WHEN("TV returns to the previous channel")
		{
			tv.SelectChannel(2);
			tv.SelectChannel(5);			
			THEN("channel on TV 2")
			{
				REQUIRE(tv.SelectPreviousChannel());
				CHECK(tv.GetChannel() == 2);
			}
			tv.SelectChannel(2);
			tv.SelectChannel(5);
			tv.SelectChannel(7);
			THEN("channel on TV 5")
			{
				REQUIRE(tv.SelectPreviousChannel());
				CHECK(tv.GetChannel() == 5);
			}
			// двойной возврат ничего не изменяет
			THEN("a double refund doesn't change anything")
			{
				tv.SelectChannel(15);
				tv.SelectChannel(17);
				CHECK(tv.GetChannel() == 17);
				REQUIRE(tv.SelectPreviousChannel());
				CHECK(tv.GetChannel() == 15);
				REQUIRE(tv.SelectPreviousChannel());
				CHECK(tv.GetChannel() == 17);
			}
		}
	}

	// Повторное включение телевизора
	GIVEN("Turning on the TV again")
	{
		CTVSet tv;
		tv.TurnOn();
		tv.SelectChannel(11);
		tv.SelectChannel(33);
		tv.TurnOff();
		// после повторного включения восстанавливает последний выбранный канал
		WHEN("after turning on the TV again")
		{
			tv.TurnOn();
			// восстанавливает последний выбранный канал
			THEN("restores last selected channel")
			{
				CHECK(tv.GetChannel() == 33);
			}
			// восстанавливает предыдущий канал
			THEN("restores last selected channel")
			{
				REQUIRE(tv.SelectPreviousChannel());
				CHECK(tv.GetChannel() == 11);
			}
		}
	}
	//Изменение имени канала
	GIVEN("Changing the channel name")
	{
		CTVSet tv;
		tv.TurnOn();
		std::string channelName;
		// название канала не может быть пустой строкой
		WHEN("the channel name cannot be an empty string.")
		{
			CHECK(!tv.SetChannelName(1, ""));
		}
		// название канала не может содержать только пробелы
		AND_WHEN("the channel name cannot contain only spaces")
		{
			CHECK(!tv.SetChannelName(1, "     "));
		}
		// название канала находится
		AND_WHEN("the name of the channel is")
		{
			CHECK(tv.SetChannelName(1, "ОРТ"));			
			REQUIRE(tv.GetChannelName(1, channelName));
			CHECK(channelName == "ОРТ");
		}
		// в канала названии удаляются лишние пробелы
		AND_WHEN("the extra spaces are removed in each name")
		{
			CHECK(tv.SetChannelName(10, "   national    geographic   "));
			REQUIRE(tv.GetChannelName(10, channelName));
			CHECK(channelName == "national geographic");
		}
		AND_WHEN("valid channel name")
		{
			REQUIRE(tv.SetChannelName(1, "bbc"));
			REQUIRE(tv.SetChannelName(2, "cnn"));
			REQUIRE(tv.SetChannelName(3, "discovery"));
			// можно переопределить существующее название канала
			THEN("you can redefine the existing channel name")
			{
				CHECK(tv.SetChannelName(3, "abc"));
				REQUIRE(tv.GetChannelName(3, channelName));
				CHECK(channelName == "abc");
			}
			//можно удалить названия канала
			AND_THEN("you can delete channel names")
			{
				REQUIRE(tv.SetChannelName(1, "bbc"));
				REQUIRE(tv.DeleteChannelName("bbc"));
				REQUIRE(!tv.GetChannelName(1, channelName));
			}
			// можно получить название канала по его номеру
			AND_THEN("you can get the channel name by its number")
			{
				REQUIRE(tv.GetChannelName(2, channelName));
				REQUIRE(channelName == "cnn");
			}

		}

	}
}
