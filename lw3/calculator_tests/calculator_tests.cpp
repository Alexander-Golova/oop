#include "stdafx.h"

#include "../calculator/calculator.h"
#include <functional>

using namespace std;

struct CalculatorFixture
{
	CCalculator calc;
};

// калькул€тор
BOOST_FIXTURE_TEST_SUITE(Calculator_, CalculatorFixture)
	// можно объ€вить новую переменную
	BOOST_AUTO_TEST_CASE(can_set_new_variable)
	{
		BOOST_CHECK(calc.SetVar("x"));
	}

BOOST_AUTO_TEST_SUITE_END()