#include "Bank.h"

void CBank::SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
	if (amount < 0)
	{
		throw std::out_of_range("amount cannot be negative");
	}

}
