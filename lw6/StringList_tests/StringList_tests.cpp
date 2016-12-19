#include "stdafx.h"
#include "../StringList/StringList.h"

using namespace std;

struct EmptyStringList
{
	CStringList list;
};

BOOST_FIXTURE_TEST_SUITE(String_list, EmptyStringList)

	BOOST_AUTO_TEST_SUITE(when_created)

		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK_EQUAL(list.GetSize(), 0u);
			BOOST_CHECK(list.IsEmpty());
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_appeding_a_string)

		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.GetSize();
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_method)
		{
			list.Append("hello");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
			list.Append("goodbye");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "goodbye");
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.Append("hello");
			auto it = list.begin();
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.GetBackElement()));
		}
		
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_push_front_a_string)

		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.GetSize();
			list.PushFront("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			list.PushFront("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
		}
		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_and_GetFrontElement_method)
		{
			list.PushFront("hello");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
			list.PushFront("goodbye");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "goodbye");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct when_not_empty : EmptyStringList
	{
		when_not_empty()
		{
			list.Append("first");
			list.Append("second");
			list.Append("third");
		}

		std::vector<std::string> expectedStrings = { "first", "second", "third" };
	};
	BOOST_FIXTURE_TEST_SUITE(when_not_empty_, when_not_empty)
		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			BOOST_CHECK(!list.IsEmpty());
			list.Clear();
			BOOST_CHECK(list.IsEmpty());
		}
	BOOST_AUTO_TEST_CASE(can_insert_element_at_iterator_pos)
	{
		auto it = ++list.begin();
		list.Insert(it, "2");
		BOOST_CHECK_EQUAL(*++list.begin(), "2");

		list.Insert(list.begin(), "1");
		BOOST_CHECK_EQUAL(*list.begin(), "1");

		list.Insert(list.end(), "6");

		std::vector<std::string> expectedStrings = { "1", "first", "2", "second", "third", "6" };
		size_t i = 0;
		for (auto str : list)
		{
			BOOST_CHECK_EQUAL(str, expectedStrings[i]);
			i++;
		}
	}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(iterator)
		BOOST_AUTO_TEST_CASE(can_be_increnenting)
		{
			list.Append("first");
			list.Append("second");
			auto iter = list.begin();
			BOOST_CHECK_EQUAL(*iter, "first");
			++iter;
			BOOST_CHECK_EQUAL(*iter, "second");
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
