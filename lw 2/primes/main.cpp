#include "stdafx.h"

#include "primes_utils.h"

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cerr << "Invalid params. Use this:" << endl;
		cerr << "prime <upperBound>" << endl;
		return 1;
	}

	const string upperBound = argv[1];
	if (!IsNumber(upperBound))
	{
		cerr << "<upperBound> must be unsigned integer" << endl;
		return 1;
	}

	auto primes = GeneratePrimeNumbersSet(atoi(upperBound.c_str()));

	for (const auto prime : primes)
	{
		//cout << prime << endl;
	}
	
    return 0;
}
