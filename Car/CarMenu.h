#pragma once
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <sstream>

#include "Car.h"

class CCarMenu
{
public:
	CCarMenu(CCar& car);
	~CCarMenu() = default;

	void GetInfo() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(size_t speed);
	void RunCommand(std::string& command);

private:
	CCar& m_car;
};
