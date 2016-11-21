#pragma once
#include "stdafx.h"

enum class Operator
{
	Plus,
	Minus,
	Multiplication,
	Division,
	None
};

struct SFunctionData
{
	SFunctionData()
		: operatorType(Operator::None)
	{}

	double value = std::numeric_limits<double>::quiet_NaN();
	std::string firstOperand;
	std::string secondOperand;
	Operator operatorType;
};


static const std::map<std::string, Operator> SYMBOLS_OPERATORS
{
	{ "+", Operator::Plus },
	{ "-", Operator::Minus },
	{ "*", Operator::Multiplication },
	{ "/", Operator::Division }	
};


class CCalculator
{
public:
	CCalculator() = default;
	~CCalculator() = default;

	bool SetVar(const std::string & var);
	const std::map<std::string, double> & GetVars() const;

private:
	bool IsNameCorrect(const std::string & id) const;
	bool IsVarExist(const std::string & var) const;
	bool IsFunctionExist(const std::string & nameFunction) const;

	std::map<std::string, SFunctionData> m_functions;
	std::map<std::string, double> m_variables;
	std::map<std::string, std::vector<std::string>> m_usedFunctions;
};
