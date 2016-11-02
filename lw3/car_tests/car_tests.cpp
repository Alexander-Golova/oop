#include "stdafx.h"

#include "../car/Car.h"

struct CarFixture
{
	CCar car;
};

// автомобиль
BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)

	// изначально с выключенным двигателем
	BOOST_AUTO_TEST_CASE(is_engine_turned_off_by_default)
	{
		BOOST_CHECK(!car.IsEngineTurnOn());
	}
	// находится на нейтральной передаче
	BOOST_AUTO_TEST_CASE(is_on_neutral_gear_by_default)
	{
		BOOST_CHECK(car.GetGear() == Gear::Neutral);
	}
	// имеет нулевую скорость
	BOOST_AUTO_TEST_CASE(it_has_zero_speed)
	{
		BOOST_CHECK(car.GetSpeed() == 0);
	}
	// у выключенного автомобиля направление движения нет (стоим на месте)
	BOOST_AUTO_TEST_CASE(auto_shut_down_at_the_direction_of_motion_is_not)
	{
		BOOST_CHECK(car.GetDirection() == Direction::Stop);
	}

	// нельзя выбрать передачу в выключенном состоянии отличную от нейтральной
	BOOST_AUTO_TEST_CASE(can_not_select_the_transmission_off)
	{
		{
			BOOST_CHECK(car.SetGear(Gear::Neutral));
			BOOST_CHECK(car.GetGear() == Gear::Neutral);
		}
		{
			auto clone(car);
			BOOST_CHECK(!car.SetGear(Gear::First));
			BOOST_CHECK(car.GetGear() == Gear::Neutral);
			BOOST_CHECK(car == clone);
		}
		{
			auto clone(car);
			BOOST_CHECK(!car.SetGear(Gear::Reverse));
			BOOST_CHECK(car.GetGear() == Gear::Neutral);
			BOOST_CHECK(car == clone);
		}
	}


	// может быть включен
	BOOST_AUTO_TEST_CASE(can_be_turned_on)
	{
		car.TurnOnEngine();
		BOOST_CHECK(car.IsEngineTurnOn());
	}
	// включенный автомобиль может быть выключен
	BOOST_AUTO_TEST_CASE(can_be_turned_auto_it_can_be_switched_off)
	{
		car.TurnOnEngine();
		car.TurnOffEngine();
		BOOST_CHECK(!car.IsEngineTurnOn());
	}

	struct when_engine_turned_on_ : CarFixture
	{
		when_engine_turned_on_()
		{
			car.TurnOnEngine();
		}
	};

	// после включения
	BOOST_FIXTURE_TEST_SUITE(when_engine_turned_on, when_engine_turned_on_)
		// включенный автомобиль изначально находится на нейтральной передаче
		BOOST_AUTO_TEST_CASE(can_be_turned_on_is_on_neutral_gear_by_default)
		{
			BOOST_CHECK(car.GetGear() == Gear::Neutral);
		}
		// имеет нулевую скорость
		BOOST_AUTO_TEST_CASE(can_be_turned_it_has_zero_speed)
		{
			BOOST_CHECK(car.GetSpeed() == 0);
		}
		// не имеет направление движения
		BOOST_AUTO_TEST_CASE(can_be_turned_auto_shut_down_at_the_direction_of_motion_is_not)
		{
			BOOST_CHECK(car.GetDirection() == Direction::Stop);
		}
		// у включенного автомобиля можно включать передачи
		BOOST_AUTO_TEST_CASE(in_the_car_can_be_switched_off_transmission)
		{
			{
				BOOST_CHECK(car.SetGear(Gear::Neutral));
				BOOST_CHECK(car.GetGear() == Gear::Neutral);
			}

			{
				BOOST_CHECK(car.SetGear(Gear::First));
				BOOST_CHECK(car.GetGear() == Gear::First);
			}

			{
				BOOST_CHECK(car.SetGear(Gear::Reverse));
				BOOST_CHECK(car.GetGear() == Gear::Reverse);
			}

			{
				auto clone(car);
				BOOST_CHECK(!car.SetGear(Gear::Second));
				BOOST_CHECK(car == clone);
			}
		}
		// на первой передаче
		struct first_gear_ : when_engine_turned_on_
		{
			first_gear_()
			{
				car.SetGear(Gear::First);
				car.SetSpeed(15);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(first_gear, first_gear_)
			// можно выбрать скорость в пределах диапазона 0 - 30
			BOOST_AUTO_TEST_CASE(choose_the_speed_in_first_gear)
			{
				{
					BOOST_CHECK(car.SetSpeed(30));
					BOOST_CHECK(car.GetSpeed() == 30);
				}
				{
					BOOST_CHECK(car.SetSpeed(0));
					BOOST_CHECK(car.GetSpeed() == 0);
				}
				{
					BOOST_CHECK(car.SetSpeed(10));
					BOOST_CHECK(car.GetSpeed() == 10);
				}
			}
			// нельзя выбрать скорость вне диапазона
			BOOST_AUTO_TEST_CASE(you_can_not_select_the_speed_out_of_range)
			{
				{
					auto clone(car);
					BOOST_CHECK(!car.SetSpeed(31));
					BOOST_CHECK(car == clone);;
				}
			}
			// нельзя без остановки переключится на заднюю передачу
			BOOST_AUTO_TEST_CASE(it_can_not_be_non_stop_switches_to_reverse_gear)
			{
				{
					BOOST_CHECK(car.SetSpeed(15));
					BOOST_CHECK(car.GetSpeed() == 15);
					BOOST_CHECK(car.SetGear(Gear::Neutral));
					BOOST_CHECK(car.GetGear() == Gear::Neutral);
					BOOST_CHECK(!car.SetGear(Gear::Reverse));
				}
			}
			// можно разогнаться до максимальной скорости
			BOOST_AUTO_TEST_CASE(can_accelerate_to_maximum_speed)
			{
				{
					BOOST_CHECK(car.SetSpeed(30));
					BOOST_CHECK(car.GetSpeed() == 30);
					BOOST_CHECK(car.SetGear(Gear::Second));
					BOOST_CHECK(car.GetGear() == Gear::Second);
					BOOST_CHECK(car.SetSpeed(50));
					BOOST_CHECK(car.GetSpeed() == 50);
					BOOST_CHECK(car.SetGear(Gear::Third));
					BOOST_CHECK(car.GetGear() == Gear::Third);
					BOOST_CHECK(car.SetSpeed(60));
					BOOST_CHECK(car.GetSpeed() == 60);
					BOOST_CHECK(car.SetGear(Gear::Fourth));
					BOOST_CHECK(car.GetGear() == Gear::Fourth);
					BOOST_CHECK(car.SetSpeed(90));
					BOOST_CHECK(car.GetSpeed() == 90);
					BOOST_CHECK(car.SetGear(Gear::Fifth));
					BOOST_CHECK(car.GetGear() == Gear::Fifth);
					BOOST_CHECK(car.SetSpeed(150));
					BOOST_CHECK(car.GetSpeed() == 150);
					BOOST_CHECK(!car.SetSpeed(151));
				}
			}
		BOOST_AUTO_TEST_SUITE_END()

		// на задней передаче
		struct on_reverse_ : when_engine_turned_on_
		{
			on_reverse_()
			{
				car.SetGear(Gear::Reverse);
				car.SetSpeed(15);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(on_reverse, on_reverse_)
			// можно разогнаться от 0 до 20
			BOOST_AUTO_TEST_CASE(choose_the_speed_in_reverse_gear)
			{
				{
					BOOST_CHECK(car.SetSpeed(20));
					BOOST_CHECK(car.GetSpeed() == 20);
				}
				{
					BOOST_CHECK(car.SetSpeed(0));
					BOOST_CHECK(car.GetSpeed() == 0);
				}
				{
					BOOST_CHECK(car.SetSpeed(10));
					BOOST_CHECK(car.GetSpeed() == 10);
				}
			}
			// нельзя выбрать скорость вне диапазона
			BOOST_AUTO_TEST_CASE(you_can_not_select_the_speed_out_of_range_in_reverse_gear)
			{
				{
					auto clone(car);
					BOOST_CHECK(!car.SetSpeed(21));
					BOOST_CHECK(car == clone);;
				}
			}
			// можно включить нейтральную передачу и уменьшить скорость
			BOOST_AUTO_TEST_CASE(you_can_include_neutral_and_reduce_speed)
			{
				{
					BOOST_CHECK(car.SetGear(Gear::Neutral));
					BOOST_CHECK(car.GetGear() == Gear::Neutral);
					BOOST_CHECK(car.SetSpeed(8));
					BOOST_CHECK(car.GetSpeed() == 8);
				}
			}

		BOOST_AUTO_TEST_SUITE_END()

		// на нейтральной передаче
		struct on_neutral_ : when_engine_turned_on_
		{
				on_neutral_()
			{
				car.SetGear(Gear::Neutral);
				car.SetSpeed(40);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(on_neutral, on_neutral_)
			// нельзя увеличить скорость
			BOOST_AUTO_TEST_CASE(it_is_impossible_to_increase_the_speed_in_neutral)
			{
				{
					auto clone(car);
					BOOST_CHECK(!car.SetSpeed(18));
					BOOST_CHECK(car == clone);;
				}
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
