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
	vector<double> coof(istream_iterator<double>(cin), (istream_iterator<double>()));
	EquationRoot4 roots = Solve4(coof[0], coof[1], coof[2], coof[3], coof[4]);
	ShowRoots(roots);
	return 0;
}
