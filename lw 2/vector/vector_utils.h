#pragma once

#include "stdafx.h"

void PrintVector(std::ostream & output, const std::vector<double> & numbers)
{
	for (const auto & element : numbers)
	{
		output << std::fixed << std::setprecision(3) << element << " ";
	}
	output << std::endl;
}

std::vector<double> GetNumbers(std::istream & input)
{
	std::vector<double> sourceVector;
	std::copy(std::istream_iterator<double>(input), std::istream_iterator<double>(), std::back_inserter(sourceVector));
	return sourceVector;
}

double max(const std::vector<double> & numbers)
{
	return *std::max_element(numbers.begin(), numbers.end());
}

double min(const std::vector<double> & numbers)
{
	return *std::min_element(numbers.begin(), numbers.end());
}

void vectorÑonversion(std::vector<double> & numbers)
{
	if (numbers.empty())
	{
		return;
	}
	
	if (min(numbers) == 0)
	{
		return;
	}

	double multiplier = max(numbers) / min(numbers);
	std::transform(numbers.begin(), numbers.end(), numbers.begin(), [=](double element) {
		return element * multiplier;
	});

}