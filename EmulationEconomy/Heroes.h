#pragma once
#include<string>
#include "Bank.h"

class CHeroes
{
public:
	CHeroes(std::string name, AccountId id, Money money, Money moneyBank);
	CHeroes(const CHeroes&) = delete;
	Money CheckPocket();

	bool GiveMoney(Money money);
	bool GetMoney(Money money);

	std::string name;
	AccountId id;

private:
	Money m_money;
	Money m_moneyBank;

};
