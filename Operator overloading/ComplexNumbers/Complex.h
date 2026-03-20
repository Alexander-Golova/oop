#pragma once
#include <cmath>
#include <iostream>
#include <iomanip>


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
	CComplex& operator*=(const CComplex& rhs);
	CComplex& operator/=(const CComplex& rhs);

	CComplex const operator-() const;
	CComplex const operator+() const;



private:
	double m_real;
	double m_imag;
};


CComplex const operator+(const CComplex& lhs, const CComplex& rhs);
CComplex const operator+(const CComplex& lhs, const double rhs);
CComplex const operator-(const CComplex& lhs, const CComplex& rhs);
CComplex const operator-(const CComplex& lhs, const double rhs);
CComplex const operator*(const CComplex& lhs, const CComplex& rhs);
CComplex const operator*(const CComplex& lhs, const double rhs);
CComplex const operator/(const CComplex& lhs, const CComplex& rhs);
CComplex const operator/(const CComplex& lhs, const double rhs);

bool const operator==(const CComplex& lhs, const CComplex& rhs);
bool const operator==(const CComplex& lhs, const double rhs);
bool const operator!=(const CComplex& lhs, const CComplex& rhs);
bool const operator!=(const CComplex& lhs, const double rhs);

std::ostream& operator<<(std::ostream& strm, const CComplex& rhs);
std::istream& operator>>(std::istream& strm, CComplex& rhs);