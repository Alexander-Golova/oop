#include "stdafx.h"

int main(int, char * [])
{
	std::vector<double> numbers(std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()));
	
	std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<double>(std::cout, " "));
	
	auto min = *std::min_element(numbers.begin(), numbers.end());


	std::cout << std::endl << std::fixed << std::setprecision(3) << min << std::endl;

	std::sort(numbers.begin(), numbers.end(), [](double a, double b) {
		return a < b;
	});



	return 0;
}
