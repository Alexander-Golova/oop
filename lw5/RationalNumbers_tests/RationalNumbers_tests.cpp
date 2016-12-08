#include "stdafx.h"
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

BOOST_AUTO_TEST_CASE(unary_minus_returns_rational_integer_with_opposite_sign)
{
	VerifyRational(-CRational(2, 3), -2, 3);
	VerifyRational(-CRational(-2, 3), 2, 3);
	VerifyRational(-CRational(-2, -3), -2, 3);
}

BOOST_AUTO_TEST_CASE(unary_plus_returns_rational_integer_equal_to_current)
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

	struct binary_addition_
	{
		CRational rational = CRational(1, 2);
	};	
	BOOST_FIXTURE_TEST_SUITE(counts_binary_addition_of, binary_addition_)
		
		BOOST_AUTO_TEST_CASE(two_rational_numbers)
		{
			auto answer = rational + CRational(5, 6);
			VerifyRational(answer, 4, 3);
		}	
		BOOST_AUTO_TEST_CASE(rational_and_integer_numbers)
		{
			auto answer = rational + 1;
			VerifyRational(answer, 3, 2);
		}	
		BOOST_AUTO_TEST_CASE(integer_and_rational_numbers)
		{
			auto answer = 1 + rational;
			VerifyRational(answer, 3, 2);
		}
		
	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
// Возвращает разность двух рациональных чисел, 
//	рационального числа и целого, либо целого числа и рационального:
//	(1/2) - (1/6) = (1/3)
//	(1/2) - 1     = (-1/2)
//	1 - (1/2)     = (1/2)
//////////////////////////////////////////////////////////////////////////

	struct binary_subtraction_
	{
		CRational rational = CRational(1, 2);
	};
	BOOST_FIXTURE_TEST_SUITE(counts_binary_subtraction_of, binary_subtraction_)

		BOOST_AUTO_TEST_CASE(two_rational_numbers)
		{
			auto answer = rational - CRational(1, 6);
			VerifyRational(answer, 1, 3);
		}
		BOOST_AUTO_TEST_CASE(rational_and_integer_numbers)
		{
			auto answer = rational - 1;
			VerifyRational(answer, -1, 2);
		}
		BOOST_AUTO_TEST_CASE(integer_and_rational_numbers)
		{
			auto answer = 1 - rational;
			VerifyRational(answer, 1, 2);
		}

	BOOST_AUTO_TEST_SUITE_END()



//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
// Выполняет увеличение рационального числа на величину второго рационального,
//	либо целого числа:
//	(1/2) += (1/6)  → (2/3)
//	(1/2) += 1      → (3/2)
//////////////////////////////////////////////////////////////////////////

	struct addition_
	{
		CRational rational = CRational(1, 2);
	};
	BOOST_FIXTURE_TEST_SUITE(counts_addition_a, addition_)

		BOOST_AUTO_TEST_CASE(rational_number)
		{
			rational += CRational(1, 6);
			VerifyRational(rational, 2, 3);
		}
		BOOST_AUTO_TEST_CASE(integer_number)
		{
			rational += 1;
			VerifyRational(rational, 3, 2);
		}

	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
// Выполняет уменьшение рационального числа на величину второго рационального либо целого числа :
// (1/2) -= (1/6)  → (1/3)
// (1/2) -= 1      → (-1/2)
//////////////////////////////////////////////////////////////////////////

	struct subtraction_
	{
		CRational rational = CRational(1, 2);
	};
	BOOST_FIXTURE_TEST_SUITE(counts_subtraction_a, subtraction_)

		BOOST_AUTO_TEST_CASE(rational_number)
		{
			rational -= CRational(1, 6);
			VerifyRational(rational, 1, 3);
		}
		BOOST_AUTO_TEST_CASE(subtraction_integer_number)
		{
			rational -= 1;
			VerifyRational(rational, -1, 2);
		}

	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
