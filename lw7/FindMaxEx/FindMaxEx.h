#pragma once

#include <vector>

template < typename T, typename Less = std::less<T>>
bool FindMaxEx(std::vector<T> const & arr, T& maxValue, Less const & less)
{
	if (arr.empty())
	{
		return false;
	}

	const T *max = &arr[0];
	for (auto & item : arr)
	{
		if (less(*max, item))
		{
		max = &item;
		}
	}
	maxValue = *max;
	return true;
}
