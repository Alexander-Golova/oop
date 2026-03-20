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
	return CComplex(lhs.Re() + rhs.Re(), lhs.Im() + rhs.Im());
}

CComplex const operator-(const CComplex& lhs, const CComplex& rhs)
{
	return CComplex(lhs.Re() - rhs.Re(), lhs.Im() - rhs.Im());
}

CComplex const operator*(const CComplex& lhs, const CComplex& rhs)
{
	double re = lhs.Re() * rhs.Re() - lhs.Im() * rhs.Im();
	double im = lhs.Re() * rhs.Im() + lhs.Im() * rhs.Re();
	return CComplex(re, im);
}

CComplex const operator/(const CComplex& lhs, const CComplex& rhs)
{
	double denom = rhs.Re() * rhs.Re() + rhs.Im() * rhs.Im();
	double re = (lhs.Re() * rhs.Re() + lhs.Im() * rhs.Im()) / denom;		
	double im = (lhs.Im() * rhs.Re() - lhs.Re() * rhs.Im()) / denom;
	return CComplex(re, im);		
}

CComplex& CComplex::operator+=(const CComplex& rhs)
{
	*this = *this + rhs;
	return *this;
}

CComplex& CComplex::operator-=(const CComplex& rhs)
{
	*this = *this - rhs;
	return *this;
}

CComplex& CComplex::operator*=(const CComplex& rhs)
{
	*this = *this * rhs;
	return *this;
}

CComplex const CComplex::operator-() const
{
	return CComplex(-m_real, -m_imag);
}

CComplex const CComplex::operator+() const
{
	return *this;
}

bool const operator==(const CComplex& lhs, const CComplex& rhs)
{
	return (lhs.Re() == rhs.Re() && lhs.Im() == rhs.Im());
}

bool const operator!=(const CComplex& lhs, const CComplex& rhs)
{
	return !(lhs == rhs);
}

CComplex const operator+(const CComplex& lhs, const double rhs)
{
	return lhs + CComplex(rhs, 0);
}

CComplex const operator-(const CComplex& lhs, const double rhs)
{
	return lhs - CComplex(rhs, 0);
}

CComplex const operator*(const CComplex& lhs, const double rhs)
{
	double re = lhs.Re() * rhs;
	double im = lhs.Im() * rhs;
	return CComplex(re, im);
}
