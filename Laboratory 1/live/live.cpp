#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <array>
#include <cmath>
#include <cctype> 
#include <sstream>

const unsigned dim = 6;

typedef std::array<std::array<char, dim>, dim> Matrix;

Matrix GetNullMatrix()
{
	Matrix nullMatrix;
	for (size_t row = 0; row < dim; ++row)
	{
		for (size_t col = 0; col < dim; ++col)
		{
			nullMatrix[row][col] = ' ';
		}
	}
	return nullMatrix;
}

void PrintMatrix(const Matrix & sourceMatrix)
{
	for (size_t row = 0; row < dim; ++row)
	{
		for (size_t col = 0; col < dim; ++col)
		{
			std::cout << sourceMatrix[row][col];
		}
		std::cout << std::endl;
	}
}

/*
Matrix GetMatrixFromFile(std::ifstream & input, bool & error)
{
	Matrix initialMatrix = GetNullMatrix();
	size_t row = 0;
	for (std::string line; getline(input, line) && row < dim; ++row)
	{
		std::istringstream coeffs(line);
		for (size_t col = 0; col < dim; ++col)
		{
			if (!(coeffs >> initialMatrix[row][col]))
			{
				error = true;
				return initialMatrix;
			}
		}
	}
	if (row < 3)
	{
		error = true;
	}
	return initialMatrix;
}
*/

int main(int argc, char * argv[])
{
	if (argc != 2 && argc != 3)
	{
		std::cerr << "Invalid arguments count" << std::endl
			<< "Usage: life <input file> [<output file>]" << std::endl;
		return 1;
	}

	std::ifstream input(argv[1]);
	if (!input.is_open())
	{
		std::cerr << "Failed to open " << argv[1] << " for reading" << std::endl;
		return 1;
	}

	Matrix firstGeneration;
	Matrix nextGeneration;

	PrintMatrix(GetNullMatrix());
	/*bool error = false;

	
	if (error)
	{
		std::cerr << "The array is defined correctly" << std::endl;
		return 1;
	}

	*/

	//PrintMatrix(nextGeneration);
	
}