#include "Equation.h"

EquationRoots Solve(double a, double b, double c)
{
	if (std::abs(a) < DBL_EPSILON)
	{
		throw std::invalid_argument("Coefficient 'a' cannot be zero: equation is not quadratic");
	}
	
	double D = b * b - 4.0 * a * c;
	if (D < 0.0)
	{
		throw std::domain_error("No real roots: discriminant = " + std::to_string(D));
	}
	
	EquationRoots result;
	if (D == 0.0)
	{
		result.numRoots = 1;
		result.roots[0] = -b / (2.0 * a);
	}
	else
	{		
		result.numRoots = 2;
		double sqrtD = std::sqrt(D);
		if (b >= 0.0)
		{
			result.roots[0] = (-b - sqrtD) / (2.0 * a);
			result.roots[1] = (2.0 * c) / (-b - sqrtD);
		}
		else
		{
			result.roots[0] = (-b + sqrtD) / (2.0 * a);
			result.roots[1] = (2.0 * c) / (-b + sqrtD);
		}
	}
	return result;
}
