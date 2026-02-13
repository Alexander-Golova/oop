#include <iostream>
#include <vector>
#include <set>

#include "primesUtilites.h"


int main(int argc, char* argv[])
{
	if (!CheckArgumentCount(argc) || !IsNumber(argv[1]))
	{
		return 1;
	}

	const std::string upperBound = argv[1];

	std::set<size_t> primes = GeneratePrimeNumbersSet(atoi(upperBound.c_str()));

	for (auto pr : primes)
	{
		std::cout << pr << " ";
	}

    std::cout << std::endl;
}