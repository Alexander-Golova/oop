#include "stdafx.h"

#include "../calculator/calculator.h"
#include <functional>

using namespace std;



struct CalculatorFixture
{
	CCalculator calc;
};

namespace
{
	bool IsNan(const double & numeric)
	{
		return numeric != numeric;
	}
}

// калькулятор
BOOST_FIXTURE_TEST_SUITE(Calculator_, CalculatorFixture)
	// можно объявить новую переменную
	BOOST_AUTO_TEST_CASE(can_set_new_variable)
	{
		BOOST_CHECK(calc.SetVar("x"));
		auto vars = calc.GetVars();
		BOOST_CHECK(vars.find("x") != vars.end());
	}
	//  нельзя второй раз объявить переменную
	BOOST_AUTO_TEST_CASE(you_can_not_declare_a_variable_for_the_second_time)
	{
		BOOST_CHECK(calc.SetVar("x"));
		BOOST_CHECK(!calc.SetVar("x"));
	}
	// значение не объявленной переменной равно NAN
	BOOST_AUTO_TEST_CASE(value_of_not_declared_var_equal_to_NAN)
	{
		BOOST_CHECK(calc.GetVars().empty());
		BOOST_CHECK(IsNan(calc.GetValue("x")));
	}
	// переменной можно задать значение
	BOOST_AUTO_TEST_CASE(can_be_set_declares_when_unknown_variable)
	{
		BOOST_CHECK(calc.GetVars().empty());
		BOOST_CHECK(IsNan(calc.GetValue("x")));
		BOOST_CHECK(calc.LetVarValue("x", "579"));
		BOOST_CHECK_EQUAL(calc.GetValue("x"), 579);
	}
	// переменной можно передать значение другой переменной
	BOOST_AUTO_TEST_CASE(variable_can_pass_the_value_of_another_variable)
	{
		BOOST_CHECK(calc.GetVars().empty());
		BOOST_CHECK(IsNan(calc.GetValue("x")));
		BOOST_CHECK(calc.LetVarValue("x", "579"));
		BOOST_CHECK(calc.LetVarValue("y", "x"));
		BOOST_CHECK_EQUAL(calc.GetValue("y"), 579);
	}
	// имя переменной не может начинаться с цифры и быть пустым
	BOOST_AUTO_TEST_CASE(name_of_var_cant_be_empty_or_start_from_digit)
	{
		BOOST_CHECK(calc.GetVars().empty());
		BOOST_CHECK(!calc.SetVar(""));
		BOOST_CHECK(!calc.SetVar("12qww"));
	}

BOOST_AUTO_TEST_SUITE_END()