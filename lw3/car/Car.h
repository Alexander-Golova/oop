#pragma once

#include "stdafx.h"

enum class Gear
{
	Reverse = -1,
	Neutral = 0,
	First,
	Second,
	Third,
	Fourth,
	Fifth
};

enum class Direction
{
	Back,
	Stop,
	Forward
};

class CCar
{
public:
	CCar();
	~CCar();

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool IsEngineTurnOn() const;

	bool SetGear(Gear gear);
	Gear GetGear() const;

	bool SetSpeed(unsigned speed);
	unsigned GetSpeed() const;

	Direction GetDirection() const;

private:
	bool m_isEngineTurnOn = false;
	Gear m_gear = Gear::Neutral;
	unsigned m_speed = 0;
};
