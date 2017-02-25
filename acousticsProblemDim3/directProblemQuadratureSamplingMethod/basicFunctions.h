#pragma once

struct Point
{
	float x;
	float y;
	float z;
};

const float PI = 3.1415926f;
const float OMEGA = 1.0f;
const float C_0 = 1.0f;

// размер куба в котором находится неоднородность
const float a_R = 1.0f;

// координаты приемников
const float receiver = -0.1f;

const size_t NUMBER_PARTITION_POINTS = 10;

// функция Грина
std::complex<float> G(float x_1, float x_2, float x_3, float y_1, float y_2, float y_3);
