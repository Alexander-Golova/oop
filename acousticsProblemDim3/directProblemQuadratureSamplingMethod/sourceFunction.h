#pragma once
#include "basicFunctions.h"

// координаты источников, и фунция, характеризующая источник

const Point source01 = { 0.0f, 0.0f, 1.1f };
const Point source02 = { 1.0f, 0.0f, 1.1f };
const Point source03 = { 0.0f, 1.0f, 1.1f };


std::complex<float> SourceFunction(const Point source, const float x, const float y, const float z);
