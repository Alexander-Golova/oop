#include "stdafx.h"
#include "calculator.h"

using namespace std;


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


bool CCalculator::IsNameCorrect(const string & id) const
{
	if (id.empty())
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
