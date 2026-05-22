#pragma once
#include "Bank.h"
#include "Heroes.h"

class CWorld
{
public:
	CWorld()
		: bank(1000000)
		, m_Homer("Homer", 0001, 1000, 10000)
		, m_Marge("Marge", 0002, 1000, 20000)
		, m_Bart("Bart", 0000, 100, 0)
		, m_Liza("Liza", 0000, 200, 0)
		, m_Apu("Apu", 0003, 1000, 100000)
		, m_Berns("Berns", 0004, 1000, 200000)
	{
		bank.Deposit(0001, 10000);
		bank.Deposit(0002, 20000);
		bank.Deposit(0003, 100000);
		bank.Deposit(0004, 200000);
	}

	void Simulation();
	CBank bank;
	
	void HomerDay();

private:	
	CHeroes m_Homer;
	CHeroes m_Marge;
	CHeroes m_Bart;
	CHeroes m_Liza;
	CHeroes m_Apu;
	CHeroes m_Berns;
};
