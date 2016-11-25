#include "stdafx.h"

#include "../calculator/calculator.h"
#include <functional>

using namespace std;

namespace
{
	bool IsNan(const double & numeric)
	{
		return numeric != numeric;
	}
}

struct CalculatorFixture
{
	CCalculator calc;
};

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
	BOOST_AUTO_TEST_CASE(name_of_variable_cant_be_empty_or_start_from_digit)
	{
		BOOST_CHECK(calc.GetVars().empty());
		BOOST_CHECK(!calc.SetVar(""));
		BOOST_CHECK(!calc.SetVar("12qww"));
	}
	// можно объявить функцию с ранее необъявленным идентификатором
	BOOST_AUTO_TEST_CASE(can_declare_function_with_non_existent_var)
	{
		BOOST_CHECK(calc.GetFunctions().empty());
		BOOST_CHECK(calc.LetVarValue("x", "5"));
		BOOST_CHECK(calc.LetVarValue("y", "7"));
		BOOST_CHECK(calc.SetFunction("f", "x", Operator::Plus, "y"));
		BOOST_CHECK(IsNan(calc.GetValue("fuction")));
	}
	// Имя функции не может быть пустым
	BOOST_AUTO_TEST_CASE(function_name_can_not_be_empty)
	{
		BOOST_CHECK(calc.GetFunctions().empty());
		BOOST_CHECK(calc.LetVarValue("x", "5"));
		BOOST_CHECK(calc.LetVarValue("y", "7"));
		BOOST_CHECK(!calc.SetFunction("", "x", Operator::Minus, "y"));
		BOOST_CHECK(calc.GetFunctions().empty());
	}

	// для переменных можно объявить функции
	struct for_the_variables_can_declare_the_functions_ : CalculatorFixture
	{
		for_the_variables_can_declare_the_functions_()
		{
			calc.LetVarValue("x", "2");
			calc.LetVarValue("y", "3");
		}
	};
	BOOST_FIXTURE_TEST_SUITE(for_the_variables_can_declare_the_functions, for_the_variables_can_declare_the_functions_)
		// сложения
		BOOST_AUTO_TEST_CASE(addition)
		{
			BOOST_CHECK(calc.SetFunction("f", "x", Operator::Plus, "y"));
			BOOST_CHECK_EQUAL(calc.GetValue("f"), 5);
		}
		// вычитания
		BOOST_AUTO_TEST_CASE(subtraction)
		{
			BOOST_CHECK(calc.SetFunction("f", "x", Operator::Minus, "y"));
			BOOST_CHECK_EQUAL(calc.GetValue("f"), -1);
		}
		// умножения
		BOOST_AUTO_TEST_CASE(multiplication)
		{
			BOOST_CHECK(calc.SetFunction("f", "x", Operator::Multiplication, "y"));
			BOOST_CHECK_EQUAL(calc.GetValue("f"), 6);
		}
		// деления
		BOOST_AUTO_TEST_CASE(division)
		{
			BOOST_CHECK(calc.SetFunction("f", "y", Operator::Division, "x"));
			BOOST_CHECK_EQUAL(calc.GetValue("f"), 1.5);
		}

	BOOST_AUTO_TEST_SUITE_END()

	// переменные
	struct variables_ : CalculatorFixture
	{
		variables_()
		{
			calc.LetVarValue("a", "2");
			calc.LetVarValue("b", "3");
			calc.LetVarValue("c", "4");
		}
	};
	BOOST_FIXTURE_TEST_SUITE(variables, variables_)
		// наследуются 
		BOOST_AUTO_TEST_CASE(inherited)
		{
			BOOST_CHECK(calc.SetFunction("f", "a", Operator::Plus, "b"));
			BOOST_CHECK(calc.SetFunction("g", "f", Operator::Plus, "c"));
			BOOST_CHECK(calc.SetFunction("u", "f", Operator::Plus, "g"));
			BOOST_CHECK_EQUAL(calc.GetValue("u"), 14);
			BOOST_CHECK(calc.LetVarValue("a", "100"));
			BOOST_CHECK_EQUAL(calc.GetValue("u"), 210);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()