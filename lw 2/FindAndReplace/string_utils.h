#pragma once

#include "stdafx.h"
#include <boost/algorithm/searching/boyer_moore.hpp>

using namespace std;

string FindAndReplace(string const & subject, string const & search, string  const & replace)
{
	string newString = "";
	boost::algorithm::boyer_moore<std::string::const_iterator> search1(search.begin(), search.end());
	if (search1(subject.begin(), subject.end()) != subject.end())
		std::cout << "Found '" << search << "'  in '" << subject << "' (boyer-moore)" << std::endl;
	else
		std::cout << "Did NOT find '" << search << "'  in '" << subject << "' (boyer-moore)" << std::endl;



	return newString;
}
