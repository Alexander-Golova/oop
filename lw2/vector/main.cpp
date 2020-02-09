#include "pch.h"

#include "vector_utils.h"

int main(int, char* [])
{
	std::vector<double> numbers = GetNumbers(std::cin);

	VectorConversion(numbers);

	sort(numbers.begin(), numbers.end());

	PrintVector(std::cout, numbers);

	return 0;
}
