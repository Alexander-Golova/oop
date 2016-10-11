#include "stdafx.h"

BOOST_AUTO_TEST_SUITE(Test)

BOOST_AUTO_TEST_CASE(Math_operators)
{
	{
		const auto expectedResult = true;
		BOOST_CHECK(true == expectedResult);
	}

	{
		const auto expectedResult = 4;
		BOOST_CHECK(2 + 2 == expectedResult);
	}

	{
		BOOST_CHECK(10 / 5 == 2);
	}

	{
		BOOST_CHECK(2 * 2 == 4);
	}
}

BOOST_AUTO_TEST_CASE(other_example)
{
	{
		BOOST_CHECK(true != false);
	}
}

BOOST_AUTO_TEST_SUITE_END()
