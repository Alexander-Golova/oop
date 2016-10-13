#include "stdafx.h"

#include "../vector/vector_utils.h"

BOOST_AUTO_TEST_SUITE(Test)

BOOST_AUTO_TEST_CASE(Find_max)
{
	{
		const double expectedResult = 4;
		BOOST_CHECK(max({ 2.5, 4, 3, -4.5 }) == expectedResult);
	}
}

BOOST_AUTO_TEST_CASE(Find_min)
{
	{
		const double expectedResult = -4.5;
		BOOST_CHECK(min({ 2.5, 4, 3, -4.5 }) == expectedResult);
	}
}

BOOST_AUTO_TEST_CASE(Getting_numbers)
{
	{
		std::stringstream str("2.5 4 3 -4.5 18.37 22");
		auto numbers = GetNumbers(str);
		const std::vector<double> correctVec = {
			2.5, 4, 3, -4.5, 18.37, 22
		};
		BOOST_CHECK(numbers == correctVec);
	}
	{
		std::stringstream str("");
		auto numbers = GetNumbers(str);
		const std::vector<double> correctVec = {};
		BOOST_CHECK(numbers == correctVec);
	}
}

BOOST_AUTO_TEST_CASE(Printing_vector)
{
	{
		std::stringstream buffer;
		std::vector<double> numbers = {
			2.5, 3.14, 7, 8, -19, 15
		};
		PrintVector(buffer, numbers);
		std::string str;
		std::getline(buffer, str);
		BOOST_CHECK(str == "2.500 3.140 7.000 8.000 -19.000 15.000 ");
	}
}

BOOST_AUTO_TEST_CASE(Vector_processing)
{
	{
		std::vector<double> numbers = {
			10, 6, 2, 100, 26
		};
		vector—onversion(numbers);
		const std::vector<double> correctVec = {
			500, 300, 100, 5000, 1300
		};
		BOOST_CHECK(numbers == correctVec);
	}
	{
		std::vector<double> numbers = {
			10, 6, -2, 100, 26
		};
		vector—onversion(numbers);
		const std::vector<double> correctVec = {
			-500, -300, 100, -5000, -1300
		};
		BOOST_CHECK(numbers == correctVec);
	}
}
BOOST_AUTO_TEST_SUITE_END()
