#pragma once

class CPoint
{
public:
	CPoint() = default;
	CPoint(double x = 0.0, double y = 0.0)
		: x(x)
		, y(y) {}
	~CPoint() = default;
	double x;
	double y;
};
