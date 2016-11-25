#pragma once

#include "calculator.h"
#include <sstream>
#include <functional>


class CCalcMenu
{
public:
	CCalcMenu(CCalculator calculator, std::istream &input, std::ostream &output);
	bool RunCommand();

private:
	void SetVar(std::istream & args);
	void LetVarValue(std::istream & args);
	void SetFunction(std::istream & args);

	void PrintIdentifierValue(std::istream & args);

	void PrintVariables();
	void PrintFunctions();

	bool ParseStrToValue(const std::string & str, std::string & firstValue, std::string & secondValue);
	bool ParseStrToAriphOperation(const std::string & str, std::string & firstValue, Operator & operand, std::string & secondValue);

	typedef std::map<std::string, std::function<void(std::istream & args) >> ActionMap;
	std::istream &m_input;
	std::ostream &m_output;

	CCalculator m_calculator;
	const ActionMap m_actionMap;
};
