#pragma once
#include "pch.h"

bool CheckArgumentCount(const int argumentCount);

bool IsNumber(const std::string& str);

std::set<uint32_t> GeneratePrimeNumbersSet(const unsigned upperBound);
