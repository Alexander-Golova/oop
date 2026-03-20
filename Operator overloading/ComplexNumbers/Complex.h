#pragma once
#include <cmath>


class CComplex
{
public:
	CComplex(double real = 0.0, double image = 0.0);

	double Re() const;
	double Im() const;
	double GetMagnitude() const;
	double GetArgument() const;

	CComplex& operator+=(const CComplex& rhs);
	CComplex& operator-=(const CComplex& rhs);


private:
	double m_real;
	double m_imag;
};


CComplex const operator+(const CComplex& lhs, const CComplex& rhs);
CComplex const operator-(const CComplex& lhs, const CComplex& rhs);
CComplex const operator*(const CComplex& lhs, const CComplex& rhs);
CComplex const operator/(const CComplex& lhs, const CComplex& rhs);
