#pragma once

#include "stdafx.h"

using namespace std;

bool CheckArgumentCount(const int argumentCount);

bool IsNumber(const std::string & str);

set<uint32_t> GeneratePrimeNumbersSet(const unsigned upperBound);
