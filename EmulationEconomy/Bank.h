#pragma once
#include <stdexcept>
#include <set>


using AccountId = unsigned long long;
using Money = long long;

// Это исключение должно выбрасываться в случае ошибок
class BankOperationError : std::runtime_error
{
public:
	using runtime_error::runtime_error;
};

//class account
//{
//public:
//	AccountId id;
//	money getmoney()
//	{
//		return m_money;
//	}
//	void deposit(money money)
//	{
//		m_money += money;
//	}
//	bool iswithdraw(money money)
//	{
//		if (money <= m_money)
//		{
//			m_money -= money;
//			return true;
//		}
//		return false;
//	}
//
//private:
//	money m_money;
//};

struct Account
{
	AccountId id;
	Money money;
};


class CBank
{
public:
	// Инициализирует монетарную систему. cash — количество денег в наличном обороте
	// При отрицательном количестве денег, выбрасывается BankOperationError
	explicit CBank(Money cash)
		: m_cash(cash)
	{
		if (m_cash < 0)
		{
			throw BankOperationError("initial cash cannot be negative");
		}
	}

	CBank(const CBank&) = delete;
	CBank& operator=(const CBank&) = delete;

	bool FindId(AccountId const id);
	void AddAccount(AccountId const accountId, Money money);
	Money GetMoney(AccountId const accountId);
	// Перевести деньги с исходного счёта (srcAccountId) на целевой (dstAccountId)
	// Нельзя перевести больше, чем есть на исходном счёте
	// Нельзя перевести отрицательное количество денег
	// Исключение BankOperationError выбрасывается, при отсутствии счетов или
	// недостатке денег на исходном счёте
	// При отрицательном количестве переводимых денег выбрасывается std::out_of_range
	void SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);

	// Перевести деньги с исходного счёта (srcAccountId) на целевой (dstAccountId)
	// Нельзя перевести больше, чем есть на исходном счёте
	// Нельзя перевести отрицательное количество денег
	// При нехватке денег на исходном счёте возвращается false
	// Если номера счетов невалидны, выбрасывается BankOperationError
	// При отрицательном количестве денег выбрасывается std::out_of_range
	//[[nodiscard]] bool TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);

	// Возвращает количество наличных денег в обороте
	//[[nodiscard]] Money GetCash() const;

	// Сообщает о количестве денег на указанном счёте
	// Если указанный счёт отсутствует, выбрасывается исключение BankOperationError
	//Money GetAccountBalance(AccountId accountId) const;

	// Снимает деньги со счёта. Нельзя снять больше, чем есть на счете
	// Нельзя снять отрицательное количество денег
	// Снятые деньги переходят добавляются к массе наличных денег
	// При невалидном номере счёта или отсутствии денег, выбрасывается исключение BankOperationError
	// При отрицательном количестве денег выбрасывается std::out_of_range
	//void WithdrawMoney(AccountId account, Money amount);

	// Попытаться снять деньги в размере amount со счёта account.
	// Объем денег в наличном обороте увеличивается на величину amount
	// При нехватке денег на счёте возвращается false, а количество наличных денег остаётся неизменным
	// При невалидном номере аккаунта выбрасывается BankOperationError.
	// При отрицательном количестве денег выбрасывается std::out_of_range
	//[[nodiscard]] bool TryWithdrawMoney(AccountId account, Money amount);

	// Поместить наличные деньги на счёт. Количество денег в наличном обороте
	// уменьшается на величину amount.
	// Нельзя поместить больше, чем имеется денег в наличном обороте
	// Нельзя поместить на счёт отрицательное количество денег
	// Нельзя поместить деньги на отсутствующий счёт
	// При невалидном номере аккаунта или нехватке наличных денег в обороте выбрасывается BankOperationError.
	// При отрицательном количестве денег выбрасывается std::out_of_range
	//void DepositMoney(AccountId account, Money amount);

	// Открывает счёт в банке. После открытия счёта на нём нулевой баланс.
	// Каждый открытый счёт имеет уникальный номер.
	// Возвращает номер счёта
	//[[nodiscard]] AccountId OpenAccount();

	// Закрывает указанный счёт.
	// Возвращает количество денег, которые были на счёте в момент закрытия
	// Эти деньги переходят в наличный оборот
	//[[nodiscard]] Money CloseAccount(AccountId accountId);

private:
	Money m_cash;
	std::set<Account> m_account;
};
