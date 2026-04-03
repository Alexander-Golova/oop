#include "LineSegment.h"


CLineSegment::CLineSegment(CPoint const& startPoint, CPoint const& endPoint, uint32_t const outlineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(outlineColor)
{}


