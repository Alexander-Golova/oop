#pragma once

#include "stdafx.h"

using namespace std;


bool CheckArgumentCount(const int argumentCount)
{

	if (argumentCount != 4)
	{
		cerr << "Invalid arguments count" << endl
			 << "Usage: replace <subject-string> <search-string> <replace-string>" << endl;
		return false;
	}
	return true;
}

bool CheckReplacingString(const string & str)
{
	if (str == "")
	{
		return true;
	}
	return false;
}

string FindAndReplace(string const & subject, string const & search, string  const & replace)
{
	string newString = "";

	int leftPosition = 0;
	int rightPosition = subject.find(search, 0);
	
	while (rightPosition != string::npos)
	{
		cout << rightPosition << endl;
		newString += subject.substr(leftPosition, rightPosition);
		newString += replace;
		leftPosition = rightPosition + search.length();
		rightPosition = subject.find(search, leftPosition);
	}
	if (rightPosition == string::npos)
	{
		newString += subject.substr(leftPosition, rightPosition);
	}

	return newString;
}
