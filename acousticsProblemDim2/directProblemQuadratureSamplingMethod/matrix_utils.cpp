#include "stdafx.h"
#include "matrix_utils.h"

using namespace std;

void SolveSlauGaussa(const vector<vector<complex<float>>> & matrix, const vector<complex<float>> & rhs,
						vector<complex<float>> & exactSolution)
{
	size_t dim = (size_t)rhs.size();
	vector<vector<complex<float>>> a(dim, vector<complex<float>>(dim + 1, complex<float>()));

	for (size_t row = 0; row < dim; ++row)
	{
		for (size_t col = 0; col < dim; ++col)
		{
			a[row][col] = matrix[row][col];
		}
		a[row][dim] = rhs[row];
	}

	vector<size_t> where(dim);
	size_t sel;

	for (size_t col = 0, row = 0; col < dim && row <= dim; ++col)
	{
		sel = row;
		for (size_t i = row; i < dim; ++i)
		{
			if (abs(a[i][col]) > abs(a[sel][col]))
			{
				sel = i;
			}
		}

		for (size_t i = col; i <= dim; ++i)
		{
			swap(a[sel][i], a[row][i]);
		}
		where[col] = row;

		for (size_t i = 0; i < dim; ++i)
		{
			if (i != row)
			{
				complex<float> c = a[i][col] / a[row][col];
				for (size_t j = col; j <= dim; ++j)
				{
					a[i][j] -= a[row][j] * c;
				}
			}
		}
		++row;
	}

	exactSolution.assign(dim, complex<float>());
	for (size_t i = 0; i < dim; ++i)
	{
		exactSolution[i] = a[where[i]][dim] / a[where[i]][i];
	}
}

void AdditionOfSquareMatrices(const size_t dim, vector<vector<complex<float>>> & matrix,
	const vector<vector<complex<float>>> & rhs)
{
	for (size_t col = 0; col < dim; ++col)
	{
		for (size_t row = 0; row < dim; ++row)
		{
			matrix[col][row] += rhs[col][row];
		}
	}
}

void MultiplicationMatrixBlock(const size_t dimMatrix_1, const size_t dimMatrix_2, const size_t dimMatrix_3,
	const vector<vector<complex<float>>> & lhs, const vector<vector<complex<float>>> & rhs,
	vector<vector<complex<float>>> & result)
{
	for (size_t i = 0; i < dimMatrix_1; ++i)
	{
		for (size_t j = 0; j < dimMatrix_3; ++j)
		{
			result[i][j] = (0.0f, 0.0f);
		}
	}

	for (size_t jj = 0; jj < dimMatrix_3; jj += SIZE_BLOCK_PARALLEL_MULTIPLICATION_MATRIX)
	{
		for (size_t kk = 0; kk < dimMatrix_2; kk += SIZE_BLOCK_PARALLEL_MULTIPLICATION_MATRIX)
		{
			for (size_t i = 0; i < dimMatrix_1; ++i)
			{
				for (size_t j = jj; j < std::min(jj + SIZE_BLOCK_PARALLEL_MULTIPLICATION_MATRIX, dimMatrix_3); ++j)
				{
					std::complex<float> r = (0.0f, 0.0f);
					for (size_t k = kk; k < std::min(kk + SIZE_BLOCK_PARALLEL_MULTIPLICATION_MATRIX, dimMatrix_2); ++k)
					{
						r = r + lhs[i][k] * rhs[k][j];
					}
					result[i][j] += r;
				}
			}
		}
	}
}

void MultiplicationTransposedMatrix(const size_t dimMatrix_1, const size_t dimMatrix_2, const size_t dimMatrix_3,
	const vector<vector<complex<float>>> & lhs, const vector<vector<complex<float>>> & rhs,
	vector<vector<complex<float>>> & result)
{
	for (size_t i = 0; i < dimMatrix_1; ++i)
	{
		for (size_t j = 0; j < dimMatrix_3; ++j)
		{
			result[i][j] = (0.0f, 0.0f);
		}
	}

	for (size_t jj = 0; jj < dimMatrix_3; jj += SIZE_BLOCK_PARALLEL_MULTIPLICATION_MATRIX)
	{
		for (size_t kk = 0; kk < dimMatrix_2; kk += SIZE_BLOCK_PARALLEL_MULTIPLICATION_MATRIX)
		{
			for (size_t i = 0; i < dimMatrix_1; ++i)
			{
				for (size_t j = jj; j < std::min(jj + SIZE_BLOCK_PARALLEL_MULTIPLICATION_MATRIX, dimMatrix_3); ++j)
				{
					std::complex<float> r = (0.0f, 0.0f);
					for (size_t k = kk; k < std::min(kk + SIZE_BLOCK_PARALLEL_MULTIPLICATION_MATRIX, dimMatrix_2); ++k)
					{
						r = r + lhs[k][i] * rhs[k][j];
					}
					result[i][j] += r;
				}
			}
		}
	}
}

