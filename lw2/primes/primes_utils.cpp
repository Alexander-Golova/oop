#include "pch.h"
#include "primes_utils.h"

using namespace std;

bool CheckArgumentCount(const int argumentCount)
{
	if (argumentCount != 2)
	{
		cerr << "Invalid params. Use this:" << endl;
		cerr << "prime <upperBound>" << endl;
		return false;
	}
	return true;
}

bool IsNumber(const string& str)
{
	return all_of(str.begin(), str.end(), isdigit);
}

set<uint32_t> GeneratePrimeNumbersSet(const unsigned upperBound)
{
	vector<bool> isPrimes(upperBound + 1, true);

	for (uint32_t i = 3; i * i <= upperBound; i += 2)
	{
		if (isPrimes[i])
		{
			for (uint32_t j = i * i; j <= upperBound; j += i)
			{
				isPrimes[j] = false;
			}
		}
	}

	set<uint32_t> primes;
	if (upperBound >= 2)
	{
		primes.insert(2);
		for (uint32_t i = 3; i <= upperBound; i += 2)
		{
			if (isPrimes[i])
			{
				primes.emplace_hint(primes.end(), i);
			}
		}
	}

	return primes;
}