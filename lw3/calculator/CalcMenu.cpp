#include "stdafx.h"
#include "CalcMenu.h"

using namespace std;
using namespace std::placeholders;

CCalcMenu::CCalcMenu(CCalculator calculator, istream & input, ostream & output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "var", bind(&CCalcMenu::SetVar, this, _1) },
		{ "let", bind(&CCalcMenu::LetVarValue, this, _1) },
		{ "fn", bind(&CCalcMenu::SetFunction, this, _1) },
		{ "print", bind(&CCalcMenu::PrintIdentifierValue, this, _1) },
		{ "printvars", bind(&CCalcMenu::PrintVariables, this) },
		{ "printfns", bind(&CCalcMenu::PrintFunctions, this) }
})
{
}

bool CCalcMenu::RunCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strm);
		return true;
	}
	return false;
}

void CCalcMenu::SetVar(istream & args)
{
	string identifier;
	args >> identifier;
	if (!m_calculator.SetVar(identifier))
	{
		cout << "Invalid name of varible!" << endl;
	}
}

void CCalcMenu::LetVarValue(istream & args)
{
	string expression;
	args >> expression;
	string firstValue;
	string secondValue;
	if (!ParseStrToValue(expression, firstValue, secondValue) || !m_calculator.LetVarValue(firstValue, secondValue))
	{
		cout << "Invalid expression!" << endl;
	}
}

bool CCalcMenu::ParseStrToValue(const string & str, string & firstValue, string & secondValue)
{
	auto parsePosition = str.find("=");

	if ((parsePosition == string::npos) || (parsePosition + 1 == str.size()))
	{
		return false;
	}
	firstValue = str.substr(0, parsePosition);
	secondValue = str.substr(parsePosition + 1, str.size());
	return true;
}

void CCalcMenu::SetFunction(istream & args)
{
	string expression;
	args >> expression;
	string firstValue, secondValue, operand, thirdValue;
	Operator expressionOperator;

	if ((ParseStrToValue(expression, firstValue, secondValue) || !m_calculator.SetFunction(firstValue, secondValue))
		&& (!ParseStrToAriphOperation(secondValue, expression, expressionOperator, thirdValue)
		   || !m_calculator.SetFunction(firstValue, expression, expressionOperator, thirdValue)))
	{
		cout << "Invalid expression!" << endl;
	}
}

bool CCalcMenu::ParseStrToAriphOperation(const string & str, string & firstValue, Operator & operand, string & secondValue)
{
	auto operandPos = string::npos;
	for (auto elem : SYMBOLS_OPERATORS)
	{
		operandPos = str.find(elem.first);
		if (operandPos != string::npos)
		{
			operand = elem.second;
			break;
		}
	}
	if (operandPos != string::npos)
	{
		firstValue = str.substr(0, operandPos);
		secondValue = str.substr(operandPos + 1, str.size());
		return true;
	}
	else
	{
		return false;
	}	
}

void CCalcMenu::PrintIdentifierValue(istream & args)
{
	string identifier;
	args >> identifier;
	cout << setprecision(2) << m_calculator.GetValue(identifier) << endl;
}

void CCalcMenu::PrintVariables()
{
	for (auto it : m_calculator.GetVars())
	{
		cout << it.first << ":" << setprecision(2) << it.second << endl;
	}
}

void CCalcMenu::PrintFunctions()
{
	for (auto it : m_calculator.GetFunctions())
	{
		cout << it.first << ":" << setprecision(2) << m_calculator.GetValue(it.first) << endl;
	}
}
