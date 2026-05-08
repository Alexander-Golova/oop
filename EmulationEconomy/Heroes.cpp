#include "Heroes.h"

CHeroes::CHeroes(std::string name, AccountId id, Money money)
	: name(name)
	, id(id)
	, m_money(money)
{};

bool CHeroes::GiveMoney(Money money)
{
	if (money < GetMoney())
	{
		m_money -= money;
		return true;
	}
	return false;	
}

Money CHeroes::FindMoney()
{
	return m_money;
}

bool CHeroes::GetMoney(Money money)
{
	m_money += money;
}
