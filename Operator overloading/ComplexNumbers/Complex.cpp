#include "Complex.h"

CComplex::CComplex(double real, double image)
	: m_real(real)
	, m_imag(image) {};

double CComplex::Re() const
{
	return m_real;
};

double CComplex::Im() const
{
	return m_imag;
};

double CComplex::GetMagnitude() const
{
	return std::hypot(m_real, m_imag);
}

double CComplex::GetArgument() const
{
	return std::atan2(m_imag, m_real);
}

CComplex const operator+(const CComplex& lhs, const CComplex& rhs)
{
	double re = lhs.Re() + rhs.Re();
	double im = lhs.Im() + rhs.Im();
	return CComplex(re, im);
}