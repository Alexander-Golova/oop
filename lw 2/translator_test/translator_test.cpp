#include "stdafx.h"

#include "../translator/translator_utils.cpp"

using namespace std;

bool VectorsAreEqual(vector<string> const& x, vector<string> const& y)
{
	return x == y;
}

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
		BOOST_CHECK_EQUAL(ToLowCase("�����"), "�����");
	}
}

BOOST_AUTO_TEST_CASE(Adding_and_searching_for_words_in_the_dictionary)
{
	{
		Dictionary dictionary;
		AddWordToDictionaryy("cat", "���", dictionary);
		auto words = FindWordInDictionary("cat", dictionary);
		BOOST_CHECK(VectorsAreEqual(words, { "���" }));
	}
	{
		Dictionary dictionary;
		AddWordToDictionaryy("cat", "���", dictionary);
		auto words = FindWordInDictionary("���", dictionary);
		BOOST_CHECK(VectorsAreEqual(words, { "cat" }));
	}
	{
		Dictionary dictionary;
		AddWordToDictionaryy("���", "cat", dictionary);
		AddWordToDictionaryy("�����", "cat", dictionary);
		auto words = FindWordInDictionary("cat", dictionary);
		BOOST_CHECK(VectorsAreEqual(words, { "���", "�����" }));
	}
}

BOOST_AUTO_TEST_SUITE_END()