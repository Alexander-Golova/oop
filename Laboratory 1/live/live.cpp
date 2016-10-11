#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <array>
#include <cmath>
#include <cctype> 
#include <sstream>

const unsigned dim = 256;

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

Matrix GetMatrixFromFile(std::ifstream & input, size_t & maxRow, size_t & maxCol, bool & error)
{
	Matrix initialMatrix = GetNullMatrix();
	size_t row = 0;
	for (std::string line; getline(input, line) && row < dim; ++row)
	{
		for (size_t col = 0; col < line.length(); ++col)
		{
			initialMatrix[row][col] = line[col];
			if (line[col] != ' ' || line[col] != '*' || line[col] != '#')
			{
				error = true;
			}
		}
		if (line.length() > maxCol)
		{
			maxCol = line.length();
		}		
	}
	maxRow = row;
	return initialMatrix;
}

size_t numberOfNeighbors(const Matrix & generation, const size_t & row, const size_t & col)
{
	size_t count = 0;
	for (size_t i = row - 1; i < row + 1; ++i)
	{
		for (size_t j = col - 1; j < col + 1; ++j)
		{
			if (i != row && j != col && generation[i][j] == '#')
			{
				++count;
			}
		}
	}
	return count;
}

Matrix nextGeneration(const Matrix & generation)
{
	Matrix stateMatrix = GetNullMatrix();
	for (size_t row = 0; row < dim; ++row)
	{
		for (size_t col = 0; col < dim; ++col)
		{
			if (generation[row][col] == '*')
			{
				stateMatrix[row][col] = '*';
			}
		}
	}
	for (size_t row = 1; row < dim - 1; ++row)
	{
		for (size_t col = 1; col < dim - 1; ++col)
		{
			if (generation[row][col] != '*')
			{
				if (numberOfNeighbors(generation, row, col) == 3)
				{
					stateMatrix[row][col] = '#';
				}
				if (numberOfNeighbors(generation, row, col) == 2 && generation[row][col] == '#')
				{
					stateMatrix[row][col] = '#';
				}
				if (numberOfNeighbors(generation, row, col) < 2 || numberOfNeighbors(generation, row, col) > 3)
				{
					stateMatrix[row][col] = ' ';
				}
			}			
		}
	}
	return stateMatrix;
}


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
	bool error = false;
	size_t maxRow = 0;
	size_t maxCol = 0;
	firstGeneration = GetMatrixFromFile(input, maxRow, maxCol, error);
	if (error)
	{
		std::cerr << "The array is defined correctly" << std::endl;
		return 1;
	}
	std::cout << maxRow << std::endl;
	std::cout << maxCol << std::endl;
	PrintMatrix(nextGeneration(firstGeneration));
	return 0;
}