#include "stdafx.h"

#include "primes_utils.h"

bool IsNumber(const string & str)
{
	return all_of(str.begin(), str.end(), isdigit);
}

set<unsigned> GeneratePrimeNumbersSet(const unsigned upperBound)
{
	vector<bool> isPrimes(upperBound + 1, true);

	for (unsigned i = 3; i * i <= upperBound; i += 2)
	{
		if (isPrimes[i])
		{
			for (unsigned j = i * i; j <= upperBound; j += i)
			{
				isPrimes[j] = false;
			}
		}
	}

	set<unsigned> primes;
	if (upperBound >= 2)
	{
		primes.insert(2);
		for (unsigned i = 3; i <= upperBound; i += 2)
		{
			if (isPrimes[i])
			{
				primes.emplace_hint(primes.end(), i);
			}
		}
	}

	return primes;
}