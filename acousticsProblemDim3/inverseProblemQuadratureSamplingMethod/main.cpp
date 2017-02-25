#include "stdafx.h"
#include "../directProblemQuadratureSamplingMethod/basicFunctions.h"
#include "../directProblemQuadratureSamplingMethod/matrix_utils.h"

using namespace std;


int main()
{
	size_t numberOfIterations;

	const size_t N = NUMBER_PARTITION_POINTS;

	const size_t N_square = (N + 1) * (N + 1);
	const size_t N_cube = (N + 1) * (N + 1) * (N + 1);

	cout << "Enter the number of iterations ";
	cin >> numberOfIterations;

	float alpha;
	cout << "Enter alpha ";
	cin >> alpha;

	float q;
	cout << "Enter q ";
	cin >> q;

	// память для основных массивов
	vector<vector<vector<vector<vector<vector<complex<float>>>>>>> a(N + 1,
		vector<vector<vector<vector<vector<complex<float>>>>>>(N + 1,
			vector<vector<vector<vector<complex<float>>>>>(N + 1,
				vector<vector<vector<complex<float>>>>(N + 1,
					vector<vector<complex<float>>>(N + 1,
						vector<complex<float>>(N + 1, complex<float>()))))));

	vector<vector<vector<vector<vector<complex<float>>>>>> overline_a(N + 1,
		vector<vector<vector<vector<complex<float>>>>>(N + 1,
			vector<vector<vector<complex<float>>>>(N + 1,
				vector<vector<complex<float>>>(N + 1,
					vector<complex<float>>(N + 1, complex<float>())))));

	// начало счета времени
	clock_t timeStart, timeFinish, timeBegin;
	timeBegin = clock();
	timeStart = clock();

	// Начало загрузки данных прямой задачи
	// загружаем  основные матрицы
	ifstream f_a("matrix_a.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t k = 0; k <= N; ++k)
			{
				for (size_t p = 0; p <= N; ++p)
				{
					for (size_t q = 0; q <= N; ++q)
					{
						for (size_t r = 0; r <= N; ++r)
						{
							f_a >> a[i][j][k][p][q][r];
						}
					}
				}
			}
		}
	}
	f_a.close();

	ifstream f_overline_a("matrix_overline_a.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t p = 0; p <= N; ++p)
			{
				for (size_t q = 0; q <= N; ++q)
				{
					for (size_t r = 0; r <= N; ++r)
					{
						f_overline_a >> overline_a[i][j][p][q][r];
					}
				}
			}
		}
	}
	f_overline_a.close();

	//печатаем время работы
	timeFinish = clock();
	float d;
	d = (float)(timeFinish - timeStart) / CLOCKS_PER_SEC;
	cout << "Download time major arrays " << d << endl;
	timeStart = clock();

	// выделяем память для правой части
	vector<vector<vector<complex<float>>>> f_Source_01(N + 1, vector<vector<complex<float>>>(N + 1,
		vector<complex<float>>(N + 1, complex<float>())));
	vector<vector<vector<complex<float>>>> f_Source_03(N + 1, vector<vector<complex<float>>>(N + 1,
		vector<complex<float>>(N + 1, complex<float>())));
	vector<vector<vector<complex<float>>>> f_Source_05(N + 1, vector<vector<complex<float>>>(N + 1,
		vector<complex<float>>(N + 1, complex<float>())));
	vector<vector<complex<float>>> f_Source_02(N + 1, vector<complex<float>>(N + 1, complex<float>()));
	vector<vector<complex<float>>> f_Source_04(N + 1, vector<complex<float>>(N + 1, complex<float>()));
	vector<vector<complex<float>>> f_Source_06(N + 1, vector<complex<float>>(N + 1, complex<float>()));

	// первый источник
	ifstream file_Source_01("f_Source_01.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t k = 0; k <= N; ++k)
			{
				file_Source_01 >> f_Source_01[i][j][k];
			}
		}
	}
	file_Source_01.close();
	ifstream file_Source_02("f_Source_02.txt");

	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			file_Source_02 >> f_Source_02[i][j];
		}
	}
	file_Source_02.close();

	// второй источник
	ifstream file_Source_03("f_Source_03.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t k = 0; k <= N; ++k)
			{
				file_Source_03 >> f_Source_03[i][j][k];
			}
		}
	}
	file_Source_03.close();
	ifstream file_Source_04("f_Source_04.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			file_Source_04 >> f_Source_04[i][j];
		}
	}
	file_Source_04.close();

	// третий источник
	ifstream file_Source_05("f_Source_05.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t k = 0; k <= N; ++k)
			{
				file_Source_05 >> f_Source_05[i][j][k];
			}
		}
	}
	file_Source_05.close();
	ifstream file_Source_06("f_Source_06.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			file_Source_06 >> f_Source_06[i][j];
		}
	}
	file_Source_06.close();
	//печатаем время работы
	timeFinish = clock();
	d = (float)(timeFinish - timeStart) / CLOCKS_PER_SEC;
	cout << "Download Time arrays sources " << d << endl;
	timeStart = clock();	
	
	// память для поля в приемниках
	vector<vector<complex<float>>> overline_u_01(N + 1, vector<complex<float>>(N + 1, complex<float>()));
	vector<vector<complex<float>>> overline_u_02(N + 1, vector<complex<float>>(N + 1, complex<float>()));
	vector<vector<complex<float>>> overline_u_03(N + 1, vector<complex<float>>(N + 1, complex<float>()));

	// Загрузка акустического поля в приёмнике
	ifstream file_overline_u_1("matrix_overline_u_1.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			file_overline_u_1 >> overline_u_01[i][j];
		}
	}
	file_overline_u_1.close();

	ifstream file_overline_u_2("matrix_overline_u_2.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			file_overline_u_2 >> overline_u_02[i][j];
		}
	}
	file_overline_u_2.close();

	ifstream file_overline_u_3("matrix_overline_u_3.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			file_overline_u_3 >> overline_u_03[i][j];
		}
	}
	file_overline_u_3.close();
	timeFinish = clock();
	d = (float)(timeFinish - timeStart) / CLOCKS_PER_SEC;
	cout << "Loading time of the acoustic field in the receivers " << d << endl;
	timeStart = clock();

	//выделение памяти под массивы производных  F_1, F_2, ...
	vector<vector<complex<float>>> F_01(N_cube, vector<complex<float>>(N_cube, complex<float>()));
	vector<vector<complex<float>>> F_03(N_cube, vector<complex<float>>(N_cube, complex<float>()));
	vector<vector<complex<float>>> F_05(N_cube, vector<complex<float>>(N_cube, complex<float>()));
	vector<vector<complex<float>>> F_o(N_cube, vector<complex<float>>(N_cube, complex<float>()));

	vector<vector<complex<float>>> F_02(N_square, vector<complex<float>>(N_cube, complex<float>()));
	vector<vector<complex<float>>> F_04(N_square, vector<complex<float>>(N_cube, complex<float>()));
	vector<vector<complex<float>>> F_06(N_square, vector<complex<float>>(N_cube, complex<float>()));
	vector<vector<complex<float>>> F_oo(N_square, vector<complex<float>>(N_cube, complex<float>()));

	//выделение памяти под массивы A и B
	vector<vector<complex<float>>> A_00(N_cube, vector<complex<float>>(N_cube, complex<float>()));
	vector<vector<complex<float>>> A_01(N_cube, vector<complex<float>>(N_cube, complex<float>()));
	vector<vector<complex<float>>> A_02(N_cube, vector<complex<float>>(N_cube, complex<float>()));
	vector<vector<complex<float>>> A_03(N_cube, vector<complex<float>>(N_cube, complex<float>()));

	vector<vector<complex<float>>> B(N_cube, vector<complex<float>>(N_cube, complex<float>()));
	vector<vector<complex<float>>> inverseMatrixB(N_cube, vector<complex<float>>(N_cube, complex<float>()));

	vector<vector<complex<float>>> auxiliaryMatrix(N_cube, vector<complex<float>>(N_cube, complex<float>()));
	vector<vector<complex<float>>> secondAuxiliaryMatrix(N_cube, vector<complex<float>>(N_cube, complex<float>()));

	// память для хранения значений основного оператора
	vector<complex<float>> F_part_01(N_cube, complex<float>());
	vector<complex<float>> F_part_02(N_square, complex<float>());
	vector<complex<float>> F_part_03(N_cube, complex<float>());
	vector<complex<float>> F_part_04(N_square, complex<float>());
	vector<complex<float>> F_part_05(N_cube, complex<float>());
	vector<complex<float>> F_part_06(N_square, complex<float>());

	// память для b_0, b_1,... 
	vector<complex<float>> b0(N_cube, complex<float>());
	vector<complex<float>> b1(N_cube, complex<float>());
	vector<complex<float>> b2(N_cube, complex<float>());
	vector<complex<float>> b3(N_cube, complex<float>());

	// память для u^(1), u^(2), u^(3)
	vector<vector<vector<complex<float>>>> u_1(N + 1, vector<vector<complex<float>>>(N + 1,
		vector<complex<float>>(N + 1, complex<float>())));
	vector<vector<vector<complex<float>>>> u_2(N + 1, vector<vector<complex<float>>>(N + 1,
		vector<complex<float>>(N + 1, complex<float>())));
	vector<vector<vector<complex<float>>>> u_3(N + 1, vector<vector<complex<float>>>(N + 1,
		vector<complex<float>>(N + 1, complex<float>())));

	// память для xi
	vector<vector<vector<complex<float>>>> xi(N + 1, vector<vector<complex<float>>>(N + 1,
		vector<complex<float>>(N + 1, complex<float>())));

	// память для перенумерованных переменных и вспомогательного вектора
	vector<complex<float>> numbered_u_1(N_cube, complex<float>());
	vector<complex<float>> numbered_u_2(N_cube, complex<float>());
	vector<complex<float>> numbered_u_3(N_cube, complex<float>());

	vector<complex<float>> numbered_xi(N_cube, complex<float>());

	vector<complex<float>> supportingVector_cube(N_cube, complex<float>());
	vector<complex<float>> secondSupportingVector(N_cube, complex<float>());
	vector<complex<float>> supportingVector_square(N_square, complex<float>());

	// Начало вычислительной части
	// начальное приближение u
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t k = 0; k <= N; ++k)
			{
				u_1[i][j][k] = f_Source_01[i][j][k];
				u_2[i][j][k] = f_Source_03[i][j][k];
				u_3[i][j][k] = f_Source_05[i][j][k];

			}
		}
	}
	// начальное приближение xi
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t k = 0; k <= N; ++k)
			{
				xi[i][j][k] = (0.01f, 0.00f);

			}
		}
	}

	// начало основных итераций
	size_t ii, jj;

	for (size_t iteration = 0; iteration < numberOfIterations; ++iteration)
	{
		cout << endl;
		cout << "Iteration number " << (iteration + 1) << endl;
		cout << "alpha= " << alpha << endl;
		timeStart = clock();

		//строим левую часть СЛАУ основаного метода Ньютона

		// определяем матрицы F_01 Якобиана
		for (size_t i = 0; i <= N; ++i)
		{
			for (size_t j = 0; j <= N; ++j)
			{
				for (size_t k = 0; k <= N; ++k)
				{
					ii = i * (N + 1) * (N + 1) + j * (N + 1) + k;
					for (size_t p = 0; p < N; ++p)
					{
						for (size_t q = 0; q < N; ++q)
						{
							for (size_t r = 0; r < N; ++r)
							{
								jj = p * (N + 1) * (N + 1) + q * (N + 1) + r;
								F_01[ii][jj] = a[i][j][k][p][q][r] * u_1[p][q][r];
								F_03[ii][jj] = a[i][j][k][p][q][r] * u_2[p][q][r];
								F_05[ii][jj] = a[i][j][k][p][q][r] * u_3[p][q][r];
								F_o[ii][jj] = a[i][j][k][p][q][r] * xi[p][q][r];
							}
						}
					}
					F_01[ii][ii] = (0.0f, 0.0f);
					F_03[ii][ii] = (0.0f, 0.0f);
					F_05[ii][ii] = (0.0f, 0.0f);
					F_o[ii][ii] = (1.0f, 0.0f);
				}
			}
		}

		// определяем матрицы F_02, F_04, F_06 Якобиана
		for (size_t i = 0; i <= N; ++i)
		{
			for (size_t j = 0; j <= N; ++j)
			{
				ii = i * (N + 1) + j;
				for (size_t p = 0; p < N; ++p)
				{
					for (size_t q = 0; q < N; ++q)
					{
						for (size_t r = 0; r < N; ++r)
						{
							jj = p * (N + 1) + q;
							F_02[ii][jj] = overline_a[i][j][p][q][r] * u_1[p][q][r];
							F_04[ii][jj] = overline_a[i][j][p][q][r] * u_2[p][q][r];
							F_06[ii][jj] = overline_a[i][j][p][q][r] * u_3[p][q][r];
							F_oo[ii][jj] = overline_a[i][j][p][q][r] * xi[p][q][r];
						}
					}
				}
			}
		}
		
		// находим матрицы А и В
		MultiplicationTransposedMatrix(N_cube, N_cube, N_cube, F_01, F_01, A_00);
		MultiplicationTransposedMatrix(N_cube, N_square, N_cube, F_02, F_02, auxiliaryMatrix);
		AdditionOfSquareMatrices(N_cube, A_00, auxiliaryMatrix);

		MultiplicationTransposedMatrix(N_cube, N_cube, N_cube, F_03, F_03, auxiliaryMatrix);
		AdditionOfSquareMatrices(N_cube, A_00, auxiliaryMatrix);

		MultiplicationTransposedMatrix(N_cube, N_square, N_cube, F_04, F_04, auxiliaryMatrix);
		AdditionOfSquareMatrices(N_cube, A_00, auxiliaryMatrix);

		MultiplicationTransposedMatrix(N_cube, N_cube, N_cube, F_05, F_05, auxiliaryMatrix);
		AdditionOfSquareMatrices(N_cube, A_00, auxiliaryMatrix);

		MultiplicationTransposedMatrix(N_cube, N_square, N_cube, F_06, F_06, auxiliaryMatrix);
		AdditionOfSquareMatrices(N_cube, A_00, auxiliaryMatrix);

		MultiplicationTransposedMatrix(N_cube, N_cube, N_cube, F_01, F_o, A_01);
		MultiplicationTransposedMatrix(N_cube, N_square, N_cube, F_02, F_oo, auxiliaryMatrix);
		AdditionOfSquareMatrices(N_cube, A_01, auxiliaryMatrix);

		MultiplicationTransposedMatrix(N_cube, N_cube, N_cube, F_03, F_o, A_02);
		MultiplicationTransposedMatrix(N_cube, N_square, N_cube, F_04, F_oo, auxiliaryMatrix);
		AdditionOfSquareMatrices(N_cube, A_02, auxiliaryMatrix);

		MultiplicationTransposedMatrix(N_cube, N_cube, N_cube, F_05, F_o, A_03);
		MultiplicationTransposedMatrix(N_cube, N_square, N_cube, F_06, F_oo, auxiliaryMatrix);
		AdditionOfSquareMatrices(N_cube, A_03, auxiliaryMatrix);

		MultiplicationTransposedMatrix(N_cube, N_cube, N_cube, F_o, F_o, B);
		MultiplicationTransposedMatrix(N_cube, N_square, N_cube, F_oo, F_oo, auxiliaryMatrix);
		AdditionOfSquareMatrices(N_cube, B, auxiliaryMatrix);

		//добавляем alpha к диагонали
		for (size_t ii = 0; ii < N_cube; ++ii)
		{
			A_00[ii][ii] += alpha;
			B[ii][ii] += alpha;
		}
		timeFinish = clock();
		d = (float)(timeFinish - timeStart) / CLOCKS_PER_SEC;
		cout << "Calculation time left side " << d << endl;
		timeStart = clock();

		//строим правую часть СЛАУ основаного метода Ньютона
		// находим значения основного оператора F
		for (size_t i = 0; i <= N; ++i)
		{
			for (size_t j = 0; j <= N; ++j)
			{
				for (size_t k = 0; k <= N; ++k)
				{
					ii = i * (N + 1) * (N + 1) + j * (N + 1) + k;
					F_part_01[ii] = u_1[i][j][k];
					F_part_03[ii] = u_2[i][j][k];
					F_part_05[ii] = u_3[i][j][k];
					for (size_t p = 0; p < N; ++p)
					{
						for (size_t q = 0; q < N; ++q)
						{
							for (size_t r = 0; r < N; ++r)
							{
								if ((i != p) || (q != j) || (r != k))
								{
									F_part_01[ii] += a[i][j][k][p][q][r] * xi[p][q][r] * u_1[p][q][r];
									F_part_03[ii] += a[i][j][k][p][q][r] * xi[p][q][r] * u_2[p][q][r];
									F_part_05[ii] += a[i][j][k][p][q][r] * xi[p][q][r] * u_3[p][q][r];
								}
							}
						}
					}
					F_part_01[ii] -= f_Source_01[i][j][k];
					F_part_03[ii] -= f_Source_03[i][j][k];
					F_part_05[ii] -= f_Source_05[i][j][k];
				}
			}
		}

		for (size_t i = 0; i <= N; ++i)
		{
			for (size_t j = 0; j <= N; ++j)
			{
				ii = i * (N + 1) + j;
				F_part_02[ii] = overline_u_01[i][j] - f_Source_02[i][j];
				F_part_04[ii] = overline_u_02[i][j] - f_Source_04[i][j];
				F_part_06[ii] = overline_u_03[i][j] - f_Source_06[i][j];
				for (size_t p = 0; p < N; ++p)
				{
					for (size_t q = 0; q < N; ++q)
					{
						for (size_t r = 0; r < N; ++r)
						{
							F_part_02[ii] += overline_a[i][j][p][q][r] * xi[p][q][r] * u_1[p][q][r];
							F_part_04[ii] += overline_a[i][j][p][q][r] * xi[p][q][r] * u_2[p][q][r];
							F_part_06[ii] += overline_a[i][j][p][q][r] * xi[p][q][r] * u_3[p][q][r];
						}
					}
				}
			}
		}

		// находим F^{\prime}(x)*x и вычитаем F(x) 
		// перенумерация xi
		for (size_t i = 0; i <= N; ++i)
		{
			for (size_t j = 0; j <= N; ++j)
			{
				for (size_t k = 0; k <= N; ++k)
				{
					ii = i * (N + 1) * (N + 1) + j * (N + 1) + k;
					numbered_xi[ii] = xi[i][j][k];
				}
			}
		}
		//
		//первый источник
		// перенумерация u^{1}
		for (size_t i = 0; i <= N; ++i)
		{
			for (size_t j = 0; j <= N; ++j)
			{
				for (size_t k = 0; k <= N; ++k)
				{
					ii = i * (N + 1) * (N + 1) + j * (N + 1) + k;
					numbered_u_1[ii] = u_1[i][j][k];
				}
			}
		}
		MultiplicationMatrixVector(N_cube, N_cube, F_01, numbered_xi, supportingVector_cube);
		for (size_t ii = 0; ii < N_cube; ++ii)
		{
			F_part_01[ii] = supportingVector_cube[ii] - F_part_01[ii];
		}
		MultiplicationMatrixVector(N_cube, N_cube, F_o, numbered_u_1, supportingVector_cube);
		for (size_t ii = 0; ii < N_cube; ++ii)
		{
			F_part_01[ii] += supportingVector_cube[ii];
		}

		MultiplicationMatrixVector(N_square, N_cube, F_02, numbered_xi, supportingVector_square);
		for (size_t ii = 0; ii <N_square; ++ii)
		{
			F_part_02[ii] = supportingVector_square[ii] - F_part_02[ii];
		}
		MultiplicationMatrixVector(N_square, N_cube, F_oo, numbered_u_1, supportingVector_square);
		for (size_t ii = 0; ii <N_square; ++ii)
		{
			F_part_02[ii] = F_part_02[ii] + supportingVector_square[ii];
		}

		//второй источник
		// перенумерация u^{2}
		for (size_t i = 0; i <= N; ++i)
		{
			for (size_t j = 0; j <= N; ++j)
			{
				for (size_t k = 0; k <= N; ++k)
				{
					ii = i * (N + 1) * (N + 1) + j * (N + 1) + k;
					numbered_u_2[ii] = u_2[i][j][k];
				}
			}
		}
		MultiplicationMatrixVector(N_cube, N_cube, F_03, numbered_xi, supportingVector_cube);
		for (size_t ii = 0; ii < N_cube; ++ii)
		{
			F_part_03[ii] = supportingVector_cube[ii] - F_part_03[ii];
		}
		MultiplicationMatrixVector(N_cube, N_cube, F_o, numbered_u_2, supportingVector_cube);
		for (size_t ii = 0; ii < N_cube; ++ii)
		{
			F_part_03[ii] += supportingVector_cube[ii];
		}

		MultiplicationMatrixVector(N_square, N_cube, F_04, numbered_xi, supportingVector_square);
		for (size_t ii = 0; ii < N_square; ++ii)
		{
			F_part_04[ii] = supportingVector_square[ii] - F_part_04[ii];
		}
		MultiplicationMatrixVector(N_square, N_cube, F_oo, numbered_u_2, supportingVector_square);
		for (size_t ii = 0; ii < N_square; ++ii)
		{
			F_part_04[ii] = F_part_04[ii] + supportingVector_square[ii];
		}

		//третий источник
		// перенумерация u^{3}
		for (size_t i = 0; i <= N; ++i)
		{
			for (size_t j = 0; j <= N; ++j)
			{
				for (size_t k = 0; k <= N; ++k)
				{
					ii = i * (N + 1) * (N + 1) + j * (N + 1) + k;
					numbered_u_3[ii] = u_3[i][j][k];
				}
			}
		}
		MultiplicationMatrixVector(N_cube, N_cube, F_05, numbered_xi, supportingVector_cube);
		for (size_t ii = 0; ii < N_cube; ++ii)
		{
			F_part_05[ii] = supportingVector_cube[ii] - F_part_05[ii];
		}
		MultiplicationMatrixVector(N_cube, N_cube, F_o, numbered_u_3, supportingVector_cube);
		for (size_t ii = 0; ii < N_cube; ++ii)
		{
			F_part_05[ii] += supportingVector_cube[ii];
		}

		MultiplicationMatrixVector(N_square, N_cube, F_06, numbered_xi, supportingVector_square);
		for (size_t ii = 0; ii < N_square; ++ii)
		{
			F_part_06[ii] = supportingVector_square[ii] - F_part_06[ii];
		}
		MultiplicationMatrixVector(N_square, N_cube, F_oo, numbered_u_3, supportingVector_square);
		for (size_t ii = 0; ii < N_square; ++ii)
		{
			F_part_06[ii] = F_part_06[ii] + supportingVector_square[ii];
		}

		// находим окончательно правую часть b0, b1,...
		// b0
		MultiplicationTransposedMatrixVector(N_cube, N_cube, F_01, F_part_01, b0);
		MultiplicationTransposedMatrixVector(N_cube, N_square, F_02, F_part_02, supportingVector_cube);
		AdditionOfVectors(N_cube, b0, supportingVector_cube);
		MultiplicationTransposedMatrixVector(N_cube, N_cube, F_03, F_part_03, supportingVector_cube);
		AdditionOfVectors(N_cube, b0, supportingVector_cube);
		MultiplicationTransposedMatrixVector(N_cube, N_square, F_04, F_part_04, supportingVector_cube);
		AdditionOfVectors(N_cube, b0, supportingVector_cube);
		MultiplicationTransposedMatrixVector(N_cube, N_cube, F_05, F_part_05, supportingVector_cube);
		AdditionOfVectors(N_cube, b0, supportingVector_cube);
		MultiplicationTransposedMatrixVector(N_cube, N_square, F_06, F_part_06, supportingVector_cube);
		AdditionOfVectors(N_cube, b0, supportingVector_cube);
		//b1
		MultiplicationTransposedMatrixVector(N_cube, N_cube, F_o, F_part_01, b1);
		MultiplicationTransposedMatrixVector(N_cube, N_square, F_oo, F_part_02, supportingVector_cube);
		AdditionOfVectors(N_cube, b1, supportingVector_cube);
		//b2
		MultiplicationTransposedMatrixVector(N_cube, N_cube, F_o, F_part_03, b2);
		MultiplicationTransposedMatrixVector(N_cube, N_square, F_oo, F_part_04, supportingVector_cube);
		AdditionOfVectors(N_cube, b2, supportingVector_cube);
		//b3
		MultiplicationTransposedMatrixVector(N_cube, N_cube, F_o, F_part_05, b3);
		MultiplicationTransposedMatrixVector(N_cube, N_square, F_oo, F_part_06, supportingVector_cube);
		AdditionOfVectors(N_cube, b3, supportingVector_cube);

		timeFinish = clock();
		d = (float)(timeFinish - timeStart) / CLOCKS_PER_SEC;
		cout << "Calculation time right side " << d << endl;
		timeStart = clock();

		// составляем основное уравнение метода Ньютона
		// для нахождения xi
		// находим обратную матрицу для B
		InvertMatrix(N_cube, B, inverseMatrixB);

		//для левой части уравнения с xi все складываем в A_00
		MultiplicationMatrixBlock(N_cube, N_cube, N_cube, A_01, inverseMatrixB, auxiliaryMatrix);
		MultiplicationMatrixTransposed(N_cube, N_cube, N_cube, auxiliaryMatrix, A_01, secondAuxiliaryMatrix);
		SubtractionOfSquareMatrices(N_cube, A_00, secondAuxiliaryMatrix);

		MultiplicationMatrixBlock(N_cube, N_cube, N_cube, A_02, inverseMatrixB, auxiliaryMatrix);
		MultiplicationMatrixTransposed(N_cube, N_cube, N_cube, auxiliaryMatrix, A_02, secondAuxiliaryMatrix);
		SubtractionOfSquareMatrices(N_cube, A_00, secondAuxiliaryMatrix);

		MultiplicationMatrixBlock(N_cube, N_cube, N_cube, A_03, inverseMatrixB, auxiliaryMatrix);
		MultiplicationMatrixTransposed(N_cube, N_cube, N_cube, auxiliaryMatrix, A_03, secondAuxiliaryMatrix);
		SubtractionOfSquareMatrices(N_cube, A_00, secondAuxiliaryMatrix);

		//для правой части уравнения с xi все складываем в b0 
		MultiplicationMatrixVector(N_cube, N_cube, inverseMatrixB, b1, supportingVector_cube);
		MultiplicationMatrixVector(N_cube, N_cube, A_01, supportingVector_cube, secondSupportingVector);
		SubtractionOfVectors(N_cube, b0, secondSupportingVector);

		MultiplicationMatrixVector(N_cube, N_cube, inverseMatrixB, b2, supportingVector_cube);
		MultiplicationMatrixVector(N_cube, N_cube, A_02, supportingVector_cube, secondSupportingVector);
		SubtractionOfVectors(N_cube, b0, secondSupportingVector);

		MultiplicationMatrixVector(N_cube, N_cube, inverseMatrixB, b3, supportingVector_cube);
		MultiplicationMatrixVector(N_cube, N_cube, A_03, supportingVector_cube, secondSupportingVector);
		SubtractionOfVectors(N_cube, b0, secondSupportingVector);

		// находим xi
		SolveSlauGaussa(A_00, b0, numbered_xi);

		//находим u^{1}
		MultiplicationTransposedMatrixVector(N_cube, N_cube, A_01, numbered_xi, supportingVector_cube);
		SubtractionOfVectors(N_cube, b1, supportingVector_cube);
		MultiplicationMatrixVector(N_cube, N_cube, inverseMatrixB, b1, numbered_u_1);

		//находим u^{2}
		MultiplicationTransposedMatrixVector(N_cube, N_cube, A_02, numbered_xi, supportingVector_cube);
		SubtractionOfVectors(N_cube, b2, supportingVector_cube);
		MultiplicationMatrixVector(N_cube, N_cube, inverseMatrixB, b2, numbered_u_2);

		//находим u^{3}
		MultiplicationTransposedMatrixVector(N_cube, N_cube, A_03, numbered_xi, supportingVector_cube);
		SubtractionOfVectors(N_cube, b3, supportingVector_cube);
		MultiplicationMatrixVector(N_cube, N_cube, inverseMatrixB, b3, numbered_u_3);

		timeFinish = clock();
		d = (float)(timeFinish - timeStart) / CLOCKS_PER_SEC;
		cout << "Calculation time solutions " << d << endl;

		// изменяем alpha для следующей итерации
		alpha = alpha * q;

		// Обратная перенумерация u^{1}, u^{2}, u^{3}, xi
		for (size_t ii = 0; ii < N_cube; ++ii)
		{
			size_t coordinate_x = ii / ((N + 1) * (N + 1));
			size_t coordinate_y = (ii - coordinate_x * ((N + 1) * (N + 1))) / (N + 1);
			size_t coordinate_z = ii % (N + 1);
			u_1[coordinate_x][coordinate_y][coordinate_z] = numbered_u_1[ii];
			u_2[coordinate_x][coordinate_y][coordinate_z] = numbered_u_2[ii];
			u_3[coordinate_x][coordinate_y][coordinate_z] = numbered_u_3[ii];
			xi[coordinate_x][coordinate_y][coordinate_z] = numbered_xi[ii];
		}

		// проекция xi >= 0
		for (size_t i = 0; i <= N; ++i)
		{
			for (size_t j = 0; j <= N; ++j)
			{
				for (size_t k = 0; k <= N; ++k)
				{
					if (real(xi[i][j][k]) <= 0.0f)
					{
						xi[i][j][k] = (0.0f, 0.0f);
					}
				}
			}
		}

		// печать результатов итераций (первые 5)
		if (iteration == 0)
		{
			ofstream f_xi("approximate_xi_1.txt");
			for (size_t i = 0; i <= N; ++i)
			{
				for (size_t j = 0; j <= N; ++j)
				{
					for (size_t k = 0; k <= N; ++k)
					{
						f_xi << fixed << setprecision(6) << real(xi[i][j][k]) << " ";
					}
				}
			}
			f_xi.close();
		}
		if (iteration == 1)
		{
			ofstream f_xi("approximate_xi_2.txt");
			for (size_t i = 0; i <= N; ++i)
			{
				for (size_t j = 0; j <= N; ++j)
				{
					for (size_t k = 0; k <= N; ++k)
					{
						f_xi << fixed << setprecision(6) << real(xi[i][j][k]) << " ";
					}
				}
			}
			f_xi.close();
		}
		if (iteration == 2)
		{
			ofstream f_xi("approximate_xi_3.txt");
			for (size_t i = 0; i <= N; ++i)
			{
				for (size_t j = 0; j <= N; ++j)
				{
					for (size_t k = 0; k <= N; ++k)
					{
						f_xi << fixed << setprecision(6) << real(xi[i][j][k]) << " ";
					}
				}
			}
			f_xi.close();
		}
		if (iteration == 3)
		{
			ofstream f_xi("approximate_xi_4.txt");
			for (size_t i = 0; i <= N; ++i)
			{
				for (size_t j = 0; j <= N; ++j)
				{
					for (size_t k = 0; k <= N; ++k)
					{
						f_xi << fixed << setprecision(6) << real(xi[i][j][k]) << " ";
					}
				}
			}
			f_xi.close();
		}
		if (iteration == 4)
		{
			ofstream f_xi("approximate_xi_5.txt");
			for (size_t i = 0; i <= N; ++i)
			{
				for (size_t j = 0; j <= N; ++j)
				{
					for (size_t k = 0; k <= N; ++k)
					{
						f_xi << fixed << setprecision(6) << real(xi[i][j][k]) << " ";
					}
				}
			}
			f_xi.close();
		}
	}

	//печатаем приближенное решение в файл
	ofstream f_xi("approximate_xi.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t k = 0; k <= N; ++k)
			{
				f_xi << fixed << setprecision(6) << real(xi[i][j][k]) << " ";
			}
		}
	}
	f_xi.close();

	d = (float)(timeFinish - timeBegin) / CLOCKS_PER_SEC;
	cout << "The total time of the program " << d << endl;

	return 0;
}
