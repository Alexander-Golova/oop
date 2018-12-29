#include "stdafx.h"

#include "string_utils.h"

using namespace std;
using namespace std::placeholders;

int main(int argc, char *argv[])
{
	if (!CheckArgumentCount(argc))
	{
		return 1;
	}

	string search = argv[1];
	string replace = argv[2];
	string subject;
	while (getline(cin, subject))
	{
		cout << FindAndReplace(subject, search, replace) << endl;
	}
	return 0;
}
