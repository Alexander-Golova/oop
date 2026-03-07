#pragma once
#include <algorithm>
#include <cctype>
#include <iostream>
#include <set>
#include <vector>


bool CheckArgumentCount(const int argumentCount);

bool IsNumber(const std::string& str);

std::set<size_t> GeneratePrimeNumbersSet(const size_t upperBound);
