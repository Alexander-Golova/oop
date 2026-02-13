#include "primesUtilites.h"



std::set<size_t> GeneratePrimeNumbersSet(const size_t upperBound)
{
	std::vector<bool> isPrimes(upperBound + 1, true);

	for (size_t i = 3; i * i < upperBound + 1; i++)
	{
		for (size_t j = i * i; j < upperBound + 1; j = j + 2 * i)
		{
			isPrimes[j] = false;
		}
	}

	std::set<size_t> primes;
	primes.emplace_hint(primes.end(), 2);

	for (size_t i = 3; i < upperBound + 1; i = i + 2)
	{
		if (isPrimes[i])
		{
			primes.emplace_hint(primes.end(), i);
		}
	}
	return primes;
}

bool CheckArgumentCount(const int argumentCount)
{
	if (argumentCount != 2)
	{
		std::cerr << "Invalid params. Use this:" << std::endl;
		std::cerr << "prime <upperBound>" << std::endl;
		return false;
	}
	return true;
}

bool IsNumber(const std::string& str)
{
	return std::all_of(str.begin(), str.end(), isdigit);
}
