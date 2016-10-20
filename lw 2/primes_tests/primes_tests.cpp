#include "stdafx.h"

#include "../primes/primes_utils.cpp"

BOOST_AUTO_TEST_SUITE(Test)

BOOST_AUTO_TEST_CASE(primes_count)
{
	{
		const auto expectedResult = 0;
		auto primes = GeneratePrimeNumbersSet(0);
		BOOST_CHECK(primes.size() == expectedResult);
	}

	{
		const auto expectedResult = 0;
		auto primes = GeneratePrimeNumbersSet(1);
		BOOST_CHECK(primes.size() == expectedResult);
	}

	{
		const auto expectedResult = 1;
		auto primes = GeneratePrimeNumbersSet(2);
		BOOST_CHECK(primes.size() == expectedResult);
	}

	{
		const auto expectedResult = 8;
		auto primes = GeneratePrimeNumbersSet(20);
		BOOST_CHECK(primes.size() == expectedResult);
	}

#ifdef NDEBUG
	{
		const auto expectedResult = 5761455;
		auto primes = GeneratePrimeNumbersSet(100000000);
		BOOST_CHECK(primes.size() == expectedResult);
	}
#endif
}

BOOST_AUTO_TEST_CASE(compare_sets)
{
	{
		const set<unsigned> expectedResult = { 2 };
		const auto primes = GeneratePrimeNumbersSet(2);
		BOOST_CHECK(primes == expectedResult);
	}

	{
		const set<unsigned> expectedResult = { 2, 3 };
		const auto primes = GeneratePrimeNumbersSet(3);
		BOOST_CHECK(primes == expectedResult);
	}

	{
		const set<unsigned> expectedResult = {
			2, 3, 5, 7, 11, 13, 17, 19
		};
		const auto primes = GeneratePrimeNumbersSet(20);
		BOOST_CHECK(primes == expectedResult);
	}

	{
		const set<unsigned> expectedResult = {};
		const auto primes = GeneratePrimeNumbersSet(1);
		BOOST_CHECK(primes == expectedResult);
	}
}

BOOST_AUTO_TEST_SUITE_END()