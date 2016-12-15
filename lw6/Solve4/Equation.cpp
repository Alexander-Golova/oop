#include "stdafx.h"

#include "Equation.h"
#include <array>

using namespace std;

boost::optional<pair<double, double>> Solve2(double a, double b, double c)
{
	double D = b * b - 4 * a * c;
	if (D == 0)
	{
		return make_pair(-b / (2 * a), -b / (2 * a));
	}
	else if (D > 0)
	{
		return make_pair((-b + sqrt(D)) / (2 * a), (-b - sqrt(D)) / (2 * a));
	}
	return boost::none;
}

double Solve3(double a, double b, double c)
{
	array<double, 3> roots;
	double q = (pow(a, 2) - 3.0 * b) / 9.0;
	double r = (2.0 * pow(a, 3) - 9.0 * a * b + 27.0 * c) / 54.0;
	double s = pow(q, 3) - pow(r, 2);
	if (s > 0)
	{
		double t = acos(r / sqrt(pow(q, 3))) / 3.0;
		roots[0] = -2 * sqrt(q) * cos(t) - a / 3.0;
		roots[1] = -2 * sqrt(q) * cos(t + 2 * M_PI / 3.0) - a / 3.0;
		roots[2] = -2 * sqrt(q) * cos(t - 2 * M_PI / 3.0) - a / 3.0;
	}
	else if (s < 0)
	{
		if (q > 0)
		{
			double t = acosh(abs(r) / sqrt(pow(q, 3))) / 3.0;
			roots[0] = -2 * ((r > 0) ? 1 : ((r < 0) ? -1 : 0)) * sqrt(q) * cosh(t) - a / 3.0;
		}
		if (q < 0)
		{
			double t = asinh(abs(r) / sqrt(pow(abs(q), 3))) / 3.0;
			roots[0] = -2 * ((r > 0) ? 1 : ((r < 0) ? -1 : 0)) * sqrt(abs(q)) * sinh(t) - a / 3.0;
		}
		if (q == 0)
		{
			roots[0] = -pow((c - pow(a, 3) / 27), 1 / 3.0) - a / 3.0;
		}
	}
	else
	{
		roots[0] = -2 * ((r > 0) ? 1 : ((r < 0) ? -1 : 0)) * sqrt(q) - a / 3.0;
		roots[1] = ((r > 0) ? 1 : ((r < 0) ? -1 : 0)) * sqrt(q) - a / 3.0;
	}
	return *max_element(roots.begin(), roots.end());
}

EquationRoot4 Solve4(double a, double b, double c, double d, double e)
{
	if (a == 0)
	{
		throw invalid_argument("Argument 'a' can not be 0.");
	}
	EquationRoot4 result;
	
	double inv = a;
	a = b / inv;
	b = c / inv;
	c = d / inv;
	d = e / inv;

	double y = Solve3(-b, a * c - 4 * d, 4 * b * d - a * a * d - c * c);
	double alpha = sqrt(a * a / 4 - b + y);
	double beta = sqrt(y * y / 4 - d);
	if ((a * y / 2 - c) < 0)
	{
		beta *= -1;
	}
	AddNewPairOfRoots(result, Solve2(1, a / 2 + alpha, y / 2 + beta));
	AddNewPairOfRoots(result, Solve2(1, a / 2 - alpha, y / 2 - beta));

	sort(begin(result.roots), begin(result.roots) + result.numRoots);
	try
	{
		if (result.numRoots == 0)
		{
			throw domain_error("Equation does not have of real roots");
		}
	}
	catch (const domain_error & ex)
	{
		cout << ex.what() << endl;
	}
	return result;
}

void AddNewPairOfRoots(EquationRoot4 & equation, boost::optional<pair<double, double>> const & roots)
{
	if (roots != boost::none)
	{
		equation.roots[equation.numRoots++] = roots.get().first;
		equation.roots[equation.numRoots++] = roots.get().second;
	}
}
