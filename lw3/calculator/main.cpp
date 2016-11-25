#include "stdafx.h"
#include "calculator.h"
#include "CalcMenu.h"

using namespace std;

int main()
{
	CCalculator calc;
	CCalcMenu control—alculator(calc, cin, cout);

	while ((!cin.eof()) && (!cin.fail()))
	{
		if (!control—alculator.RunCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}

    return 0;
}
