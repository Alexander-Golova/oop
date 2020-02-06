#include "pch.h"
#include "../FindAndReplace/string_utils.h"

// �� ���������� ����� � ������ ������
TEST_CASE("does not search in empty string")
{
	CHECK(FindAndReplace("", "replace", "something") == "");
}

// �� ���� ������ ������
TEST_CASE("replacement of empty string should return subject")
{
	CHECK(FindAndReplace("subj", "", "something") == "subj");
}
