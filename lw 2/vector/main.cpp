#include "stdafx.h"
#include "vector_utils.h"


int main(int, char * [])
{
	vector<double> numbers = GetNumbers(std::cin);

	VectorÑonversion(numbers);

	sort(numbers.begin(), numbers.end(), [](double a, double b) {
		return a < b;
	});

	PrintVector(cout, numbers);

	return 0;
}
