#include "pch.h"

#include "vector_utils.h"

void PrintVector(std::ostream& output, const std::vector<double>& numbers)
{
	for (const auto& element : numbers)
	{
		output << std::fixed << std::setprecision(3) << element << " ";
	}
	output << std::endl;
}

std::vector<double> GetNumbers(std::istream& input)
{
	return { std::istream_iterator<double>(input), std::istream_iterator<double>() };
}

void VectorConversion(std::vector<double>& numbers)
{
	if (numbers.empty())
	{
		return;
	}

	double min = *min_element(numbers.begin(), numbers.end());
	if (min == 0)
	{
		return;
	}

	double multiplier = *max_element(numbers.begin(), numbers.end()) / min;
	transform(numbers.begin(), numbers.end(), numbers.begin(), [=](double element) {
		return element * multiplier;
	});
}
