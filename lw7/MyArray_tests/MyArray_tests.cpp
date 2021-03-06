﻿#include "stdafx.h"
#include "../MyArray/MyArray.h"

using namespace std;

struct ArrayItem
{
	ArrayItem(int value = 0) : value(value)
	{}
	int value;
};

struct EmptyStringArray
{
	CMyArray<ArrayItem> arr;
};

BOOST_FIXTURE_TEST_SUITE(MyArray, EmptyStringArray)

	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK_EQUAL(arr.GetSize(), 0u);
		}
		BOOST_AUTO_TEST_CASE(has_0_capacity)
		{
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 0u);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_appending_an_item)
		BOOST_AUTO_TEST_CASE(increases_its_size_and_capacity)
		{
			arr.Append(ArrayItem());
			BOOST_CHECK_EQUAL(arr.GetSize(), 1u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 1u);
			arr.Append(ArrayItem());
			BOOST_CHECK_EQUAL(arr.GetSize(), 2u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 2u);
			arr.Append(ArrayItem());
			BOOST_CHECK_EQUAL(arr.GetSize(), 3u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);
			arr.Append(ArrayItem());
			BOOST_CHECK_EQUAL(arr.GetSize(), 4u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);
		}
		BOOST_AUTO_TEST_CASE(it_becomes_available_at_the_back)
		{
			arr.Append(1);
			BOOST_CHECK_EQUAL(arr.GetBack().value, 1);
			arr.Append(2);
			BOOST_CHECK_EQUAL(arr.GetBack().value, 2);
			arr.Append(3);
			BOOST_CHECK_EQUAL(arr.GetBack().value, 3);
			arr.Append(4);
			BOOST_CHECK_EQUAL(arr.GetBack().value, 4);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_copy_construction)
		BOOST_AUTO_TEST_CASE(has_size_capacity_equal_to_size_of_original_array)
		{
			for (auto i = 0; i < 6; ++i)
			{
				arr.Append(i);
			}
			BOOST_CHECK_NE(arr.GetSize(), arr.GetCapacity());

			auto copy(arr);
			BOOST_CHECK_EQUAL(copy.GetSize(), arr.GetSize());
			BOOST_CHECK_EQUAL(copy.GetCapacity(), arr.GetSize());
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct IntMyArray_
	{
		CMyArray<int> arr;
	};

	struct IntMyArray_filled_ : IntMyArray_
	{
		IntMyArray_filled_()
		{
			arr.Append(1);
			arr.Append(2);
			arr.Append(3);
		}
	};
	// при заполнении элементов
	BOOST_FIXTURE_TEST_SUITE(when_filled_with_elements, IntMyArray_filled_)
		// имеет размер, равный количеству элементов
		BOOST_AUTO_TEST_CASE(has_size_equal_number_of_elements)
		{
			BOOST_CHECK_EQUAL(arr.GetSize(), 3);
		}
		// не позволяет получить доступ к элементам вне диапазона
		BOOST_AUTO_TEST_CASE(does_not_allow_to_acess_to_elements_out_of_range)
		{
			BOOST_CHECK_THROW(arr[3], std::out_of_range);
		}
		// позволяет получить доступ к данным из диапазона
		BOOST_AUTO_TEST_CASE(allows_to_change_elements_using_index_access_operator)
		{
			BOOST_CHECK_EQUAL(arr[0], 1);
			BOOST_CHECK_EQUAL(arr[1], 2);

			arr[0] = 10;
			arr[1] = 11;

			BOOST_CHECK_EQUAL(arr[0], 10);
			BOOST_CHECK_EQUAL(arr[1], 11);
		}
		// можут быть изменен с меньшим размером
		BOOST_AUTO_TEST_CASE(can_be_resized_to_smaller)
		{
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);
			arr.Resize(2);
			BOOST_CHECK_EQUAL(arr.GetSize(), 2u);
			BOOST_CHECK_EQUAL(arr[0], 1);
			BOOST_CHECK_EQUAL(arr[1], 2);
			BOOST_CHECK_THROW(arr[2], std::out_of_range);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);
		}
		// может быть изменен с большим размером
		BOOST_AUTO_TEST_CASE(can_be_resized_to_bigger)
		{
			arr.Resize(5);
			BOOST_CHECK_EQUAL(arr.GetSize(), 5u);
			BOOST_CHECK_EQUAL(arr[2], 3);
			BOOST_CHECK_EQUAL(arr[3], 0);
			BOOST_CHECK_EQUAL(arr[4], 0);
			BOOST_CHECK_THROW(arr[5], std::out_of_range);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 5u);
			arr.Resize(2);
			BOOST_CHECK_EQUAL(arr.GetSize(), 2u);
			arr.Resize(4);
			BOOST_CHECK_EQUAL(arr.GetSize(), 4u);
			BOOST_CHECK_EQUAL(arr[3], 0);
			BOOST_CHECK_THROW(arr[4], std::out_of_range);
		}
		// может быть очищен
		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			arr.Clear();
			BOOST_CHECK_EQUAL(arr.GetSize(), 0);
			BOOST_CHECK_THROW(arr[0], std::out_of_range);
			BOOST_CHECK_THROW(int x = arr[0], std::out_of_range);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);
		}
		// может быть скопирован
		BOOST_AUTO_TEST_CASE(can_be_copied)
		{
			CMyArray<int> newArray;
			newArray = arr;

			BOOST_CHECK_EQUAL(newArray.GetSize(), arr.GetSize());
			BOOST_CHECK_EQUAL(newArray[0], arr[0]);
			BOOST_CHECK_EQUAL(newArray[1], arr[1]);
			BOOST_CHECK_EQUAL(newArray[2], arr[2]);
			BOOST_CHECK_THROW(newArray[3] = 0, std::out_of_range);

			newArray.Clear();
			BOOST_CHECK_EQUAL(newArray.GetSize(), 0u);
			BOOST_CHECK_EQUAL(arr.GetSize(), 3u);

			CMyArray<int> newArray2;
			newArray2 = std::move(arr);

			BOOST_CHECK_EQUAL(arr.GetSize(), 0u);
			BOOST_CHECK_EQUAL(newArray2.GetSize(), 3u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 0u);
			BOOST_CHECK_EQUAL(newArray2.GetCapacity(), 4u);

		}
		// имеет конструктор перемещения
		BOOST_AUTO_TEST_CASE(has_moves_constructor)
		{
			CMyArray<int> arr1;
			arr1.Append(1);
			arr1.Append(2);
			arr1.Append(3);
			arr1.Append(4);
			arr1.Append(5);
			arr1.Append(6);
			CMyArray<int> arr2(std::move(arr1));
			BOOST_CHECK_EQUAL(arr1.GetSize(), 0u);
			BOOST_CHECK_EQUAL(arr2.GetSize(), 6u);
			BOOST_CHECK_EQUAL(arr2[0], 1);
			BOOST_CHECK_EQUAL(arr2[5], 6);
		}
		// имеет итератор для начала
		BOOST_AUTO_TEST_CASE(has_iterators_to_begin)
		{
			auto it = arr.begin();
			BOOST_CHECK_EQUAL(*it, 1);
			++it;
			BOOST_CHECK_EQUAL(*it, 2);
			++it;
			BOOST_CHECK_EQUAL(*it, 3);
			--it;
			BOOST_CHECK_EQUAL(*it, 2);

			CMyArray<int> expectedArray;
			expectedArray.Append(1);
			expectedArray.Append(2);
			expectedArray.Append(3);
			size_t i = 0;
			for (auto number : arr)
			{
				BOOST_CHECK_EQUAL(number, expectedArray[i]);
				i++;
			}
		}
		// имеет итератор для конца
		BOOST_AUTO_TEST_CASE(has_iterators_to_end)
		{
			auto it = arr.end();
			BOOST_CHECK(it != arr.begin());
			BOOST_CHECK(!(it == arr.begin()));
			--it;
			BOOST_CHECK_EQUAL(*it, 3);
			--it;
			BOOST_CHECK_EQUAL(*it, 2);
			--it;
			BOOST_CHECK_EQUAL(*it, 1);
			++it;
			BOOST_CHECK_EQUAL(*it, 2);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
