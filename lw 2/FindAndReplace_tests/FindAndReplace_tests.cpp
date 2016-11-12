#include "stdafx.h"

#include "../FindAndReplace/string_utils.h"

using namespace std;

// функция Find_And_Replace
BOOST_AUTO_TEST_SUITE(Find_And_Replace_function)

	// не производит поиск в пустой строке
	BOOST_AUTO_TEST_CASE(does_not_search_in_empty_string)
	{
		BOOST_CHECK_EQUAL(FindAndReplace("", "replace", "something"), "");
	}

	// не ищет пустую строку
	BOOST_AUTO_TEST_CASE(replacement_of_empty_string_should_return_subject)
	{
		BOOST_CHECK_EQUAL(FindAndReplace("subj", "", "something"), "subj");
	}

	// не меняет исходную строку, если строка поиска не найдена 
	BOOST_AUTO_TEST_CASE(does_not_change_the_original_string_if_the_search_string_is_not_found)
	{
		BOOST_CHECK_EQUAL(FindAndReplace("subject", "search", "replace"), "subject");
	}

	// заменяет одно вхождение строки поиска
	BOOST_AUTO_TEST_CASE(replaces_the_entry_search_for_replace)
	{
		string subject = "I use different search engine.";
		const string correctString = "I use different replace engine.";
		BOOST_CHECK_EQUAL(FindAndReplace(subject, "search", "replace"), correctString);
	}

	// заменяет все вхождение строки поиска на слово меньшей длины
	BOOST_AUTO_TEST_CASE(replaces_all_occurrences_of_a_search_string_in_the_word_of_shorter_length)
	{
		string subject = "Buffalo buffalo Buffalo buffalo buffalo buffalo Buffalo buffalo";
		const string correctString = "Buffalo bison Buffalo bison bison bison Buffalo bison";
		BOOST_CHECK_EQUAL(FindAndReplace(subject, "buffalo", "bison"), correctString);
	}

	// заменяет все вхождение строки поиска на слово большей длины
	BOOST_AUTO_TEST_CASE(replaces_all_occurrences_of_the_search_string_word_for_a_greater_length)
	{
		string subject = "Buffalo buffalo Buffalo buffalo buffalo buffalo Buffalo buffalo";
		const string correctString = "Buffalo amphibian Buffalo amphibian amphibian amphibian Buffalo amphibian";
		BOOST_CHECK_EQUAL(FindAndReplace(subject, "buffalo", "amphibian"), correctString);
	}

BOOST_AUTO_TEST_SUITE_END()
