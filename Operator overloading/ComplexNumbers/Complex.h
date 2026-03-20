#pragma once
#include <cmath>


class CComplex
{
public:
	// инициализация комплексного числа значениями действительной и мнимой частей
	CComplex(double real = 0, double image = 0);

	// возвращает действительную часть комплексного числа
	double Re() const;

	// возвращает мнимую часть комплексного числа
	double Im() const;

	// возвращает модуль комплексного числа
	double GetMagnitude() const;

	// возвращает аргумент комплексного числа
	double GetArgument() const;

private:
	double m_real;
	double m_imag;
};


CComplex const operator+(const CComplex& lhs, const CComplex& rhs);
