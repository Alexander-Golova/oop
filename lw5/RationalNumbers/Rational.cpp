#include "stdafx.h"
#include "Rational.h"
#include <utility>
#include <stdexcept>
#include <cassert>


CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator must not be equal to zero");
	}
	if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}
	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

void CRational::Normalize()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}

unsigned LCM(unsigned a, unsigned b)
{
	return a / GCD(a, b) * b;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
//////////////////////////////////////////////////////////////////////////

double CRational::ToDouble()const
{
	return static_cast<double>(m_numerator) / m_denominator;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
//////////////////////////////////////////////////////////////////////////

CRational const CRational::operator-()const
{
	return CRational(-m_numerator, m_denominator);
}

CRational const CRational::operator+()const
{
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 3. Реализовать бинарный +
//////////////////////////////////////////////////////////////////////////

CRational const operator+(const CRational & lhs, const CRational & rhs)
{
	int lcm = LCM(lhs.GetDenominator(), rhs.GetDenominator());
	int numerator = lcm / lhs.GetDenominator() * lhs.GetNumerator()
	              + lcm / rhs.GetDenominator() * rhs.GetNumerator();
	return CRational(numerator, lcm);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
//////////////////////////////////////////////////////////////////////////

CRational const operator-(const CRational & lhs, const CRational & rhs)
{
	int lcm = LCM(lhs.GetDenominator(), rhs.GetDenominator());
	int numerator = lcm / lhs.GetDenominator() * lhs.GetNumerator()
		          - lcm / rhs.GetDenominator() * rhs.GetNumerator();
	return CRational(numerator, lcm);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
//////////////////////////////////////////////////////////////////////////

CRational & CRational::operator+=(const CRational & rhs)
{
	*this = *this + rhs;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
//////////////////////////////////////////////////////////////////////////

CRational & CRational::operator-=(CRational const & rhs)
{
	*this = *this - rhs;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
//////////////////////////////////////////////////////////////////////////

CRational const operator*(const CRational & lhs, const CRational & rhs)
{
	return (CRational(lhs.GetNumerator() * rhs.GetNumerator(), lhs.GetDenominator() * rhs.GetDenominator()));
}

//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
//////////////////////////////////////////////////////////////////////////

CRational const operator/(const CRational & lhs, const CRational & rhs)
{
	return (CRational(lhs.GetNumerator() * rhs.GetDenominator(), lhs.GetDenominator() * rhs.GetNumerator()));
}

//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
//////////////////////////////////////////////////////////////////////////

CRational & CRational::operator *=(const CRational & rhs)
{
	m_numerator *= rhs.GetNumerator();
	m_denominator *= rhs.GetDenominator();
	Normalize();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
//////////////////////////////////////////////////////////////////////////

CRational & CRational::operator/=(const CRational & rhs)
{
	if (*this == rhs)
	{
		m_numerator = m_denominator = 1;
		return *this;
	}
	if (rhs.GetNumerator() == 0)
	{
		throw std::invalid_argument("Denominator must not be equal to zero");
	}
	m_numerator *= rhs.GetDenominator();
	m_denominator *= rhs.GetNumerator();
	Normalize();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
//////////////////////////////////////////////////////////////////////////

bool const operator==(const CRational & lhs, const CRational & rhs)
{
	return (lhs.GetNumerator() == rhs.GetNumerator() && lhs.GetDenominator() == rhs.GetDenominator());
}

bool const operator!=(const CRational & lhs, const CRational & rhs)
{
	return !(lhs == rhs);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
//////////////////////////////////////////////////////////////////////////

bool const operator<(const CRational & lhs, const CRational & rhs)
{
	return (lhs.GetNumerator() * rhs.GetDenominator() < rhs.GetNumerator() * lhs.GetDenominator());
}

bool const operator<=(const CRational & lhs, const CRational & rhs)
{
	return (lhs == rhs || lhs < rhs);
}

bool const operator>(const CRational & lhs, const CRational & rational2)
{
	return !(lhs <= rational2);
}

bool const operator>=(const CRational & lhs, const CRational & rhs)
{
	return (lhs == rhs || lhs > rhs);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//////////////////////////////////////////////////////////////////////////

std::ostream & operator<<(std::ostream & strm, const CRational & rhs)
{
	strm << rhs.GetNumerator() << '/' << rhs.GetDenominator();
	return strm;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//////////////////////////////////////////////////////////////////////////

std::istream & operator>>(std::istream & strm, CRational & rhs)
{
	int numerator;
	int denominator;
	if ((strm >> numerator) && (strm.get() == '/') && (strm >> denominator))
	{
		rhs = CRational(numerator, denominator);
	}
	else
	{
		strm.setstate(std::ios_base::failbit);
	}
	return strm;
}

// Реализовать возможность получения смешанной дроби из рационального числа
std::pair<int, CRational> CRational::ToCompoundFraction()const
{
	int integer = static_cast<int>(ToDouble());
	int numerator = m_numerator - m_denominator * integer;
	return std::make_pair(std::move(integer), CRational(numerator, m_denominator));
}
