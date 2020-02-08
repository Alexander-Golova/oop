#pragma once
#include "pch.h"

bool CheckArgumentCount(const int argumentCount);

bool IsNumber(const std::string& str);

std::set<size_t> GeneratePrimeNumbersSet(const size_t upperBound);
