#include "stdafx.h"

#include "primes_utils.h"

int main(int argc, char * argv[])
{
	if (!CheckArgumentCount(argc) || !IsNumber(argv[1]))
	{
		return 1;
	}

	const string upperBound = argv[1];
	auto primes = GeneratePrimeNumbersSet(atoi(upperBound.c_str()));

	for (const auto prime : primes)
	{
		cout << prime << endl;
	}
	
    return 0;
}
