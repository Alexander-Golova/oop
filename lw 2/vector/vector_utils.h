#pragma once

#include "stdafx.h"

using namespace std;

void PrintVector(ostream & output, const vector<double> & numbers)
{
	for (const auto & element : numbers)
	{
		output << fixed << setprecision(3) << element << " ";
	}
	output << endl;
}

vector<double> GetNumbers(istream & input)
{
	return{ istream_iterator<double>(input), istream_iterator<double>() };
}

void VectorÑonversion(vector<double> & numbers)
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