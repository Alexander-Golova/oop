#pragma once

#include "stdafx.h"

bool CheckArgumentCount(const int argumentCount);

bool CheckReplacingString(const std::string & str);

std::string FindAndReplace(const std::string & subject, const std::string & search, const std::string & replace);
