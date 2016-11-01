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
	// нельзя выбрать передачу в выключенном состоянии
	BOOST_AUTO_TEST_CASE(can_not_select_the_transmission_off)
	{
		BOOST_CHECK(!car.SetSpeed(1));
	}
	// у выключенного автомобиля направление движения нет (стоим на месте)
	BOOST_AUTO_TEST_CASE(auto_shut_down_at_the_direction_of_motion_is_not)
	{
		BOOST_CHECK(car.GetDirection() == Direction::Stop);
	}

BOOST_AUTO_TEST_SUITE_END()
