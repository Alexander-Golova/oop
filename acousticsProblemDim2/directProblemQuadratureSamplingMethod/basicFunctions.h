#pragma once

struct Point
{
	float x;
	float y;
};

// ������� ������������� ����
const float OMEGA = 1.0f;
const float C_0 = 1.0f;

// ���������� ����������
const float receiver = 11.0f;

// ���������� ����������
const size_t NUMBER_SOURCE = 5;

// ���������� ����������� �� ������� ���������
const size_t NUMBER_PARTITION_POINTS = 50;

// ������ �������� � ������� ��������� ��������������
const float DOMAIN_IN_HOMOGENEITY = 10.0;

//������� �������
std::complex<float> Hankel(const float x);

// ������� �����
std::complex<float> G(const float x_1, const float x_2, const float y_1, const float y_2);
