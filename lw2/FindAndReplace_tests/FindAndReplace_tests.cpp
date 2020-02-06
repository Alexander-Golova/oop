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