// Возвращает результат произведения рациональных чисел, 
//	рационального и целого, либо целого и рационального :
//	(1/2) * (2/3) = (1/3)
//	(1/2) * (-3)  = (-3/2)
//	7 * (2/3)     = (14/3)
//////////////////////////////////////////////////////////////////////////
	struct bi_multiplication_
	{
		CRational rational = CRational(1, 2);
	};
	BOOST_FIXTURE_TEST_SUITE(counts_binary_multiplication_of, bi_multiplication_)

		BOOST_AUTO_TEST_CASE(rational_integers)
		{
			auto answer = rational * CRational(2, 3);
			VerifyRational(answer, 1, 3);
		}
		BOOST_AUTO_TEST_CASE(rational_and_integer)
		{
			auto answer = rational * CRational(-3);
			VerifyRational(answer, -3, 2);
		}
		BOOST_AUTO_TEST_CASE(integer_and_rational)
		{
			auto answer = CRational(14) * rational;
			VerifyRational(answer, 7, 1);
		}

	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
// Возвращает частное двух рациональных чисел, 
//	рационального и целого, целого и рационального :
//	(1/2) ⁄ (2/3) = (3/4)
//	(1/2) ⁄ 5     = (1/10)
//	7 ⁄ (2/3)     = (21/2)
//////////////////////////////////////////////////////////////////////////
	struct bi_division_
	{
		CRational rational = CRational(1, 2);
	};
	BOOST_FIXTURE_TEST_SUITE(binary_division_of, bi_division_)

		BOOST_AUTO_TEST_CASE(rational_numbers)
		{
			auto answer = rational / CRational(2, 3);
			VerifyRational(answer, 3, 4);
		}
		BOOST_AUTO_TEST_CASE(rational_and_integer_numbers)
		{
			auto answer = rational / CRational(5);
			VerifyRational(answer, 1, 10);
		}
		BOOST_AUTO_TEST_CASE(integer_and_rational_numbers)
		{
			auto answer = CRational(7) / rational;
			VerifyRational(answer, 14, 1);
		}
		BOOST_AUTO_TEST_CASE(rational_and_zero_as_exeption)
		{
			BOOST_REQUIRE_THROW(auto answer = rational / CRational(0), std::invalid_argument::exception);
			BOOST_REQUIRE_THROW(auto answer = rational / CRational(0, 1), std::invalid_argument::exception);
		}

	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
// Умножает значение первого рационального числа на другое рациональное, 
//	либо целое:
//	(1/2) *= (2/3) → (1/3)
//	(1/2) *= 3     → (3/2)
//////////////////////////////////////////////////////////////////////////

	struct multiplication_
	{
		CRational rational = CRational(1, 2);
	};
	BOOST_FIXTURE_TEST_SUITE(counts_multiplication_a, multiplication_)

		BOOST_AUTO_TEST_CASE(rational_number)
		{
			rational *= CRational(2, 3);
			VerifyRational(rational, 1, 3);
		}
		BOOST_AUTO_TEST_CASE(integer_number)
		{
			rational *= 3;
			VerifyRational(rational, 3, 2);
		}

	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
