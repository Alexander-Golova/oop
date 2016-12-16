#pragma once

#include <vector>

template < typename T, typename Less>
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	T newMax(arr[0]);
	for (const auto & item : arr)
	{
		if (less(newMax, item))
		{
			newMax = item;
		}
	}
	maxValue = newMax;
	return true;
}
