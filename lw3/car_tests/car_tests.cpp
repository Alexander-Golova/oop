#include "stdafx.h"

#include "../car/Car.h"

struct CarFixture
{
	CCar car;
};

// ����������
BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)

	// ���������� � ����������� ����������
	BOOST_AUTO_TEST_CASE(is_engine_turned_off_by_default)
	{
		BOOST_CHECK(!car.IsEngineTurnOn());
	}

BOOST_AUTO_TEST_SUITE_END()
