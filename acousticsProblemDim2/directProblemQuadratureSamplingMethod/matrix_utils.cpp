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

void MultiplicationMatrixBlock(const size_t dim1, const size_t dim2, const size_t dim3,
			const vector<vector<complex<float>>> & lhs, const vector<vector<complex<float>>> & rhs,
			vector<vector<complex<float>>> & result)
{
	vector<complex<float>> thatColumn(dim3);
	vector<complex<float>> thisRow(dim2);
	complex<float> summand;

	for (size_t col = 0; col < dim3; ++col)
	{
		for (size_t k = 0; k < dim2; ++k)
		{
			thatColumn[k] = rhs[k][col];
		}
		for (size_t row = 0; row < dim1; ++row)
		{
			thisRow = lhs[row];
			summand = (0.0f, 0.0f);
			for (size_t k = 0; k < dim2; ++k)
			{
				summand += thisRow[k] * thatColumn[k];
			}
			result[row][col] = summand;
		}
	}
}

void MultiplicationMatrixTransposed(const size_t dim1, const size_t dim2, const size_t dim3,
			const vector<vector<complex<float>>> & lhs, const vector<vector<complex<float>>> & rhs,
			vector<vector<complex<float>>> & result)
{
	vector<complex<float>> thatRow(dim2);
	vector<complex<float>> thisRow(dim2);
	complex<float> summand;

	for (size_t col = 0; col < dim3; ++col)
	{
		for (size_t row = 0; row < dim1; ++row)
		{
			thisRow = lhs[row];
			thatRow = rhs[row];
			summand = (0.0f, 0.0f);
			for (size_t k = 0; k < dim2; ++k)
			{
				summand += thisRow[k] * conj(thatRow[k]);
			}
			result[row][col] = summand;
		}
	}
}

void MultiplicationTransposedMatrix(const size_t dim1, const size_t dim2, const size_t dim3,
	const vector<vector<complex<float>>> & lhs, const vector<vector<complex<float>>> & rhs,
	vector<vector<complex<float>>> & result)
{
	vector<vector<complex<float>>> newLhs(dim3, vector<complex<float>>(dim1));
	for (size_t i = 0; i < dim1; ++i)
	{
		for (size_t j = 0; j < dim3; ++j)
		{
			newLhs[j][i] = conj(rhs[i][j]);
		}
	}

	vector<vector<complex<float>>> transpResult(dim3, vector<complex<float>>(dim2));
	MultiplicationMatrixTransposed(dim3, dim1, dim2, newLhs, lhs, transpResult);	
	for (size_t i = 0; i < dim2; ++i)
	{
		for (size_t j = 0; j < dim3; ++j)
		{
			result[i][j] = conj(transpResult[j][i]);
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

void MultiplicationMatrixVector(const size_t dim1, const size_t dim2,
				const vector<vector<complex<float>>> & matrix, const vector<complex<float>> & vect,
						vector<complex<float>> & result)
{
	for (size_t row = 0; row < dim1; ++row)
	{
		result[row] = (0.0f, 0.0f);
	}
	for (size_t row = 0; row < dim1; ++row)
	{
		for (size_t col = 0; col < dim2; ++col)
		{
			result[row] += conj(matrix[row][col]) * vect[col];
		}
	}
}

complex<float> MultiplicationVectorVector(const size_t dim, const vector<complex<float>> & lhs,
											const vector<complex<float>> & rhs)
{
	complex<float> sum = complex<float>();
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
	for (size_t row = 0; row < dim; ++row)
	{
		for (size_t col = 0; col < dim; ++col)
		{
			lhs[row][col] -= rhs[row][col];
		}
	}
}

void InvertMatrix(const size_t dim, vector<vector<complex<float>>> matrix,
					vector<vector<complex<float>>> & invertedMatrix)
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
