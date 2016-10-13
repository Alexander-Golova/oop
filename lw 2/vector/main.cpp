#include "stdafx.h"
#include "vector_utils.h"

int main(int, char * [])
{
	std::vector<double> numbers = GetNumbers(std::cin);

	vectorÑonversion(numbers);

	std::sort(numbers.begin(), numbers.end(), [](double a, double b) {
		return a < b;
	});

	PrintVector(std::cout, numbers);

	return 0;
}
