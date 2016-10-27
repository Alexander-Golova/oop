#include "stdafx.h"

#include "../translator/translator_utils.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(MyTest)

BOOST_AUTO_TEST_CASE(Translations_into_lowercase_English_words)
{
	{
		BOOST_CHECK_EQUAL(ToLowCase("Cat"), "cat");
	}
	{
		BOOST_CHECK_EQUAL(ToLowCase("cAt"), "cat");
	}
	{
		BOOST_CHECK_EQUAL(ToLowCase("CAT"), "cat");
	}
	{
		BOOST_CHECK_EQUAL(ToLowCase("КошКа"), "КошКа");
	}
}

BOOST_AUTO_TEST_CASE(Adding_and_searching_for_words_in_the_dictionary)
{
	{
		Dictionary dictionary;
		AddWordToDictionaryy("cat", "кот", dictionary);
		auto words = FindWordInDictionary("cat", dictionary);
		const vector<string> expectedResult = {
			"кот"
		};
 		BOOST_CHECK(words == expectedResult);
	}
	{
		Dictionary dictionary;
		AddWordToDictionaryy("cat", "кот", dictionary);
		auto words = FindWordInDictionary("кот", dictionary);
		const vector<string> expectedResult = {
			"cat"
		};
		BOOST_CHECK(words == expectedResult);
	}
	{
		Dictionary dictionary;
		AddWordToDictionaryy("кот", "cat", dictionary);
		AddWordToDictionaryy("кошка", "cat", dictionary);
		auto words = FindWordInDictionary("cat", dictionary);
		const vector<string> expectedResult = {
			"кот", "кошка"
		};
		BOOST_CHECK(words == expectedResult);
	}
}

BOOST_AUTO_TEST_SUITE_END()