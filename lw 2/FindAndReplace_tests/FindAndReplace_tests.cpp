#include "stdafx.h"

#include "../FindAndReplace/string_utils.cpp"

BOOST_AUTO_TEST_SUITE(MyTest)

BOOST_AUTO_TEST_CASE(replacing_empty_string_should_return_subject)
{
	BOOST_CHECK_EQUAL(FindAndReplace("subj", "", "something"), "subj");
}

BOOST_AUTO_TEST_CASE(Find_And_Replace)
{
	{
		string subject = "123456789";
		auto newString = FindAndReplace(subject, "1", "");
		const string correctString = "23456789";
		BOOST_CHECK(newString == correctString);
	}
	{
		string subject = "123456789";
		auto newString = FindAndReplace(subject, "1", "0");
		const string correctString = "023456789";
		BOOST_CHECK(newString == correctString);
	}
	{
		string subject = "123456789";
		auto newString = FindAndReplace(subject, "1", "0000");
		const string correctString = "000023456789";
		BOOST_CHECK(newString == correctString);
	}
	{
		string subject = "123456789";
		auto newString = FindAndReplace(subject, "0", "000");
		const string correctString = "123456789";
		BOOST_CHECK(newString == correctString);
	}
	{
		string subject = "1234526789";
		auto newString = FindAndReplace(subject, "2", "000");
		const string correctString = "10003450006789";
		BOOST_CHECK(newString == correctString);
	}

}

BOOST_AUTO_TEST_SUITE_END()
