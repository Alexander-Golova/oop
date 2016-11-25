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
		return isalnum(ch) || ch == '_';
	}
}

bool CCalculator::SetVar(const string & variable)
{
	if (!IsNameCorrect(variable) || IsFunctionExist(variable) || IsVarExist(variable))
	{
		return false;
	}
	m_variables.insert({ variable, numeric_limits<double>::quiet_NaN() });
	return true;
}

const map<string, double> & CCalculator::GetVars() const
{
	return m_variables;
}

double CCalculator::GetValue(const string & variable) const
{
	if (IsVarExist(variable))
	{
		return m_variables.at(variable);
	}
	if (IsFunctionExist(variable))
	{
		return m_functions.at(variable).value;;
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

	for (const auto functionName : m_usedFunctions[firstVar])
	{
		CalculateFunctionValue(functionName);
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

const map<string, SFunctionData> & CCalculator::GetFunctions() const
{
	return m_functions;
}

bool CCalculator::SetFunction(const string & varFunction, const string & variable)
{
	if (IsVarExist(varFunction) || IsFunctionExist(varFunction) || !IsNameCorrect(varFunction))
	{
		return false;
	}
	if (!IsVarExist(variable) && !IsFunctionExist(variable))
	{
		return false;
	}

	if (IsVarExist(variable))
	{
		m_usedVariables[varFunction].insert(variable);
	}
	else
	{
		m_usedVariables[varFunction] = m_usedVariables[variable];
	}
	for (const auto & element : m_usedVariables[varFunction])
	{
		m_usedFunctions[element].push_back(varFunction);
	}


	SFunctionData functionInfo;
	functionInfo.firstOperand = variable;
	m_functions.insert(make_pair(varFunction, functionInfo));
	CalculateFunctionValue(varFunction);
	return true;
}

bool CCalculator::SetFunction(const string & varFunction, const string &firstIdentifier,
	                          Operator operatorFunction, const string &secondIdentifier)
{
	if (IsVarExist(varFunction) || IsFunctionExist(varFunction) || !IsNameCorrect(varFunction))
	{
		return false;
	}
	if (!IsVarExist(firstIdentifier) && !IsFunctionExist(firstIdentifier))
	{
		return false;
	}
	if (!IsVarExist(secondIdentifier) && !IsFunctionExist(secondIdentifier))
	{
		return false;
	}
	if (operatorFunction == Operator::None)
	{
		return false;
	}

	if (IsVarExist(firstIdentifier))
	{
		m_usedVariables[varFunction].insert(firstIdentifier);
	}
	else
	{
		m_usedVariables[varFunction] = m_usedVariables[firstIdentifier];
	}
	if (IsVarExist(secondIdentifier))
	{
		m_usedVariables[varFunction].insert(secondIdentifier);
	}
	else
	{
		m_usedVariables[varFunction] = m_usedVariables[secondIdentifier];
	}
	for (const auto & element : m_usedVariables[varFunction])
	{
		m_usedFunctions[element].push_back(varFunction);
	}

	// TODO: use class-constructor
	SFunctionData functionInfo;
	functionInfo.firstOperand = firstIdentifier;
	functionInfo.secondOperand = secondIdentifier;
	functionInfo.operatorType = operatorFunction;

	m_functions.insert({ varFunction, functionInfo });
	CalculateFunctionValue(varFunction);



	return true;
}

void CCalculator::CalculateFunctionValue(const string & functionName)
{
	if (IsFunctionExist(functionName))
	{
		auto & function = m_functions.at(functionName);
		if (!(function.operatorType == Operator::None))
		{
			CalculateTwoOperandsFunction(function);
		}
		else
		{
			function.value = GetValue(function.firstOperand);
		}
	}
}

void CCalculator::CalculateTwoOperandsFunction(SFunctionData & functionInfo)
{
	double firstOperand = GetValue(functionInfo.firstOperand);
	double secondOperand = GetValue(functionInfo.secondOperand);

	if (!IsNan(firstOperand) && !IsNan(secondOperand))
	{
		double result = numeric_limits<double>::quiet_NaN();
		switch (functionInfo.operatorType)
		{
		case Operator::Plus:
			result = firstOperand + secondOperand;
			break;
		case Operator::Division:
			result = firstOperand / secondOperand;
			break;
		case Operator::Multiplication:
			result = firstOperand * secondOperand;
			break;
		case Operator::Minus:
			result = firstOperand - secondOperand;
			break;
		}
		functionInfo.value = result;
	}
}