// Делит первое рациональное число на другое рациональное, 
//	либо целое:
//	(1/2) /= (2/3) → (3/4)
//	(3/4) /= (3/8) → (2/1)
//	(1/2) /= 3     → (1/6)
//////////////////////////////////////////////////////////////////////////

	struct division_
	{
		CRational rational = CRational(1, 2);
	};
	BOOST_FIXTURE_TEST_SUITE(counst_division_a, division_)

		BOOST_AUTO_TEST_CASE(rational_number)
		{
			rational /= CRational(2, 3);
			VerifyRational(rational, 3, 4);
		}
		BOOST_AUTO_TEST_CASE(integer_number)
		{
			rational /= 3;
			VerifyRational(rational, 1, 6);
		}
		BOOST_AUTO_TEST_CASE(rational_and_zero_throw_exeption)
		{
			BOOST_REQUIRE_THROW(rational /= CRational(0), std::invalid_argument);
			BOOST_REQUIRE_THROW(rational /= CRational(0, 1), std::invalid_argument);
		}

	BOOST_AUTO_TEST_SUITE_END()

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

	struct equality_
	{
		CRational rational = CRational(1, 2);
	};
	BOOST_FIXTURE_TEST_SUITE(checks_equality_of, equality_)

		BOOST_AUTO_TEST_CASE(rational_numbers)
		{
			BOOST_CHECK(rational == CRational(1, 2));
			BOOST_CHECK(!(rational == CRational(2, 3)));
		}
		BOOST_AUTO_TEST_CASE(rational_and_integer_numbers)
		{
			BOOST_CHECK(!(rational == CRational(7)));
		}
		BOOST_AUTO_TEST_CASE(integer_and_rational_numbers)
		{
			BOOST_CHECK(CRational(3) == CRational(3, 1));
		}
		BOOST_AUTO_TEST_CASE(integer_and_integer_numbers)
		{
			BOOST_CHECK(CRational(4, 1) == CRational(4));
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct inequality_
	{
		CRational rational = CRational(1, 2);
	};
	BOOST_FIXTURE_TEST_SUITE(checks_inequality_of, inequality_)

		BOOST_AUTO_TEST_CASE(rational_numbers)
		{
			BOOST_CHECK(!(rational != CRational(1, 2)));
			BOOST_CHECK(rational != CRational(2, 3));
		}
		BOOST_AUTO_TEST_CASE(rational_and_integer_numbers)
		{
			BOOST_CHECK(rational != CRational(7));
		}
		BOOST_AUTO_TEST_CASE(integer_and_rational_numbers)
		{
			BOOST_CHECK(!(CRational(3) != CRational(3, 1)));
		}
		BOOST_AUTO_TEST_CASE(integer_and_integer_numbers)
		{
			BOOST_CHECK(!(CRational(4, 1) != CRational(4)));
		}

	BOOST_AUTO_TEST_SUITE_END()

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
	
	struct less_
	{
		CRational rational = CRational(1, 2);
	};
	BOOST_FIXTURE_TEST_SUITE(checks_less_of, less_)

		BOOST_AUTO_TEST_CASE(rational_numbers)
		{
			BOOST_CHECK(!(rational < CRational(1, 2)));
			BOOST_CHECK(!(CRational(2, 3) < rational));
		}
		BOOST_AUTO_TEST_CASE(rational_and_integer_numbers)
		{
			BOOST_CHECK(rational < CRational(7));
		}
		BOOST_AUTO_TEST_CASE(integer_and_rational_numbers)
		{
			BOOST_CHECK(!(CRational(3) < CRational(3, 1)));
		}
		BOOST_AUTO_TEST_CASE(integer_and_integer_numbers)
		{
			BOOST_CHECK(!(CRational(4, 1) < CRational(4)));
		}

		BOOST_AUTO_TEST_SUITE_END()

	struct less_or_equality_
	{
		CRational rational = CRational(1, 2);
	};
	BOOST_FIXTURE_TEST_SUITE(сhecks_less_or_equality_of, less_or_equality_)

		BOOST_AUTO_TEST_CASE(rational_numbers)
		{
			BOOST_CHECK((rational <= CRational(1, 2)));
			BOOST_CHECK(!(CRational(2, 3) <= rational));
		}
		BOOST_AUTO_TEST_CASE(rational_and_integer_numbers)
		{
			BOOST_CHECK(rational <= CRational(7));
		}
		BOOST_AUTO_TEST_CASE(integer_and_rational_numbers)
		{
			BOOST_CHECK(CRational(3) <= CRational(3, 1));
		}
		BOOST_AUTO_TEST_CASE(integer_and_integer_numbers)
		{
			BOOST_CHECK(CRational(4, 1) <= CRational(4));
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct larger_
	{
		CRational rational = CRational(1, 2);
	};
	BOOST_FIXTURE_TEST_SUITE(checks_larger_of, larger_)

		BOOST_AUTO_TEST_CASE(rational_numbers)
		{
			BOOST_CHECK(!(rational > CRational(1, 2)));
			BOOST_CHECK((CRational(2, 3) > rational));
		}
		BOOST_AUTO_TEST_CASE(rational_and_integer_numbers)
		{
			BOOST_CHECK(!(rational > CRational(7)));
		}
		BOOST_AUTO_TEST_CASE(integer_and_rational_numbers)
		{
			BOOST_CHECK(!(CRational(3) > CRational(3, 1)));
		}
		BOOST_AUTO_TEST_CASE(larger_two_integers)
		{
			BOOST_CHECK((CRational(4, 1) > CRational(3)));
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct larger_or_equality_
	{
		CRational rational = CRational(1, 2);
	};
	BOOST_FIXTURE_TEST_SUITE(checks_larger_or_equality_of, larger_or_equality_)

		BOOST_AUTO_TEST_CASE(rational_numbers)
		{
			BOOST_CHECK((rational >= CRational(1, 2)));
			BOOST_CHECK((CRational(2, 3) >= rational));
		}
		BOOST_AUTO_TEST_CASE(rational_and_integer_numbers)
		{
			BOOST_CHECK(!(rational >= CRational(7)));
		}
		BOOST_AUTO_TEST_CASE(integer_and_rational_numbers)
		{
			BOOST_CHECK(CRational(3) >= CRational(3, 1));
		}
		BOOST_AUTO_TEST_CASE(integer_and_integer_numbers)
		{
			BOOST_CHECK(CRational(4, 1) >= CRational(4));
		}

	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//	std::ostream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////

	struct ostream_
	{
		CRational rational = CRational(7, 15);
	};
	BOOST_FIXTURE_TEST_SUITE(can_outputs_to_ostream_a, ostream_)

		BOOST_AUTO_TEST_CASE(rational_numbrs)
		{
			std::ostringstream strm;
			strm << rational;
			BOOST_CHECK_EQUAL(strm.str(), "7/15");
		}

	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//	std::istream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////
	struct istream_
	{
		CRational rational;
	};
	BOOST_FIXTURE_TEST_SUITE(can_read_from_istream_a, istream_)

		BOOST_AUTO_TEST_CASE(rational_numbers)
		{
			std::istringstream strm("7/15");
			strm >> rational;
			VerifyRational(rational, 7, 15);
		}
		BOOST_AUTO_TEST_CASE(negative_rational_numbers)
		{
			std::istringstream strm("-7/15");
			strm >> rational;
			VerifyRational(rational, -7, 15);
		}

	BOOST_AUTO_TEST_SUITE_END()

	// Реализовать возможность получения смешанной дроби из рационального числа
	BOOST_AUTO_TEST_CASE(can_get_compound_fraction)
	{
		auto rational = CRational(9, 4);
		VerifyCompoundFraction(rational, 2, 1, 4);
	}
	BOOST_AUTO_TEST_CASE(can_get_compound_negative_fraction)
	{
		auto rational = CRational(-9, 4);
		VerifyCompoundFraction(rational, -2, -1, 4);
	}
	BOOST_AUTO_TEST_CASE(integer_will_return_to_previous_state)
	{
		auto rational = CRational(-9);
		VerifyCompoundFraction(rational, -9, 0, 1);
	}
	BOOST_AUTO_TEST_CASE(if_fraction_is_less_than_zero_then_integer_equal_to_zero)
	{
		auto rational = CRational(1, 2);
		VerifyCompoundFraction(rational, 0, 1, 2);
	}

BOOST_AUTO_TEST_SUITE_END()
