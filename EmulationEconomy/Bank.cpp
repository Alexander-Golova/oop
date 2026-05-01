#include "Bank.h"

bool CBank::FindId(AccountId const id)
{
	auto it = m_account.find({ id, 0 });
	return (it != m_account.end());
}

void CBank::AddAccount(AccountId const accountId, Money money)
{
	if (!FindId(accountId))
	{
		if (money < 0)
		{
			money = 0;
		}
		m_account.insert({ accountId, money });
	}
} 

Money CBank::GetMoney(AccountId const accountId)
{
	auto it = m_account.find({ accountId, 0 });
	return it->money;
}

void CBank::SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
	if (amount < 0)
	{
		throw std::out_of_range("amount cannot be negative");
	}
	if (amount <= GetMoney(srcAccountId))
	{

	}
}



