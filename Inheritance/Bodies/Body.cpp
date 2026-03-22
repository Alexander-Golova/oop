#include "Body.h"

CBody::CBody(const std::string& type, double density)
	: m_density(density)
	, m_type(type)
{
}

double CBody::GetDensity() const
{
	return m_density;
}

double CBody::GetMass() const
{
	return GetVolume() * GetDensity();
}

std::string CBody::ToString() const
{
	std::ostringstream strm;
	strm << m_type << ":" << std::endl
		 << std::fixed << std::setprecision(2)
		 << "\tdensity = " << GetDensity() << std::endl
		 << "\tvolume = " << GetVolume() << std::endl
		 << "\tmass = " << GetMass() << std::endl;
	AppendProperties(strm);
	return strm.str();
}
