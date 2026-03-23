#include "Parallelepiped.h"

CParallelepiped::CParallelepiped(double width, double height, double depth, double density)
	: CBody("Parallelepiped", density)
	, m_width(width)
	, m_height(height)
	, m_depth(depth)
{}

double CParallelepiped::GetVolume() const
{
	return m_width * m_height * m_depth;
}

double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

double CParallelepiped::GetDepth() const
{
	return m_depth;
}

void CParallelepiped::AppendProperties(std::ostream& strm) const
{
	strm << "\twidth = " << m_width << std::endl
		 << "\theight = " << m_height << std::endl
		 << "\tdepth = " << m_depth << std::endl;		
}
