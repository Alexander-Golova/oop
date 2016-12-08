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
// TODO: 1. ����������� ����� ToDouble() �������� �������
//////////////////////////////////////////////////////////////////////////

double CRational::ToDouble()const
{
	return static_cast<double>(m_numerator) / m_denominator;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 2. ����������� ������� + � ������� -
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
// TODO: 3. ����������� �������� +
//////////////////////////////////////////////////////////////////////////

CRational const operator+(const CRational & lhs, const CRational & rhs)
{
	int lcm = LCM(lhs.GetDenominator(), rhs.GetDenominator());
	int numerator = lcm / lhs.GetDenominator() * lhs.GetNumerator()
	              + lcm / rhs.GetDenominator() * rhs.GetNumerator();
	return CRational(numerator, lcm);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 4. ����������� �������� -
//////////////////////////////////////////////////////////////////////////

CRational const operator-(const CRational & lhs, const CRational & rhs)
{
	int lcm = LCM(lhs.GetDenominator(), rhs.GetDenominator());
	int numerator = lcm / lhs.GetDenominator() * lhs.GetNumerator()
		          - lcm / rhs.GetDenominator() * rhs.GetNumerator();
	return CRational(numerator, lcm);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 5. ����������� �������� +=
//////////////////////////////////////////////////////////////////////////

CRational & CRational::operator+=(const CRational & rhs)
{
	*this = *this + rhs;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 6. ����������� �������� -=
//////////////////////////////////////////////////////////////////////////

CRational & CRational::operator-=(CRational const & rhs)
{
	*this = *this - rhs;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 7. ����������� �������� *
//////////////////////////////////////////////////////////////////////////

CRational const operator*(const CRational & lhs, const CRational & rhs)
{
	return (CRational(lhs.GetNumerator() * rhs.GetNumerator(), lhs.GetDenominator() * rhs.GetDenominator()));
}

//////////////////////////////////////////////////////////////////////////
// TODO: 8. ����������� �������� /
//////////////////////////////////////////////////////////////////////////

CRational const operator/(const CRational & lhs, const CRational & rhs)
{
	return (CRational(lhs.GetNumerator() * rhs.GetDenominator(), lhs.GetDenominator() * rhs.GetNumerator()));
}

//////////////////////////////////////////////////////////////////////////
// TODO: 9. ����������� �������� *=
//////////////////////////////////////////////////////////////////////////

CRational & CRational::operator *=(const CRational & rhs)
{
	m_numerator *= rhs.GetNumerator();
	m_denominator *= rhs.GetDenominator();
	Normalize();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 10. ����������� �������� /=
//////////////////////////////////////////////////////////////////////////

CRational & CRational::operator/=(const CRational & rhs)
{
	m_numerator *= rhs.GetDenominator();
	m_denominator *= rhs.GetNumerator();
	if (m_denominator == 0)
	{
		throw std::invalid_argument("Denominator must not be equal to zero");
	}
	Normalize();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 11. ����������� ��������� == � !=
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
// TODO: 12. ����������� ��������� <, >, <=, >=
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
// TODO: 13. ����������� �������� ������ ������������� ����� � �������� ����� 
//////////////////////////////////////////////////////////////////////////

std::ostream & operator<<(std::ostream & strm, const CRational & rhs)
{
	strm << rhs.GetNumerator() << '/' << rhs.GetDenominator();
	return strm;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 14. ����������� �������� ����� ������������� ����� �� �������� ������ 
//////////////////////////////////////////////////////////////////////////

std::istream & operator>>(std::istream & strm, CRational & rhs)
{
	std::streamoff startPos = strm.tellg();
	int numerator;
	int denominator;
	if ((strm >> numerator) && (strm.get() == '/') && (strm >> denominator))
	{
		rhs = CRational(numerator, denominator);
		return strm;
	}
	strm.seekg(startPos);
	return strm;
}

// ����������� ����������� ��������� ��������� ����� �� ������������� �����
std::pair<int, CRational> CRational::ToCompoundFraction()const
{
	int integer = static_cast<int>(ToDouble());
	int numerator = m_numerator - m_denominator * integer;
	return std::make_pair<int, CRational>(std::move(integer), CRational(numerator, m_denominator));
}
