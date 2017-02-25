#include "stdafx.h"
#include "sourceFunction.h"

using namespace std;

complex<float> SourceFunction(const Point source, const float x, const float y, const float z)
{
	float dist = sqrtf(pow(x - source.x, 2) + pow(y - source.y, 2) + pow(z - source.z, 2));
	return -exp((0.0f, 1.0f) * OMEGA * dist / C_0) / (4 * PI * dist);
}
