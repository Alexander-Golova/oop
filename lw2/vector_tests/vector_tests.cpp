#include "pch.h"

#include "../vector/vector_utils.h"

// Получение элементов вектора
TEST_CASE("Getting vector elements")
{
	std::istringstream inputStream;
	//Не пустая строка
	{
		inputStream.str("2.5 4 3 -4.5 18.37 22");
		auto numbers = GetNumbers(inputStream);
		const std::vector<double> correctVec = { 2.5, 4, 3, -4.5, 18.37, 22 };
		CHECK(numbers == correctVec);
	}

	// Пустая строка
	{
		inputStream.str("");
		auto numbers = GetNumbers(inputStream);
		const std::vector<double> correctVec = {};
		CHECK(numbers == correctVec);
	}
}

// Печать вектора
TEST_CASE("Printing vector")
{
	std::stringstream buffer;
	std::string str;
	{
		std::vector<double> numbers = { 2.5, 3.14, 7, 8, -19, 15 };
		PrintVector(buffer, numbers);
		std::getline(buffer, str);
		CHECK(str == "2.500 3.140 7.000 8.000 -19.000 15.000 ");
	}

	{
		std::vector<double> numbers = {};
		PrintVector(buffer, numbers);
		std::getline(buffer, str);
		CHECK(str == "");
	}
}

// Обработка вектора
TEST_CASE("Vector processing")
{
	{
		std::vector<double> numbers = { 10, 6, 2, 100, 26 };
		VectorConversion(numbers);
		const std::vector<double> correctVec = { 500, 300, 100, 5000, 1300 };
		CHECK(numbers == correctVec);
	}

	{
		std::vector<double> numbers = { 10, 6, -2, 100, 26 };
		VectorConversion(numbers);
		const std::vector<double> correctVec = { -500, -300, 100, -5000, -1300 };
		CHECK(numbers == correctVec);
	}

	{
		std::vector<double> numbers = { 10, 6, 0, 100, 26 };
		VectorConversion(numbers);
		const std::vector<double> correctVec = { 10, 6, 0, 100, 26 };
		CHECK(numbers == correctVec);
	}

	{
		std::vector<double> numbers = {};
		VectorConversion(numbers);
		const std::vector<double> correctVec = {};
		CHECK(numbers == correctVec);
	}
}
