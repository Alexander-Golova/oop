#include "stdafx.h"

#include "../Solve4/Equation.h"

using namespace std;

const double epsilon = 0.0001;

template <typename Ex, typename Fn>
void ExpectException(Fn && fn, const string & expectedDescription)
{
	// Проверяем, что вызов fn() выбросит исключение типа Ex 
	// с описанием, равным expectedDescription
	BOOST_CHECK_EXCEPTION(fn(), Ex, [&](const Ex& e) {
		return e.what() == expectedDescription;
	});
	try
	{
	fn(); // Выполняем действие, от которого ожидаем выброс исключения
	// Если не выбросило, то тест провалился
	BOOST_ERROR("No exception thrown");
	}
	catch (const Ex & e) // Ловим исключение типа Ex (или его подкласс)
	{
	// Проверяем, что исключение будет иметь ожидаемое сообщение
	BOOST_CHECK_EQUAL(expectedDescription, e.what());
	}
	catch (...)
	{
	// Если выбросили иное исключение, то это также ошибка
	BOOST_ERROR("Unexpected exception");
	}
}

template <typename Ex>
void ExpectResultFailure(double a, double b, double c, double d, double e, const string & expectedDescription)
{
	ExpectException<Ex>([&] {
		Solve4(a, b, c, d, e);
	}, expectedDescription);
}

bool IsRootsEqual(const double roots[4], const double expectedRoots[4], size_t numbRoots)
{
	for (size_t i = 0; i < numbRoots; ++i)
	{
		if (ceil(roots[i] * 10000) / 10000.0 != (ceil(expectedRoots[i] * 10000) / 10000.0))
		{
			return false;
		}
	}
	return true;
}

void CheckRoots(EquationRoot4 const& result, unsigned expectedNumberRoots, const double expectedRoots[4])
{
	BOOST_CHECK_EQUAL(result.numRoots, expectedNumberRoots);
	BOOST_CHECK(IsRootsEqual(result.roots, expectedRoots, expectedNumberRoots));
}

// максимальный действительный корень уравнения третьей степени
BOOST_AUTO_TEST_SUITE(maximum_root_of_the_equation_of_the_third_degree)

	BOOST_AUTO_TEST_CASE(in_the_case_of_the_three_roots_in_the_equation)
	{
		BOOST_CHECK_CLOSE_FRACTION(Solve3(0, -1, 0), 1, epsilon);
	}
	BOOST_AUTO_TEST_CASE(in_the_case_of_the_same_root)
	{
		BOOST_CHECK_CLOSE_FRACTION(Solve3(-1, -1, -2), 2, epsilon);
		BOOST_CHECK_CLOSE_FRACTION(Solve3(-1, 1, -1), 1, epsilon);
		BOOST_CHECK_CLOSE_FRACTION(Solve3(3, 3, 2), -2, epsilon);
	}
	BOOST_AUTO_TEST_CASE(in_the_case_of_two_different_roots)
	{
		BOOST_CHECK_CLOSE_FRACTION(Solve3(3, 0, -4), 1, epsilon);
	}

BOOST_AUTO_TEST_SUITE_END()

// уравнение 4 степени
BOOST_AUTO_TEST_SUITE(Equation)

	BOOST_AUTO_TEST_CASE(not_have_highest_coefficient_of_zero)
	{
		ExpectResultFailure<invalid_argument>(0, 1, 1, 1, 1, "Argument 'a' can not be 0.");
	}
	BOOST_AUTO_TEST_CASE(can_have_no_roots)
	{
		double expectedRoots[4];
		CheckRoots(Solve4(1, 4, 6, 4, 2), 0, expectedRoots);
	}
	BOOST_AUTO_TEST_CASE(has_four_equal_real_roots)
	{
		double expectedRoots1[4] = { 0, 0, 0, 0 };
		CheckRoots(Solve4(1, 0, 0, 0, 0), 4, expectedRoots1);
		double expectedRoots2[4] = { -1, -1, -1, -1 };
		CheckRoots(Solve4(1, 4, 6, 4, 1), 4, expectedRoots2);
	}	
	BOOST_AUTO_TEST_CASE(has_different_real_roots)
	{
		double expectedRoots3[4] = { 0, 1, 2, 3 };
		CheckRoots(Solve4(1, -6, 11, -6, 0), 4, expectedRoots3);
		double expectedRoots4[4] = { -1, -1, 1, 1 };
		CheckRoots(Solve4(1, 0, -2, 0, 1), 4, expectedRoots4);
	}
	BOOST_AUTO_TEST_CASE(has_two_real_roots)
	{
		double expectedRoots5[4] = { -2, 1 };
		CheckRoots(Solve4(1, 3, 3, -1, -6), 2, expectedRoots5);
	}
BOOST_AUTO_TEST_SUITE_END()
