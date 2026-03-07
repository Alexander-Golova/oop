#include "PrimesUtils.h"
#include <iostream>

int main(int argc, char* argv[])
{
	if (!CheckArgumentCount(argc))
	{
		return 1;
	}

	if (!IsNumber(argv[1]))
	{
		std::cerr << "Invalid <upperBound>. Use this:" << std::endl;
		std::cerr << "<upperBound> - positive integer " << std::endl;
		return 1;
	}

	const std::string upperBound = argv[1];
	auto primes = GeneratePrimeNumbersSet(atoi(upperBound.c_str()));

	for (const auto prime : primes)
	{
		std::cout << prime << std::endl;
	}

	return 0;
}
