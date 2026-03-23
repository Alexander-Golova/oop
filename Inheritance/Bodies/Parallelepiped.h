#pragma once
#include "Body.h"


class CParallelepiped final : public CBody
{
	CParallelepiped(double width, double height, double depth, double density = 1);
	
	double GetVolume() const override;
	double GetWidth() const;
	double GetHeight() const;
	double GetDepth() const;

private:
	void AppendProperties(std::ostream& strm) const override;
	double m_width;
	double m_height;
	double m_depth;
};
