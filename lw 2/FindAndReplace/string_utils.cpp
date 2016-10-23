#include "stdafx.h"

#include "string_utils.h"

using namespace std;


bool CheckArgumentCount(const int argumentCount)
{

	if (argumentCount != 3)
	{
		cerr << "Invalid arguments count" << endl
		     << "Usage: replace <subject-string> <search-string> <replace-string>" << endl;
		return false;
	}
	return true;
}

string FindAndReplace(string const & subject, string const & search, string  const & replace)
{
	string newString = "";

	size_t leftPosition = 0;
	size_t rightPosition = 0;

	if (search.length() == 0)
	{
		return subject;
	}

	while (rightPosition != string::npos)
	{
		rightPosition = subject.find(search, leftPosition);
		if (rightPosition != string::npos)
		{
			newString.append(subject, leftPosition, rightPosition - leftPosition);
			newString += replace;
			leftPosition = rightPosition + search.length();
		}
	}

	newString.append(subject, leftPosition, subject.length());

	return newString;
}