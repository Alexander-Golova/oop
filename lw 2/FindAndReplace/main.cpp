#include "stdafx.h"

#include "string_utils.h"

int main(int argc, char *argv[])
{
	if (!CheckArgumentCount(argc) || !CheckReplacingString(argv[1]))
	{
		return 1;
	}

	string modifiedString = FindAndReplace(argv[1], argv[2], argv[3]);
	cout << modifiedString << endl;
	
	return 0;
}
