#pragma once

#include <boost/optional.hpp>

struct EquationRoot4
{
	size_t numRoots = 0;
	double roots[4];
};

boost::optional<std::pair<double, double>> Solve2(double a, double b, double c);
double Solve3(double a, double b, double c);
EquationRoot4 Solve4(double a, double b, double c, double d, double e);
void AddNewPairOfRoots(EquationRoot4 & equation, boost::optional<std::pair<double, double>> const & roots);
