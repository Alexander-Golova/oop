#include "World.h"

void CWorld::Simulation()
{
	HomerDay();
}


void CWorld::HomerDay()
{
	// Гомер работает на электростанции
	bank.SendMoney(0004, 0001, 1000);
	// Он регулярно выдаёт некоторую сумму денег своей жене Мардж. Перевод осуществляет путём перевода денег на карту Мардж.
	bank.SendMoney(0001, 0002, 400);
	// Некоторую сумму денег Гомер платит за электричество в доме.
	bank.SendMoney(0001, 0004, 50);
	// Также Гомер регулярно снимает наличные деньги со счёта и даёт их своим детям: Барту и Лизе.
	if (bank.TryWithdrawMoney(0001, 50))
	{
		m_Bart.GetMoney(50);
	}
	if (bank.TryWithdrawMoney(0001, 50))
	{
		m_Liza.GetMoney(50);
	}	
}
