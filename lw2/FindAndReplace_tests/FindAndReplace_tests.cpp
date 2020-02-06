#include "pch.h"
#include "../FindAndReplace/string_utils.h"

// не производит поиск в пустой строке
TEST_CASE("does not search in empty string")
{
	CHECK(FindAndReplace("", "replace", "something") == "");
}

// не ищет пустую строку
TEST_CASE("replacement of empty string should return subject")
{
	CHECK(FindAndReplace("subj", "", "something") == "subj");
}

// не меняет исходную строку, если строка поиска не найдена
TEST_CASE("does not change the original string if the search string is not found")
{
	CHECK(FindAndReplace("subject", "search", "replace") == "subject");
}

// заменяет одно вхождение строки поиска
TEST_CASE("replaces the entry search for replace")
{
	std::string subject = "I use different search engine.";
	const std::string correctString = "I use different replace engine.";
	CHECK(FindAndReplace(subject, "search", "replace") == correctString);
}

// заменяет все вхождение строки поиска на слово меньшей длины
TEST_CASE("replaces all occurrences of a search string in the word of shorter length")
{
	std::string subject = "Buffalo buffalo Buffalo buffalo buffalo buffalo Buffalo buffalo";
	const std::string correctString = "Buffalo bison Buffalo bison bison bison Buffalo bison";
	CHECK(FindAndReplace(subject, "buffalo", "bison") == correctString);
}

// заменяет все вхождение строки поиска на слово большей длины
TEST_CASE("replaces all occurrences of the search string word for a greater length")
{
	std::string subject = "Buffalo buffalo Buffalo buffalo buffalo buffalo Buffalo buffalo";
	const std::string correctString = "Buffalo amphibian Buffalo amphibian amphibian amphibian Buffalo amphibian";
	CHECK(FindAndReplace(subject, "buffalo", "amphibian") == correctString);
}
