#pragma once

const size_t SIZE_BLOCK_PARALLEL_MULTIPLICATION_MATRIX = 32;

// ������� ������� ������� ������
void SolveSlauGaussa(const std::vector<std::vector<std::complex<float>>> & matrix,
	const std::vector<std::complex<float>> & rhs, std::vector<std::complex<float>> & exactSolution);

// �������� ���� ���������� ������ - ��������� ������������ � ������ �������
void AdditionOfSquareMatrices(const size_t dimMatrix, std::vector<std::vector<std::complex<float>>> & matrix,
	const std::vector<std::vector<std::complex<float>>> & rhs);

// ������� ��������� ������
void MultiplicationMatrixBlock(const size_t dimMatrix_1, const size_t dimMatrix_2, const size_t dimMatrix_3,
	const std::vector<std::vector<std::complex<float>>> & lhs, const std::vector<std::vector<std::complex<float>>> & rhs,
	std::vector<std::vector<std::complex<float>>> & result);

// ������� ��������� ����������������� ������� �� ������� �������
void MultiplicationTransposedMatrix(const size_t dimMatrix_1, const size_t dimMatrix_2, const size_t dimMatrix_3,
	const std::vector<std::vector<std::complex<float>>> & lhs, const std::vector<std::vector<std::complex<float>>> & rhs,
	std::vector<std::vector<std::complex<float>>> & result);

// ������� ��������� ������� ������� �� ����������������� �������
void MultiplicationMatrixTransposed(const size_t dimMatrix_1, const size_t dimMatrix_2, const size_t dimMatrix_3,
	const std::vector<std::vector<std::complex<float>>> & lhs, const std::vector<std::vector<std::complex<float>>> & rhs,
	std::vector<std::vector<std::complex<float>>> & result);

// ��������� ����������������� ������� �� ������
void MultiplicationTransposedMatrixVector(const size_t dimMatrix_1, const size_t dimMatrix_2,
	const std::vector<std::vector<std::complex<float>>> & matrix, const std::vector<std::complex<float>> & vect,
	std::vector<std::complex<float>> & result);

// ��������� ������� �� ������
void MultiplicationMatrixVector(const size_t dimMatrix_1, const size_t dimMatrix_2,
	const std::vector<std::vector<std::complex<float>>> & matrix, const std::vector<std::complex<float>> & vect,
	std::vector<std::complex<float>> & result);

// ��������� ������� �� ������
std::complex<float> MultiplicationVectorVector(const size_t dim, const std::vector<std::complex<float>> & lhs,
	const std::vector<std::complex<float>> & rhs);

// �������� ���� �������� - ��������� ������������ � ������ ������
void AdditionOfVectors(const size_t dim, std::vector<std::complex<float>> & lhs,
	const std::vector<std::complex<float>> & rhs);

// ��������� ���� �������� - ��������� ������������ � ������ ������
void SubtractionOfVectors(const size_t dim, std::vector<std::complex<float>> & lhs,
	const std::vector<std::complex<float>> & rhs);

// ��������� ���� ���������� ������ - ��������� ������������ � ������ �������
void SubtractionOfSquareMatrices(const size_t dim, std::vector<std::vector<std::complex<float>>> & lhs,
	const std::vector<std::vector<std::complex<float>>> & rhs);

//���������� �������� ������� ������� �������-������
void InvertMatrix(const size_t dim, std::vector<std::vector<std::complex<float>>> matrix,
	std::vector<std::vector<std::complex<float>>> & invertedMatrix);
