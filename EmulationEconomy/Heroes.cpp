#include "Heroes.h"

CHeroes::CHeroes(std::string name, AccountId id, Money money, Money moneyBank)
	: name(name)
	, id(id)
	, m_money(money)
	, m_moneyBank(moneyBank)
{};


bool CHeroes::GiveMoney(Money money)
{
	if (money <= CheckPocket())
	{
		m_money -= money;
		return true;
	}
	return false;	
}

Money CHeroes::CheckPocket()
{
	return m_money;
}

bool CHeroes::GetMoney(Money money)
{
	m_money += money;
}
