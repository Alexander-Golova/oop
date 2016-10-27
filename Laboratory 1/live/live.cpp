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

void PrintMatrix(std::ostream & output, const Matrix & sourceMatrix, size_t & maxRow, size_t & maxCol)
{
	for (size_t row = 0; row < maxRow; ++row)
	{
		for (size_t col = 0; col < maxCol; ++col)
		{
			output << sourceMatrix[row][col];
		}
		output << std::endl;
	}
}

Matrix GetMatrixFromFile(std::istream & input, size_t & maxRow, size_t & maxCol, bool & error)
{
	Matrix initialMatrix = GetNullMatrix();
	size_t row = 0;
	for (std::string line; getline(input, line) && row < dim; ++row)
	{
		for (size_t col = 0; col < line.length(); ++col)
		{
			initialMatrix[row][col] = line[col];
			if (line[col] != ' ' && line[col] != '*' && line[col] != '#')
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
	if (maxRow > 256 || maxCol > 256)
	{
		error = true;
	}
	return initialMatrix;
}

size_t CalculateNeighbors(const Matrix & generation, size_t & row, size_t & col)
{
	size_t count = 0;
	for (size_t i = row - 1; i <= row + 1; ++i)
	{
		for (size_t j = col - 1; j <= col + 1; ++j)
		{
			if ((i != row || j != col) && generation[i][j] == '#')
			{
				++count;
			}
		}
	}
	return count;
}

Matrix ConstructionOfBorder(const Matrix & generation, const size_t & maxRow, const size_t & maxCol)
{
	Matrix borderMatrix = GetNullMatrix();
	for (size_t row = 0; row < maxRow; ++row)
	{
		for (size_t col = 0; col < maxCol; ++col)
		{
			if (generation[row][col] == '*')
			{
				borderMatrix[row][col] = '*';
			}
		}
	}
	return borderMatrix;
}

Matrix NextGeneration(const Matrix & generation, const size_t & maxRow, const size_t & maxCol)
{
	Matrix stateMatrix = ConstructionOfBorder(generation, maxRow, maxCol);
	for (size_t row = 1; row < maxRow - 1; ++row)
	{
		for (size_t col = 1; col < maxCol - 1; ++col)
		{
			if (generation[row][col] != '*')
			{
				if (CalculateNeighbors(generation, row, col) == 3)
				{
					stateMatrix[row][col] = '#';
				}
				if (CalculateNeighbors(generation, row, col) == 2 && generation[row][col] == '#')
				{
					stateMatrix[row][col] = '#';
				}
				if (CalculateNeighbors(generation, row, col) < 2 || CalculateNeighbors(generation, row, col) > 3)
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

	if (argc == 3)
	{
		std::ofstream output(argv[2]);
		if (!output.is_open())
		{
			std::cout << "Failed to open " << argv[2] << " for writing" << std::endl;
			return 1;
		}
		PrintMatrix(output, NextGeneration(firstGeneration, maxRow, maxCol), maxRow, maxCol);
	}
	else
	{
		PrintMatrix(std::cout, NextGeneration(firstGeneration, maxRow, maxCol), maxRow, maxCol);
	}
		
	return 0;
}