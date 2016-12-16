#pragma once

#include <vector>

template < typename T, typename Less>
bool FindMaxEx(std::vector<T> const & arr, T& maxValue, Less const & less)
{
	if (arr.empty())
	{
		return false;
	}

	T max(arr[0]);
	for (const auto & item : arr)
	{
		if (less(max, item))
		{
			max = item;
		}
	}
	maxValue = max;
	return true;
}
