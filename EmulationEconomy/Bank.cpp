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

void CBank::SendMoney(AccountId const srcAccountId, AccountId const dstAccountId, Money amount)
{
	if (amount < 0)
	{
		throw std::out_of_range("amount cannot be negative");
	}
	auto srcHandler = m_account.extract({ srcAccountId, 0 });
	if (srcHandler.empty())
	{
		throw BankOperationError("error srcAccountId not found");
	}
	auto sdtHandler = m_account.extract({ dstAccountId, 0 });
	if (sdtHandler.empty())
	{
		throw BankOperationError("error dstAccountId not found");
	}
	if (srcHandler.value().money < amount)
	{
		m_account.insert(std::move(srcHandler));
		throw BankOperationError("insufficient funds in the account");
	}

	srcHandler.value().money -= amount;
	m_account.insert(std::move(srcHandler));
	sdtHandler.value().money += amount;
	m_account.insert(std::move(sdtHandler));	
}

