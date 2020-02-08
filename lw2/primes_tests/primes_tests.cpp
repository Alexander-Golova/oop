#include "pch.h"
#include "../primes/primes_utils.h"

TEST_CASE("primes count")
{
	{
		const auto expectedResult = 0;
		auto primes = GeneratePrimeNumbersSet(0);
		CHECK(primes.size() == expectedResult);
	}

	{
		const auto expectedResult = 0;
		auto primes = GeneratePrimeNumbersSet(1);
		CHECK(primes.size() == expectedResult);
	}

	{
		const auto expectedResult = 1;
		auto primes = GeneratePrimeNumbersSet(2);
		CHECK(primes.size() == expectedResult);
	}

	{
		const auto expectedResult = 8;
		auto primes = GeneratePrimeNumbersSet(20);
		CHECK(primes.size() == expectedResult);
	}

#ifdef NDEBUG
	{
		const auto expectedResult = 5761455;
		auto primes = GeneratePrimeNumbersSet(100000000);
		CHECK(primes.size() == expectedResult);
	}
#endif
}


TEST_CASE("compare sets")
{
	{
		const std::set<size_t> expectedResult = { 2 };
		const auto primes = GeneratePrimeNumbersSet(2);
		CHECK(primes == expectedResult);
	}

	{
		const std::set<size_t> expectedResult = { 2, 3 };
		const auto primes = GeneratePrimeNumbersSet(3);
		CHECK(primes == expectedResult);
	}

	{
		const std::set<size_t> expectedResult = {
			2, 3, 5, 7, 11, 13, 17, 19
		};
		const auto primes = GeneratePrimeNumbersSet(20);
		CHECK(primes == expectedResult);
	}

	{
		const std::set<size_t> expectedResult = {};
		const auto primes = GeneratePrimeNumbersSet(1);
		CHECK(primes == expectedResult);
	}
}
