#pragma once
#include "stdafx.h"

struct EquationRoot4
{
	size_t numRoots = 0;
	double roots[4];
};

std::pair<boost::optional<double>, boost::optional<double>> Solve2(double a, double b, double c);
double Solve3(double a, double b, double c);
EquationRoot4 Solve4(double a, double b, double c, double d, double e);
void AddNewPairOfRoots(EquationRoot4 & equation, std::pair<boost::optional<double>, boost::optional<double>> const & roots);
