#include "stdafx.h"

#include "translator_utils.h"

bool CheckArgumentCount(const int argumentCount)
{
	if (argumentCount > 2)
	{
		cout << "Invalid argument count" << endl;
		cout << "translator [<input dictionary>]" << endl;
		return false;
	}
	return true;
}
