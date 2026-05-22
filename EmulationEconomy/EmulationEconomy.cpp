#include <iostream>
#include "Bank.h"
#include "Heroes.h"



int main()
{
	CBank Bank(1000000);
	CHeroes Gomer("Gomer", 000001, 1000);

	CHeroes Marge("Marge", 000002, 10);
	std::cout << Bank.GetMoney(000001);

}