void MultiplicationMatrixTransposed(const size_t dimMatrix_1, const size_t dimMatrix_2, const size_t dimMatrix_3,
	const vector<vector<complex<float>>> & lhs, const vector<vector<complex<float>>> & rhs,
	vector<vector<complex<float>>> & result)
{
	for (size_t i = 0; i < dimMatrix_1; ++i)
	{
		for (size_t j = 0; j < dimMatrix_3; ++j)
		{
			result[i][j] = (0.0f, 0.0f);
		}
	}

	for (size_t jj = 0; jj < dimMatrix_3; jj += SIZE_BLOCK_PARALLEL_MULTIPLICATION_MATRIX)
	{
		for (size_t kk = 0; kk < dimMatrix_2; kk += SIZE_BLOCK_PARALLEL_MULTIPLICATION_MATRIX)
		{
			for (size_t i = 0; i < dimMatrix_1; ++i)
			{
				for (size_t j = jj; j < std::min(jj + SIZE_BLOCK_PARALLEL_MULTIPLICATION_MATRIX, dimMatrix_3); ++j)
				{
					std::complex<float> r = (0.0f, 0.0f);
					for (size_t k = kk; k < std::min(kk + SIZE_BLOCK_PARALLEL_MULTIPLICATION_MATRIX, dimMatrix_2); ++k)
					{
						r = r + lhs[i][k] * rhs[j][k];
					}
					result[i][j] += r;
				}
			}
		}
	}
}

void MultiplicationTransposedMatrixVector(const size_t dimMatrix_1, const size_t dimMatrix_2,
	const vector<vector<complex<float>>> & matrix, const vector<complex<float>> & vect,
	vector<complex<float>> & result)
{
	for (size_t i = 0; i < dimMatrix_1; ++i)
	{
		result[i] = (0.0f, 0.0f);
	}
	for (size_t i = 0; i < dimMatrix_1; ++i)
	{
		for (size_t j = 0; j < dimMatrix_2; ++j)
		{
			result[i] += std::conj(matrix[j][i]) * vect[j];
		}
	}
}

void MultiplicationMatrixVector(const size_t dimMatrix_1, const size_t dimMatrix_2,
	const vector<vector<complex<float>>> & matrix, const vector<complex<float>> & vect,
	vector<complex<float>> & result)
{
	for (size_t i = 0; i < dimMatrix_1; ++i)
	{
		result[i] = (0.0f, 0.0f);
	}
	for (size_t i = 0; i < dimMatrix_1; ++i)
	{
		for (size_t j = 0; j < dimMatrix_2; ++j)
		{
			result[i] += std::conj(matrix[i][j]) * vect[j];
		}
	}
}

complex<float> MultiplicationVectorVector(const size_t dim, const vector<complex<float>> & lhs,
	const vector<complex<float>> & rhs)
{
	std::complex<float> sum = (0.0f, 0.0f);
	for (size_t i = 0; i < dim; ++i)
	{
		sum += lhs[i] * rhs[i];
	}
	return sum;
}

void AdditionOfVectors(const size_t dim, vector<complex<float>> & lhs,
	const vector<complex<float>> & rhs)
{
	for (size_t i = 0; i < dim; ++i)
	{
		lhs[i] += rhs[i];
	}
}

void SubtractionOfVectors(const size_t dim, vector<complex<float>> & lhs,
	const vector<complex<float>> & rhs)
{
	for (size_t i = 0; i < dim; ++i)
	{
		lhs[i] -= rhs[i];
	}
}

void SubtractionOfSquareMatrices(const size_t dim, vector<vector<complex<float>>> & lhs,
	const vector<vector<complex<float>>> & rhs)
{
	for (size_t i = 0; i < dim; ++i)
	{
		for (size_t j = 0; j < dim; ++j)
		{
			lhs[i][j] -= rhs[i][j];
		}
	}
}

void InvertMatrix(const size_t dim, std::vector<std::vector<std::complex<float>>> matrix,
	std::vector<std::vector<std::complex<float>>> & invertedMatrix)
{
	std::complex<float> temp;
	for (size_t row = 0; row < dim; ++row)
	{
		for (size_t col = 0; col < dim; ++col)
		{
			invertedMatrix[row][col] = (0.0f, 0.0f);
		}
		invertedMatrix[row][row] = (1.0f, 0.0f);
	}

	for (size_t row = 0; row < dim; ++row)
	{
		complex<float> maxElement = matrix[row][row];
		size_t maxNumber = row;
		for (size_t col = row; col < dim; ++col)
		{
			if (abs(matrix[col][row]) > abs(maxElement))
			{
				maxElement = matrix[col][row];
				maxNumber = col;
			}
		}
		for (size_t col = 0; col < dim; ++col)
		{
			temp = matrix[row][col];
			matrix[row][col] = matrix[maxNumber][col];
			matrix[maxNumber][col] = temp;
		}
		for (size_t col = 0; col < dim; ++col)
		{
			temp = invertedMatrix[row][col];
			invertedMatrix[row][col] = invertedMatrix[maxNumber][col];
			invertedMatrix[maxNumber][col] = temp;
		}

		for (size_t col = 0; col < dim; ++col)
		{
			if (row != col)
			{
				complex<float> multiplier = matrix[col][row] / matrix[row][row];
				for (size_t i = 0; i < dim; ++i)
				{
					matrix[col][i] -= matrix[row][i] * multiplier;
					invertedMatrix[col][i] -= invertedMatrix[row][i] * multiplier;
				}
			}
		}
	}
	for (size_t row = 0; row < dim; ++row)
	{
		invertedMatrix[row][row] /= matrix[row][row];
	}
}
