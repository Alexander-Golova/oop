#include "stdafx.h"

#include "../FindAndReplace/string_utils.h"

BOOST_AUTO_TEST_SUITE(Test)

BOOST_AUTO_TEST_CASE(Find_And_Replace)
{
	{
		string subject = "big paws, big black nose, stubby tail, and growl he goes";
		auto newString = FindAndReplace(subject, "big", "small");
		const string correctString = "small paws, small black nose, stubby tail, and growl he goes";
		BOOST_CHECK(newString == correctString);
	}
	{
		string subject = "big paws, big black nose, stubby tail, and growl he goes";
		auto newString = FindAndReplace(subject, "paws", "ears");
		const string correctString = "big ears, big black nose, stubby tail, and growl he goes";
		BOOST_CHECK(newString == correctString);
	}
	{
		string subject = "1223344455566667777888899999...";
		auto newString = FindAndReplace(subject, "0", "000");
		const string correctString = "1223344455566667777888899999...";
		BOOST_CHECK(newString == correctString);
	}
	{
		string subject = "1223344455566667777888899999...";
		auto newString = FindAndReplace(subject, "6", "666");
		const string correctString = "122334445556666666666667777888899999...";
		BOOST_CHECK(newString == correctString);
	}
}

BOOST_AUTO_TEST_SUITE_END()
