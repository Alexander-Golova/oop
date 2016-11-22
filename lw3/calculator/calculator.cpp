#include "stdafx.h"
#include "calculator.h"

using namespace std;

namespace
{
	bool IsNan(const double & numeric)
	{
		return numeric != numeric;
	}

	bool IsCharCorrect(char ch)
	{
		return std::isalnum(ch) || ch == '_';
	}
}

bool CCalculator::SetVar(const string & var)
{
	if (!IsNameCorrect(var) || IsFunctionExist(var) || IsVarExist(var))
	{
		return false;
	}
	m_variables.insert({ var, numeric_limits<double>::quiet_NaN() });
	return true;
}

const map<string, double> & CCalculator::GetVars() const
{
	return m_variables;
}

double CCalculator::GetValue(const string & var) const
{
	if (IsVarExist(var))
	{
		return m_variables.at(var);
	}
	return numeric_limits<double>::quiet_NaN();
}

bool CCalculator::LetVarValue(const string & firstVar, const string & secondValue)
{
	if (secondValue.empty() || IsFunctionExist(firstVar))
	{
		return false;
	}
	if (!IsVarExist(firstVar))
	{
		if (!SetVar(firstVar))
		{
			return false;
		}
	}
	if (IsVarExist(secondValue))
	{
		m_variables[firstVar] = GetValue(secondValue);
	}
	else
	{
		m_variables[firstVar] = stod(secondValue);
	}
	return true;
}

bool CCalculator::IsNameCorrect(const string & id) const
{
	if (id.empty() || isdigit(*id.begin()) || !all_of(id.begin(), id.end(), IsCharCorrect))
	{
		return false;
	}
	return true;
}

bool CCalculator::IsVarExist(const string & id) const
{
	return m_variables.find(id) != m_variables.end();
}

bool CCalculator::IsFunctionExist(const string & id) const
{
	return m_functions.find(id) != m_functions.end();
}
