#include "stdafx.h"
#include "string_utils.h"


int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		cerr << "Invalid arguments count" << endl
			 << "Usage: replace <subject-string> <search-string> <replace-string>" << endl;
		return 1;
	}
	string subjectString = argv[1];
	if (subjectString.empty())
	{
		cerr << "Subject string must be not empty" << endl;
		return 1;
	}
	string searchString = argv[2];
	if (searchString.empty())
	{
		cerr << "Searching string must be not empty" << endl;
		return 1;
	}
	string replaceString = argv[3];
	if (replaceString.empty())
	{
		cerr << "Replace string must be not empty" << endl;
		return 1;
	}

	string modifiedString = FindAndReplace(subjectString, searchString, replaceString);
	cout << modifiedString << endl;

	return 0;
}

