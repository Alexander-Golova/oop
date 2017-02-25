#pragma once

const size_t SIZE_BLOCK_PARALLEL_MULTIPLICATION_MATRIX = 32;

// решение системы методом Гаусса
void SolveSlauGaussa(const std::vector<std::vector<std::complex<float>>> & matrix,
	const std::vector<std::complex<float>> & rhs, std::vector<std::complex<float>> & exactSolution);

// сложение двух квадратных матриц - результат записывается в первую матрицу
void AdditionOfSquareMatrices(const size_t dimMatrix, std::vector<std::vector<std::complex<float>>> & matrix,
	const std::vector<std::vector<std::complex<float>>> & rhs);

// блочное умножение матриц
void MultiplicationMatrixBlock(const size_t dimMatrix_1, const size_t dimMatrix_2, const size_t dimMatrix_3,
	const std::vector<std::vector<std::complex<float>>> & lhs, const std::vector<std::vector<std::complex<float>>> & rhs,
	std::vector<std::vector<std::complex<float>>> & result);

// блочное умножение транспонированной матрицы на обычную матрицу
void MultiplicationTransposedMatrix(const size_t dimMatrix_1, const size_t dimMatrix_2, const size_t dimMatrix_3,
	const std::vector<std::vector<std::complex<float>>> & lhs, const std::vector<std::vector<std::complex<float>>> & rhs,
	std::vector<std::vector<std::complex<float>>> & result);

// блочное умножение обычной матрицы на транспонированную матрицу
void MultiplicationMatrixTransposed(const size_t dimMatrix_1, const size_t dimMatrix_2, const size_t dimMatrix_3,
	const std::vector<std::vector<std::complex<float>>> & lhs, const std::vector<std::vector<std::complex<float>>> & rhs,
	std::vector<std::vector<std::complex<float>>> & result);

// умножение транспонированной матрицы на вектор
void MultiplicationTransposedMatrixVector(const size_t dimMatrix_1, const size_t dimMatrix_2,
	const std::vector<std::vector<std::complex<float>>> & matrix, const std::vector<std::complex<float>> & vect,
	std::vector<std::complex<float>> & result);

// умножение матрицы на вектор
void MultiplicationMatrixVector(const size_t dimMatrix_1, const size_t dimMatrix_2,
	const std::vector<std::vector<std::complex<float>>> & matrix, const std::vector<std::complex<float>> & vect,
	std::vector<std::complex<float>> & result);

// умножение вектора на вектор
std::complex<float> MultiplicationVectorVector(const size_t dim, const std::vector<std::complex<float>> & lhs,
	const std::vector<std::complex<float>> & rhs);

// сложение двух векторов - результат записывается в первый вектор
void AdditionOfVectors(const size_t dim, std::vector<std::complex<float>> & lhs,
	const std::vector<std::complex<float>> & rhs);

// вычитание двух векторов - результат записывается в первый вектор
void SubtractionOfVectors(const size_t dim, std::vector<std::complex<float>> & lhs,
	const std::vector<std::complex<float>> & rhs);

// вычитание двух квадратных матриц - результат записывается в первую матрицу
void SubtractionOfSquareMatrices(const size_t dim, std::vector<std::vector<std::complex<float>>> & lhs,
	const std::vector<std::vector<std::complex<float>>> & rhs);

//нахождение обратной матрицы методом Жордана-Гаусса
void InvertMatrix(const size_t dim, std::vector<std::vector<std::complex<float>>> matrix,
	std::vector<std::vector<std::complex<float>>> & invertedMatrix);
