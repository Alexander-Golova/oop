#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <array>
#include <cmath>
#include <cctype> 

const double eps = 10e-5;
const unsigned dim = 3;

typedef std::array<std::array<double, dim>, dim> matrix;

matrix GetNullMatrix(const unsigned & dim)
{
	matrix NullMatrix;
	for (unsigned i = 0; i < dim; ++i)
	{
		for (unsigned j = 0; j < dim; ++j)
		{
			NullMatrix[i][j] = 0;
		}
	}
	return NullMatrix;
}

matrix GetIdentityMatrix(const unsigned & dim)
{
	matrix IdentityMatrix = GetNullMatrix(dim);
	for (unsigned i = 0; i < dim; ++i)
	{
		IdentityMatrix[i][i] = 1;
	}
	return IdentityMatrix;
}

void PrintMatrix(const unsigned & dim, const matrix & initialMatrix)
{
	for (unsigned i = 0; i < dim; ++i)
	{
		for (unsigned j = 0; j < dim; ++j)
		{
			std::cout << std::fixed << std::setprecision(3) << initialMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

matrix GetMatrixFromFile(std::ifstream & input, const unsigned dim, bool & error)
{
	matrix initialMatrix = GetNullMatrix(dim);	

	std::string currentLine;
	unsigned quantityOfLines = 0;

	while (std::getline(input, currentLine))
	{
		if (quantityOfLines >= dim)
		{
			std::cerr << "Many lines in the file" << std::endl;
			error = true;
			return initialMatrix;
		}
		unsigned quantityNumber = 0;
		unsigned i = 0;
		while (i < currentLine.length())
		{
			if (quantityNumber >= dim)
			{
				std::cerr << "Many numbers in line" << std::endl;
				error = true;
				return initialMatrix;
			}
			std::string numer;
			bool triggerMinus = false;

			while (std::isdigit(currentLine[i]) || currentLine[i] == '-')
			{
				if (triggerMinus && (currentLine[i] == '-'))
				{
					std::cerr << "Two consecutive minus" << std::endl;
					error = true;
					return initialMatrix;
				}
				if (currentLine[i] == '-')
				{
					triggerMinus = true;
				}
				numer += currentLine[i];
				++i;
			}
			initialMatrix[quantityOfLines][quantityNumber] = static_cast<double>(atoi(numer.c_str()));
			++i;
			++quantityNumber;
		}
		if (quantityNumber < dim)
		{
			std::cerr << "Not only the numbers in a row" << std::endl;
			error = true;
			return initialMatrix;
		}
		++quantityOfLines;
	}
	if (quantityOfLines < dim)
	{
		std::cerr << "Few rows of the matrix" << std::endl;
		error = true;
		return initialMatrix;
	}
	return initialMatrix;
}

void swap(double & x, double & y)
{
	double temp = x;
	x = y;
	y = temp;
}

void swap(int & x, int & y) {
	int temp = x;
	x = y;
	y = temp;
}

double GetDeterminantMatrix(const unsigned & dim, matrix initialMatrix)
{
	double det = 1;
	for (unsigned i = 0; i < dim; ++i)
	{
		unsigned leadingPosition = i;
		for (unsigned j = i + 1; j < dim; ++j)
		{
			if (fabs(initialMatrix[j][i]) > fabs(initialMatrix[leadingPosition][i]))
			{
				leadingPosition = j;
			}
		}
		if (fabs(initialMatrix[leadingPosition][i]) < eps)
		{
			return 0;
		}
		if (leadingPosition != i)
		{
			det *= -1;
			for (unsigned j = 0; j < dim; ++j)
			{
				swap(initialMatrix[i][j], initialMatrix[leadingPosition][j]);
			}
		}
		det *= initialMatrix[i][i];
		for (unsigned j = i + 1; j < dim; ++j)
		{
			initialMatrix[i][j] /= initialMatrix[i][i];
		}
		for (unsigned j = 0; j < dim; ++j)
		{
			if (j != i && fabs(initialMatrix[j][i]) > eps)
			{
				for (unsigned k = i + 1; k < dim; ++k)
				{
					initialMatrix[j][k] -= initialMatrix[i][k] * initialMatrix[j][i];

				}
			}
		}
	}
	return det;
}

matrix GetInverseMatrix(const unsigned & dim, matrix initialMatrix)
{
	matrix inverseMatrix = GetIdentityMatrix(dim);
	for (unsigned i = 0; i < dim; ++i)
	{
		double leadingMember = initialMatrix[i][i];
		unsigned leadingPosition = i;
		for (unsigned j = i; j < dim; ++j)
		{
			if (fabs(initialMatrix[j][i]) > fabs(leadingMember))
			{
				leadingMember = initialMatrix[j][i];
				leadingPosition = j;
			}
		}
		if (fabs(leadingMember) > eps)
		{
			for (unsigned j = 0; j < dim; ++j)
			{
				swap(initialMatrix[i][j], initialMatrix[leadingPosition][j]);
				swap(inverseMatrix[i][j], inverseMatrix[leadingPosition][j]);
			}
			for (unsigned j = 0; j < dim; ++j)
			{
				if (i != j)
				{
					double multiplier = initialMatrix[j][i] / initialMatrix[i][i];
					for (unsigned k = 0; k < dim; ++k)
					{
						initialMatrix[j][i] -= initialMatrix[i][k] * multiplier;
						inverseMatrix[j][i] -= inverseMatrix[i][k] * multiplier;
					}
				}
			}
		}
	}
	for (unsigned i = 0; i < dim; ++i)
	{
		inverseMatrix[i][i] /= initialMatrix[i][i];
		initialMatrix[i][i] /= initialMatrix[i][i];
	}
	return inverseMatrix;
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		std::cerr << "Invalid arguments count" << std::endl
			<< "Usage: invert <matrix file>" << std::endl;
		return 1;
	}

	std::ifstream input(argv[1]);
	if (!input.is_open())
	{
		std::cerr << "Failed to open " << argv[1] << " for reading" << std::endl;
		return 1;
	}

	matrix initialMatrix;
	
	bool error = false;
	
    initialMatrix = GetMatrixFromFile(input, dim, error);

	if (error)
	{
		return 1;
	}

	if (GetDeterminantMatrix(dim, initialMatrix) == 0)
	{
		std::cout << "The inverse matrix does not exist" << std::endl;
	}
	else
	{
		PrintMatrix(dim, GetInverseMatrix(dim, initialMatrix));
	}
	return 0;
}