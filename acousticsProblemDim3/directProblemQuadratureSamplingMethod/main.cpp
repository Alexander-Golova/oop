#include "stdafx.h"
#include "basicFunctions.h"
#include "sourceFunction.h"
#include "matrix_utils.h"

using namespace std;

int main()
{
	const size_t N = NUMBER_PARTITION_POINTS;
	const float h = (float)a_R / N;

	// выделение памяти для акустического давления u
	vector<vector<vector<complex<float>>>> u(N + 1, vector<vector<complex<float>>>(N + 1,
		vector<complex<float>>(N + 1, complex<float>())));

	// выделение памяти для точного решения xi
	vector<vector<vector<float>>> xi(N + 1, vector<vector<float>>(N + 1, vector<float>(N + 1, 0.0f)));

	// задание точного решения \xi
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t k = 0; k <= N; ++k)
			{
				xi[i][j][k] = 0.0f;
			}
		}
	}
	for (size_t i = 5; i <= 8; ++i)
	{
		for (size_t j = 5; j <= 8; ++j)
		{
			for (size_t k = 7; k <= 10; ++k)
			{
				xi[i][j][k] = 0.2f;
			}
		}
	}

	//печатаем точное решение в файл
	ofstream f_xi("exact_xi.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t k = 0; k <= N; ++k)
			{
				f_xi << fixed << setprecision(6) << xi[i][j][k] << " ";
			}
		}
	}
	f_xi.close();

	// выделение памяти под 6-ти мерный "квадратный" комплексный массив
	vector<vector<vector<vector<vector<vector<complex<float>>>>>>> a(N + 1, 
		vector<vector<vector<vector<vector<complex<float>>>>>>(N + 1,
			vector<vector<vector<vector<complex<float>>>>>(N + 1,
				vector<vector<vector<complex<float>>>>(N + 1,
					vector<vector<complex<float>>>(N + 1,
						vector<complex<float>>(N + 1, complex<float>()))))));

	// выделение памяти под 5-ти мерный "квадратный" комплексный массив
	vector<vector<vector<vector<vector<complex<float>>>>>> overline_a(N + 1,
		vector<vector<vector<vector<complex<float>>>>>(N + 1,
			vector<vector<vector<complex<float>>>>(N + 1,
				vector<vector<complex<float>>>(N + 1,
					vector<complex<float>>(N + 1, complex<float>())))));

	// Начало вычислений основных матриц
	// начало счета времени
	clock_t timeStart, timeFinish, timeBegin;
	timeBegin = clock();
	timeStart = clock();

	// для индексов метода квадратур
	vector<float> index(N + 1);
	for (size_t i = 1; i < N; ++i)
	{
		if (i % 2 != 0)
		{
			index[i] = 1.333333f;
		}
		else
		{
			index[i] = 0.666667f;
		}
	}
	index[0] = 0.333333f;
	index[N] = 0.333333f;

	// нахождение массива a
	float dist;
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t k = 0; k <= N; ++k)
			{
				for (size_t p = 0; p < N; ++p)
				{
					for (size_t q = 0; q < N; ++q)
					{
						for (size_t r = 0; r < N; ++r)
						{
							if ((i != p) || (q != j) || (r != k))
							{
								dist = sqrtf(float((i - p) * (i - p) + (j - q) * (j - q) + (k - r) * (k - r)));
								dist *= h;
								a[i][j][k][p][q][r] = index[p] * index[q] * index[r];
								a[i][j][k][p][q][r] *= exp(-dist * (0.0f, 1.0f) * OMEGA / C_0) / dist;
								a[i][j][k][p][q][r] *= OMEGA * OMEGA * h * h * h;
								a[i][j][k][p][q][r] /= 12.566371f;
							}
						}
					}
				}
			}
		}
	}

	// нахождение массива overline_a
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t p = 0; p < N; ++p)
			{
				for (size_t q = 0; q < N; ++q)
				{
					for (size_t r = 0; r < N; ++r)
					{
						dist = sqrtf(float((i - p) * (i - p) + (j - q) * (j - q) + (receiver - r) * (receiver - r)));
						dist *= h;
						overline_a[i][j][p][q][r] = index[p] * index[q] * index[r];
						overline_a[i][j][p][q][r] *= exp(-dist * (0.0f, 1.0f) * OMEGA / C_0) / dist;
						overline_a[i][j][p][q][r] *= OMEGA * OMEGA * h * h * h;
						overline_a[i][j][p][q][r] /= 12.566371f;
					}
				}
			}
		}
	}

	//печатаем время работы
	timeFinish = clock();
	float d = (float)(timeFinish - timeStart) / CLOCKS_PER_SEC;
	cout << "Time calculation of basic matrices " << d << endl;
	timeStart = clock();

	// записываем массивы в файлы
	ofstream f_overline_a("matrix_overline_a.txt");
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
						f_overline_a << fixed << setprecision(6) << overline_a[i][j][p][q][r] << " ";
					}
				}
			}
		}
	}
	f_overline_a.close();

	ofstream f_a("matrix_a.txt");
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
							f_a << fixed << setprecision(6) << a[i][j][k][p][q][r] << " ";
						}
					}
				}
			}
		}
	}
	f_a.close();
	//печатаем время работы
	timeFinish = clock();
	d = (float)(timeFinish - timeStart) / CLOCKS_PER_SEC;
	cout << "Download time major arrays " << d << endl;
	timeStart = clock();

	// счет функции источника в R и X
	// первый источник
	ofstream f_Source_01("f_Source_01.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t k = 0; k <= N; ++k)
			{
				f_Source_01 << fixed << setprecision(6) << SourceFunction(source01, i * h, j * h, k * h) << " ";
			}
		}
	}
	f_Source_01.close();
	ofstream f_Source_02("f_Source_02.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			f_Source_02 << fixed << setprecision(6) << SourceFunction(source01, i * h, j * h, receiver) << " ";
		}
	}
	f_Source_02.close();

	// второй источник
	ofstream f_Source_03("f_Source_03.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t k = 0; k <= N; ++k)
			{
				f_Source_03 << fixed << setprecision(6) << SourceFunction(source02, i * h, j * h, k * h) << " ";
			}
		}
	}
	f_Source_03.close();
	ofstream f_Source_04("f_Source_04.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			f_Source_04 << fixed << setprecision(6) << SourceFunction(source02, i * h, j * h, receiver) << " ";
		}
	}
	f_Source_04.close();

	// третий источник
	ofstream f_Source_05("f_Source_05.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t k = 0; k <= N; ++k)
			{
				f_Source_05 << fixed << setprecision(6) << SourceFunction(source03, i * h, j * h, k * h) << " ";
			}
		}
	}
	f_Source_05.close();
	ofstream f_Source_06("f_Source_06.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			f_Source_06 << fixed << setprecision(6) << SourceFunction(source03, i * h, j * h, receiver) << " ";
		}
	}
	f_Source_06.close();

	//печатаем время работы
	timeFinish = clock();
	d = (float)(timeFinish - timeStart) / CLOCKS_PER_SEC;
	cout << "The computation time of the source function " << d << endl;
	timeStart = clock();

	
	// для нахождения u^(1) составляем СЛАУ основная матрица * u^(1) = правой части
	// substantiveMatrix[ii][jj] * numbered_u[jj] = rightPartEequation[ii]	
	const size_t N_cube = (N + 1) * (N + 1) * (N + 1);

	vector<complex<float>> rightPartEquation(N_cube, complex<float>());
	vector<complex<float>> numbered_u(N_cube, complex<float>());
	vector<vector<complex<float>>> substantiveMatrix(N_cube, vector<complex<float>>(N_cube, complex<float>()));

	//счет основной матрицы
	//
	size_t ii, jj;
	complex<float> sumOfTheCoefficients;
	//
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t k = 0; k <= N; ++k)
			{
				ii = i * (N + 1) * (N + 1) + j * (N + 1) + k;
				sumOfTheCoefficients = (0.0f, 0.0f);
				for (size_t p = 0; p < N; ++p)
				{
					for (size_t q = 0; q < N; ++q)
					{
						for (size_t r = 0; r < N; ++r)
						{
							jj = p * (N + 1) * (N + 1) + q * (N + 1) + r;
							substantiveMatrix[ii][jj] += a[i][j][k][p][q][r] * xi[p][q][r];
						}
					}
				}
				substantiveMatrix[ii][ii] = (1.0f, 0.0f);
			}
		}
	}
	timeFinish = clock();
	d = (float)(timeFinish - timeStart) / CLOCKS_PER_SEC;
	cout << "The computation time of the matrix inside the cube " << d << endl;
	timeStart = clock();

	// Для первого источника
	// нахождение правой части
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t k = 0; k <= N; ++k)
			{
				ii = i * (N + 1) * (N + 1) + j * (N + 1) + k;
				rightPartEquation[ii] = SourceFunction(source01, i * h, j * h, k * h);
			}
		}
	}
	// нахождение u^{(1)}
	SolveSlauGaussa(substantiveMatrix, rightPartEquation, numbered_u);

	// Обратная перенумерация
	size_t coordinate_x;
	size_t coordinate_y;
	size_t coordinate_z;
	for (size_t ii = 0; ii < N_cube; ++ii)
	{
		coordinate_x = ii / ((N + 1) * (N + 1));
		coordinate_y = (ii - coordinate_x * ((N + 1) * (N + 1))) / (N + 1);
		coordinate_z = ii % (N + 1);
		u[coordinate_x][coordinate_y][coordinate_z] = numbered_u[ii];
	}
	timeFinish = clock();
	d = (float)(timeFinish - timeStart) / CLOCKS_PER_SEC;
	cout << "Finding the acoustic pressure in R " << d << endl;
	timeStart = clock();
	
	// находим overline_u_0
	// выделение памяти для overline_u_0
	vector<vector<complex<float>>> overline_u(N + 1, vector<complex<float>>(N + 1, complex<float>()));
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			overline_u[i][j] = SourceFunction(source01, i * h, j * h, receiver);
		}
	}
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t p = 0; p < N; ++p)
			{
				for (size_t q = 0; q < N; ++q)
				{
					for (size_t r = 0; r < N; ++r)
					{
						overline_u[i][j] -= overline_a[i][j][p][q][r] * xi[p][q][r] * u[p][q][r];
					}
				}
			}
		}
	}
	// печать overline_u_0^(1) в файл в одну строчку
	ofstream f_overline_u_1("matrix_overline_u_1.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			f_overline_u_1 << fixed << setprecision(6) << overline_u[i][j] << " ";
		}
	}
	f_overline_u_1.close();
	timeFinish = clock();
	d = (float)(timeFinish - timeStart) / CLOCKS_PER_SEC;
	cout << "Finding the acoustic pressure in X " << d << endl;
	timeStart = clock();

	//Для второго источника
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t k = 0; k <= N; ++k)
			{
				ii = i * (N + 1) * (N + 1) + j * (N + 1) + k;
				rightPartEquation[ii] = SourceFunction(source02, i * h, j * h, k * h);
			}
		}
	}
	// нахождение u^{(2)}
	SolveSlauGaussa(substantiveMatrix, rightPartEquation, numbered_u);

	// Обратная перенумерация
	for (size_t ii = 0; ii < N_cube; ++ii)
	{
		coordinate_x = ii / ((N + 1) * (N + 1));
		coordinate_y = (ii - coordinate_x * ((N + 1) * (N + 1))) / (N + 1);
		coordinate_z = ii % (N + 1);
		u[coordinate_x][coordinate_y][coordinate_z] = numbered_u[ii];
	}
	timeFinish = clock();
	d = (float)(timeFinish - timeStart) / CLOCKS_PER_SEC;
	cout << "Finding the acoustic pressure in R " << d << endl;
	timeStart = clock();

	// находим overline_u_0
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			overline_u[i][j] = SourceFunction(source02, i * h, j * h, receiver);
		}
	}
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t p = 0; p < N; ++p)
			{
				for (size_t q = 0; q < N; ++q)
				{
					for (size_t r = 0; r < N; ++r)
					{
						overline_u[i][j] -= overline_a[i][j][p][q][r] * xi[p][q][r] * u[p][q][r];
					}
				}
			}
		}
	}
	// печать overline_u_0^(2) в файл в одну строчку
	ofstream f_overline_u_2("matrix_overline_u_2.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			f_overline_u_2 << fixed << setprecision(6) << overline_u[i][j] << " ";
		}
	}
	f_overline_u_2.close();
	timeFinish = clock();
	d = (float)(timeFinish - timeStart) / CLOCKS_PER_SEC;
	cout << "Finding the acoustic pressure in X " << d << endl;
	timeStart = clock();

	//Для третьего источника
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t k = 0; k <= N; ++k)
			{
				ii = i*(N + 1)*(N + 1) + j*(N + 1) + k;
				rightPartEquation[ii] = SourceFunction(source03, i * h, j * h, k * h);
			}
		}
	}
	// нахождение u^{(3)}
	SolveSlauGaussa(substantiveMatrix, rightPartEquation, numbered_u);
	//
	// Обратная перенумерация
	//
	for (size_t ii = 0; ii < N_cube; ++ii)
	{
		coordinate_x = ii / ((N + 1) * (N + 1));
		coordinate_y = (ii - coordinate_x * ((N + 1) * (N + 1))) / (N + 1);
		coordinate_z = ii % (N + 1);
		u[coordinate_x][coordinate_y][coordinate_z] = numbered_u[ii];
	}
	timeFinish = clock();
	d = (float)(timeFinish - timeStart) / CLOCKS_PER_SEC;
	cout << "Finding the acoustic pressure in R " << d << endl;
	timeStart = clock();


	// находим overline_u_0
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			overline_u[i][j] = SourceFunction(source03, i * h, j * h, receiver);;
		}
	}
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			for (size_t p = 0; p < N; ++p)
			{
				for (size_t q = 0; q < N; ++q)
				{
					for (size_t r = 0; r < N; ++r)
					{
						overline_u[i][j] -= overline_a[i][j][p][q][r] * xi[p][q][r] * u[p][q][r];
					}
				}
			}
		}
	}
	// печать overline_u_0^(3) в файл в одну строчку
	ofstream f_overline_u_3("matrix_overline_u_3.txt");
	for (size_t i = 0; i <= N; ++i)
	{
		for (size_t j = 0; j <= N; ++j)
		{
			f_overline_u_3 << fixed << setprecision(6) << overline_u[i][j] << " ";
		}
	}
	f_overline_u_3.close();
	timeFinish = clock();
	d = (float)(timeFinish - timeStart) / CLOCKS_PER_SEC;
	cout << "Finding the acoustic pressure in X " << d << endl;

	d = (float)(timeFinish - timeBegin) / CLOCKS_PER_SEC;
	cout << "The total time of the program " << d << endl;

	return 0;
}
