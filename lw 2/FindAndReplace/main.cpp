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

	auto findReplace = [](auto & subject) {
		return FindAndReplace(subject, search, replace)
	};
	transform(istream_iterator<string>(cin), istream_iterator<string>(), ostream_iterator<string>(cout), findReplace);

	return 0;
}
