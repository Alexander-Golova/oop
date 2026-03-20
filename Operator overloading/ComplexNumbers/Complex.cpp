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

CComplex& CComplex::operator/=(const CComplex& rhs)
{
	*this = *this / rhs;
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

bool const operator==(const CComplex& lhs, const double rhs)
{
	return lhs == CComplex(rhs, 0);
}

bool const operator!=(const CComplex& lhs, const CComplex& rhs)
{
	return !(lhs == rhs);
}

bool const operator!=(const CComplex& lhs, const double rhs)
{
	return !(lhs == CComplex(rhs, 0));
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

CComplex const operator/(const CComplex& lhs, const double rhs)
{
	double re = lhs.Re() / rhs;
	double im = lhs.Im() / rhs;
	return CComplex(re, im);
}

std::ostream& operator<<(std::ostream& strm, const CComplex& rhs)
{
	strm << std::fixed << std::setprecision(1) << rhs.Re();
	if (rhs.Im() >= 0)
	{
		strm << '+';
	}
	strm << rhs.Im() << 'i';
	return strm;
}

std::istream& operator>>(std::istream& strm, CComplex& rhs)
{
	double re = 0.0;
	double im = 0.0;
	char sign = '+';
	char ch_i = '\0';

	std::ios old_state(nullptr);
	old_state.copyfmt(strm);

	if (strm >> re)
	{
		strm >> std::ws;
		if (strm.get(sign))
		{
			if (sign == '+' || sign == '-')
			{
				if (strm >> im)
				{
					strm >> std::ws;
					if (strm.get(ch_i))
					{
						if (ch_i == 'i' || ch_i == 'I')
						{
							rhs = CComplex(re, (sign == '-') ? -im : im);
						}
						else
						{
							strm.setstate(std::ios_base::failbit);
						}
					}
				}
			}
			else
			{
				strm.setstate(std::ios_base::failbit);
				strm.putback(sign);
			}
		}
	}
	if (strm.fail())
	{
		rhs = CComplex(0.0, 0.0);
		strm.copyfmt(old_state);
	}
	return strm;
}
