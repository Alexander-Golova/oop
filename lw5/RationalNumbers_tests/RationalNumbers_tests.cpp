﻿#include "stdafx.h"
#include "../RationalNumbers/Rational.h"

BOOST_AUTO_TEST_CASE(Test_Greates_Common_Denominator)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1u);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2u);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
}

/*
Рациональное число:
равно нулю по умолчанию (0/1)
может быть созданно из целого в формате (n / 1)
может быть задано с указанием числителя и знаменателя
хранится в нормализованном виде
*/

void VerifyRational(const CRational & r, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(r.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(r.GetDenominator(), expectedDenominator);
}

void VerifyInputOperator(const std::string & str, boost::optional<CRational> expectedResult)
{
	std::istringstream input(str);
	CRational rat;
	input >> rat;
	if (expectedResult == boost::none)
	{
		BOOST_CHECK_EQUAL(input.fail(), true);
	}
	else
	{
		VerifyRational(rat, expectedResult->GetNumerator(), expectedResult->GetDenominator());
	}
}

void VerifyCompoundFraction(const CRational &r, int expectedInteger, int expectedNumerator, int expectedDeniminator)
{
	BOOST_CHECK_EQUAL(r.ToCompoundFraction().first, expectedInteger);
	BOOST_CHECK_EQUAL(r.ToCompoundFraction().second.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(r.ToCompoundFraction().second.GetDenominator(), expectedDeniminator);
}

BOOST_AUTO_TEST_SUITE(Rational_number)
BOOST_AUTO_TEST_CASE(is_0_by_default)
{
	VerifyRational(CRational(), 0, 1);
}
BOOST_AUTO_TEST_CASE(can_be_constructed_from_integer)
{
	VerifyRational(CRational(10), 10, 1);
	VerifyRational(CRational(-10), -10, 1);
	VerifyRational(CRational(0), 0, 1);
}
BOOST_AUTO_TEST_CASE(can_be_constructed_with_numerator_and_denominator)
{
	VerifyRational(CRational(5, 2), 5, 2);
	VerifyRational(CRational(-5, 2), -5, 2);
	VerifyRational(CRational(5, -2), -5, 2);
	VerifyRational(CRational(-5, -2), 5, 2);
}
BOOST_AUTO_TEST_CASE(is_normalized_after_construction)
{
	VerifyRational(CRational(6, 8), 3, 4);
	VerifyRational(CRational(6, -8), -3, 4);
	VerifyRational(CRational(-6, 8), -3, 4);
	VerifyRational(CRational(-6, -8), 3, 4);
	VerifyRational(CRational(-10, 20), -1, 2);
}
BOOST_AUTO_TEST_CASE(cant_have_zero_denominator)
{
	BOOST_REQUIRE_THROW(CRational(1, 0), std::invalid_argument);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
// Возвращает отношение числителя и знаменателя в виде числа double
// Пример использования:
//	CRational r(3, 5)
//	cout << r.ToDouble(); // Должно вывести 0.6
//////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(can_be_converted_to_double)
{
	BOOST_CHECK_CLOSE_FRACTION(CRational(3, 5).ToDouble(), 0.6, DBL_EPSILON);
	BOOST_CHECK_CLOSE_FRACTION(CRational(7, 2).ToDouble(), 3.5, DBL_EPSILON);
	BOOST_CHECK_CLOSE_FRACTION(CRational(-3, 4).ToDouble(), -0.75, DBL_EPSILON);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
// Указание: см. материалы к лекции
// Пример использования:
//	const CRational r1(3, 5);
//	CRational r2 = -r1; // r2 должно стать -3/5
//	assert(r2.GetNumerator(), -3);
//	assert(r2.GetDenominator(), 5);
//	CRational r3 = +r2; // r3 также равно -3/5
//	assert(r3.GetNumerator(), -3);
//	assert(r3.GetDenominator(), 5);
// Унарный минус возвращает раицональное число с противоположным знаком
// Унарный плюс возвращает рациональное число, равное текущему
// Реализация не должна допускать операции вроде:
//  -someRational = someOtherRational;
//	+someRational = someOtherRational;
//////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(has_unary_minus_that_return_unsigned_fraction)
{
	VerifyRational(-CRational(2, 3), -2, 3);
	VerifyRational(-CRational(-2, 3), 2, 3);
	VerifyRational(-CRational(-2, -3), -2, 3);
}

BOOST_AUTO_TEST_CASE(has_unary_plus_that_return_itself)
{
	VerifyRational(+CRational(2, 3), 2, 3);
	VerifyRational(+CRational(-2, 3), -2, 3);
	VerifyRational(+CRational(2, -3), -2, 3);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 3. Реализовать бинарный +
// Возвращает результат сложения двух рациональных чисел, 
//	рационального числа с целым, целого числа с рациональным.
//	(1/2) + (1/6) = (2/3)
//	(1/2) + 1     = (3/2)
//	1 + (1/2)     = (3/2)
//////////////////////////////////////////////////////////////////////////
	
	BOOST_AUTO_TEST_CASE(has_binary_addition_operation)
	{
		VerifyRational(CRational(1, 2) + CRational(5, 6), 4, 3);
		VerifyRational(CRational(1, 2) + 1, 3, 2);
		VerifyRational(1 + CRational(1, 2), 3, 2);
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
// Возвращает разность двух рациональных чисел, 
//	рационального числа и целого, либо целого числа и рационального:
//	(1/2) - (1/6) = (1/3)
//	(1/2) - 1     = (-1/2)
//	1 - (1/2)     = (1/2)
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(has_binary_subtraction_operation)
	{
		VerifyRational(CRational(1, 2) - CRational(1, 6), 1, 3);
		VerifyRational(CRational(1, 2) - 1, -1, 2);
		VerifyRational(1 - CRational(1, 2), 1, 2);
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
// Выполняет увеличение рационального числа на величину второго рационального,
//	либо целого числа:
//	(1/2) += (1/6)  → (2/3)
//	(1/2) += 1      → (3/2)
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_CASE(has_adding_assignment_operator)
	{
			VerifyRational(CRational(1, 2) += CRational(1, 6), 2, 3);
			VerifyRational(CRational(1, 2) += 1, 3, 2);
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
// Выполняет уменьшение рационального числа на величину второго рационального либо целого числа :
// (1/2) -= (1/6)  → (1/3)
// (1/2) -= 1      → (-1/2)
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_CASE(has_subtracting_assignment_operator)
	{
		VerifyRational(CRational(1, 2) -= CRational(1, 6), 1, 3);
		VerifyRational(CRational(1, 2) -= 1, -1, 2);
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
// Возвращает результат произведения рациональных чисел, 
//	рационального и целого, либо целого и рационального :
//	(1/2) * (2/3) = (1/3)
//	(1/2) * (-3)  = (-3/2)
//	7 * (2/3)     = (14/3)
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(has_binary_multiplication_operation)
	{
		VerifyRational(CRational(1, 2) * CRational(2, 3), 1, 3);
		VerifyRational(CRational(1, 2) * CRational(-3), -3, 2);
		VerifyRational(CRational(14) * CRational(1, 2), 7, 1);
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
// Возвращает частное двух рациональных чисел, 
//	рационального и целого, целого и рационального :
//	(1/2) ⁄ (2/3) = (3/4)
//	(1/2) ⁄ 5     = (1/10)
//	7 ⁄ (2/3)     = (21/2)
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(has_division_operation)
	{
		VerifyRational(CRational(1, 2) / CRational(2, 3), 3, 4);
		VerifyRational(CRational(1, 2) / CRational(5), 1, 10);
		VerifyRational(CRational(7) / CRational(1, 2), 14, 1);
		BOOST_REQUIRE_THROW(CRational(1, 2) / CRational(0), std::invalid_argument::exception);
		BOOST_REQUIRE_THROW(CRational(1, 2) / CRational(0, 1), std::invalid_argument::exception);
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
// Умножает значение первого рационального числа на другое рациональное, 
//	либо целое:
//	(1/2) *= (2/3) → (1/3)
//	(1/2) *= 3     → (3/2)
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_CASE(has_multiply_assignment_operator)
	{
		CRational ratNum(3, 14);
		VerifyRational(ratNum *= ratNum, 9, 196);
		VerifyRational(CRational(1, 2) *= CRational(2, 3), 1, 3);
		VerifyRational(CRational(1, 2) *= 3, 3, 2);
		VerifyRational(CRational(3, 14) *= 7, 3, 2);
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
// Делит первое рациональное число на другое рациональное, 
//	либо целое:
//	(1/2) /= (2/3) → (3/4)
//	(3/4) /= (3/8) → (2/1)
//	(1/2) /= 3     → (1/6)
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_CASE(has_division_assignment_operator)
	{
		CRational rat(1, 2);
		VerifyRational(rat /= rat, 1, 1);
		VerifyRational(CRational(1, 2) /= CRational(2, 3), 3, 4);
		VerifyRational(CRational(1, 2) /= 3, 1, 6);
		BOOST_REQUIRE_THROW(CRational(1, 2) /= CRational(0), std::invalid_argument);
		BOOST_REQUIRE_THROW(CRational(1, 2) /= CRational(0, 1), std::invalid_argument);
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
// Проверяют равенство (и неравенство) двух рациональных чисел, 
//	целого и рационального, рационального и целого:
//	(1/2) == (1/2) → true
//	(4/1) == 4     → true
//	3 == (3/1)     → true
//	(1/2) != (2/3) → true
//	(1/2) != 7     → true
//	3 != (2/3)     → true
//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_CASE(can_be_compared_for_equality)
	{
		BOOST_CHECK(CRational(1, 2) == CRational(1, 2));
		BOOST_CHECK(CRational(1, 3) == CRational(2, 6));
		BOOST_CHECK(CRational(4, 1) == 4);
		BOOST_CHECK(3 == CRational(3, 1));
		BOOST_CHECK(!(CRational(1, 2) == CRational(2, 3)));
		BOOST_CHECK(!(CRational(1, 2) == 7));
		BOOST_CHECK(!(3 == CRational(2, 3)));
		BOOST_CHECK(!(CRational(1, 2) != CRational(1, 2)));
		BOOST_CHECK(!(CRational(1, 3) != CRational(2, 6)));
		BOOST_CHECK(!(CRational(4, 1) != 4));
		BOOST_CHECK(!(3 != CRational(3, 1)));
		BOOST_CHECK(CRational(1, 2) != CRational(2, 3));
		BOOST_CHECK(CRational(1, 2) != 7);
		BOOST_CHECK(3 != CRational(2, 3));
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
// Сравнивают два рациональных числа, рациональное с целым, 
//	целое с рациональным:
//	(1/2) >= (1/3) → true
//	(1/2) <= (1/3) → false
//	(3/1) > 2      → true
//	(1/2) < 7      → true
//	3 <= (7/2)     → true
//	3 >= (8/2)     → false
//////////////////////////////////////////////////////////////////////////
	
	BOOST_AUTO_TEST_SUITE(has_comparison_operators)
		BOOST_AUTO_TEST_CASE(less_than)
		{
			BOOST_CHECK(CRational(1, 2) < 7);
			BOOST_CHECK(CRational(-1, 2) < 0);
			BOOST_CHECK(0 < CRational(1, 2));
			BOOST_CHECK(!(CRational(1, 2) < 0));
			BOOST_CHECK(!(CRational(1, 2) < CRational(1, 2)));
			BOOST_CHECK(CRational(1, 3) < CRational(1, 2));
			BOOST_CHECK(CRational(-1, 2) < CRational(1, 2));
		}

		BOOST_AUTO_TEST_CASE(greater_than)
		{
			BOOST_CHECK(CRational(3, 1) > 2);
			BOOST_CHECK(CRational(3, 1) > 0);
			BOOST_CHECK(0 > CRational(-1, 2));
			BOOST_CHECK(!(CRational(-1, 2) > 0));
			BOOST_CHECK(CRational(1, 2) > CRational(-1, 2));
			BOOST_CHECK(!(CRational(1, 2) > CRational(1, 2)));
			BOOST_CHECK(!(CRational(1, 3) > CRational(1, 2)));
			BOOST_CHECK(!(CRational(-6, 2) > CRational(-2, 1)));
		}

		BOOST_AUTO_TEST_CASE(less_than_or_equal)
		{
			BOOST_CHECK(3 <= CRational(7, 2));
			BOOST_CHECK(!(CRational(1, 2) <= CRational(1, 3)));
			BOOST_CHECK(CRational(7, 2) <= CRational(7, 2));
			BOOST_CHECK(CRational(7, 3) <= CRational(7, 2));
			BOOST_CHECK(CRational(1, 2) <= 1);
			BOOST_CHECK(0 <= CRational(1, 2));
			BOOST_CHECK(CRational(-1, 2) <= CRational(-1, 3));
		}

		BOOST_AUTO_TEST_CASE(greater_than_or_equal)
		{
			BOOST_CHECK(CRational(1, 2) >= CRational(1, 3));
			BOOST_CHECK(!(3 >= CRational(8, 2)));
			BOOST_CHECK(CRational(1, 2) >= CRational(1, 3));
			BOOST_CHECK(CRational(7, 2) >= CRational(7, 2));
			BOOST_CHECK(CRational(1, 2) >= 0);
			BOOST_CHECK(1 >= CRational(1, 2));
			BOOST_CHECK(CRational(-1, 3) >= CRational(-1, 2));
		}
	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//	std::ostream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(can_be_printed_to_ostream)
	{
		{
			std::ostringstream output;
			output << CRational(7, 15);
			BOOST_CHECK_EQUAL(output.str(), "7/15");
		}

		{
			std::ostringstream output;
			output << "Lorem ipsum " << CRational(-1, 2) << " dolor sit amet";
			BOOST_CHECK_EQUAL(output.str(), "Lorem ipsum -1/2 dolor sit amet");
		}

		{
			std::ostringstream output;
			output << CRational(3);
			BOOST_CHECK_EQUAL(output.str(), "3/1");
		}
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//	std::istream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(can_be_read_from_istream)
	{
		VerifyInputOperator("7/15", CRational(7, 15));
		VerifyInputOperator("-1/1", CRational(-1, 1));
		VerifyInputOperator("0", CRational(0, 1));
		VerifyInputOperator("7.15", boost::none);
	}

	// Реализовать возможность получения смешанной дроби из рационального числа
	BOOST_AUTO_TEST_CASE(can_be_converted_to_compound_fraction)
	{
		{
			auto rational = CRational(9, 4);
			VerifyCompoundFraction(rational, 2, 1, 4);
		}
		{
			auto rational = CRational(-9, 4);
			VerifyCompoundFraction(rational, -2, -1, 4);
		}
		{
			auto rational = CRational(-9);
			VerifyCompoundFraction(rational, -9, 0, 1);
		}
		{
			auto rational = CRational(1, 2);
			VerifyCompoundFraction(rational, 0, 1, 2);
		}
	}

BOOST_AUTO_TEST_SUITE_END()
