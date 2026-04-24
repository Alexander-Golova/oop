#include "Rational.h"

CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{};

CRational::CRational(int value)
	: m_numerator(value)
	, m_denominator(1)
{};
	
CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{};

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return static_cast<double>(m_numerator / m_denominator);
}

CRational const operator+(const CRational& lhs, const CRational& rhs)
{
	int denominator = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
	int numerator = denominator / lhs.GetDenominator() * lhs.GetNumerator() + denominator / rhs.GetDenominator() * rhs.GetNumerator();
	int div = std::gcd(denominator, numerator);
	return CRational(numerator / div, denominator / div);
}

CRational const operator-(const CRational& lhs, const CRational& rhs)
{
	int denominator = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
	int numerator = denominator / lhs.GetDenominator() * lhs.GetNumerator() - denominator / rhs.GetDenominator() * rhs.GetNumerator();
	int div = std::gcd(denominator, numerator);
	return CRational(numerator / div, denominator / div);
}

CRational const operator*(const CRational& lhs, const CRational& rhs)
{
	int numerator = lhs.GetNumerator()	/ std::gcd(rhs.GetDenominator(), lhs.GetNumerator());
	int denominator = rhs.GetDenominator() / std::gcd(rhs.GetDenominator(), lhs.GetNumerator());
	numerator *= (rhs.GetNumerator() / std::gcd(rhs.GetNumerator(), lhs.GetDenominator()));
	denominator *= (lhs.GetDenominator() / std::gcd(rhs.GetNumerator(), lhs.GetDenominator()));
	return CRational(numerator, denominator);
}

CRational const operator/(const CRational& lhs, const CRational& rhs)
{
	int numerator = lhs.GetNumerator() * rhs.GetDenominator();
	int denominator = lhs.GetDenominator() * rhs.GetNumerator();
	int div = std::gcd(denominator, numerator);
	return CRational(numerator / div, denominator / div);
}
