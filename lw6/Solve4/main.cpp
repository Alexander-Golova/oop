#include "stdafx.h"
#include "Equation.h"

using namespace std;

void ShowRoots(EquationRoot4 const & roots)
{
	if (roots.numRoots)
	{
		cout << "Equation has " << roots.numRoots << " root" << (roots.numRoots > 1 ? "s" : "") << " : ";
		for (size_t i = 0; i < roots.numRoots; i++)
		{
			cout << roots.roots[i] << "  ";
		}
		cout << endl;
	}
}

int main()
{
	double a, b, c, d, e;
	while ((std::cin >> a) && (std::cin >> b) && (std::cin >> c) && (std::cin >> d) && (std::cin >> e))
	{
		ShowRoots(Solve4(a, b, c, d, e));
		cout << endl;
	}
	return 0;
}
