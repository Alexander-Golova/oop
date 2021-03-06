#include "pch.h"

const double eps = 10e-5;
const unsigned dim = 3;

typedef std::array<std::array<double, dim>, dim> Matrix;

Matrix GetIdentityMatrix()
{
	Matrix identityMatrix;
	for (size_t row = 0; row < dim; ++row)
	{
		for (size_t col = 0; col < dim; ++col)
		{
			identityMatrix[row][col] = 0;
		}
		identityMatrix[row][row] = 1;
	}
	return identityMatrix;
}

void PrintMatrix(const Matrix& initialMatrix)
{
	for (size_t row = 0; row < dim; ++row)
	{
		for (size_t col = 0; col < dim; ++col)
		{
			std::cout << std::fixed << std::setprecision(3) << initialMatrix[row][col] << " ";
		}
		std::cout << std::endl;
	}
}

Matrix GetMatrixFromFile(std::ifstream& input, bool& error)
{
	Matrix initialMatrix = GetIdentityMatrix();
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
	if (row != dim)
	{
		error = true;
	}
	return initialMatrix;
}

size_t GetMaximumNumberElementsRow(const Matrix& sourceMatrix, const size_t row, bool& error)
{
	error = false;
	double maxElement = sourceMatrix[row][row];
	size_t maxNumber = row;
	for (size_t col = row; col < dim; ++col)
	{
		if (fabs(sourceMatrix[col][row]) > fabs(maxElement))
		{
			maxElement = sourceMatrix[col][row];
			maxNumber = col;
		}
	}
	if (fabs(maxElement) < eps)
	{
		error = true;
	}
	return maxNumber;
}

void TransformMatrixColumn(Matrix& sourceMatrix, Matrix& invertedMatrix, const size_t& row)
{
	for (size_t col = 0; col < dim; ++col)
	{
		if (row != col)
		{
			double multiplier = sourceMatrix[col][row] / sourceMatrix[row][row];
			for (size_t i = 0; i < dim; ++i)
			{
				sourceMatrix[col][i] -= sourceMatrix[row][i] * multiplier;
				invertedMatrix[col][i] -= invertedMatrix[row][i] * multiplier;
			}
		}
	}
}

void NormalizeDiagonalMatrix(const Matrix& sourceMatrix, Matrix& invertedMatrix)
{
	for (size_t row = 0; row < dim; ++row)
	{
		invertedMatrix[row][row] /= sourceMatrix[row][row];
	}
}

bool InvertMatrix(Matrix sourceMatrix, Matrix& invertedMatrix)
{
	bool error = false;
	invertedMatrix = GetIdentityMatrix();
	for (size_t row = 0; row < dim && !error; ++row)
	{
		size_t leadingPosition = GetMaximumNumberElementsRow(sourceMatrix, row, error);
		if (error)
		{
			return !error;
		}
		else
		{
			std::swap(sourceMatrix[row], sourceMatrix[leadingPosition]);
			std::swap(invertedMatrix[row], invertedMatrix[leadingPosition]);
			TransformMatrixColumn(sourceMatrix, invertedMatrix, row);
		}
	}
	NormalizeDiagonalMatrix(sourceMatrix, invertedMatrix);
	return !error;
}

int main(int argc, char* argv[])
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

	Matrix sourceMatrix;
	Matrix invertedMatrix;
	bool error = false;

	sourceMatrix = GetMatrixFromFile(input, error);
	if (error)
	{
		std::cerr << "The array is defined correctly" << std::endl;
		return 1;
	}

	if (InvertMatrix(sourceMatrix, invertedMatrix))
	{
		PrintMatrix(invertedMatrix);
	}
	else
	{
		std::cout << "The inverse matrix does not exist" << std::endl;
	}
	return 0;
}
