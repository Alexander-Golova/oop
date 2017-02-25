#include "stdafx.h"
#include "basicFunctions.h"

std::complex<float> G(float x_1, float x_2, float x_3, float y_1, float y_2, float y_3)
{
	float dist = sqrtf(pow(x_1 - y_1, 2) + pow(x_2 - y_2, 2) + pow(x_3 - y_3, 2));
	return -OMEGA * OMEGA * exp((0.0f, 1.0f) * OMEGA * dist / C_0) / (4 * PI * dist);
}
