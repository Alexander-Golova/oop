#include "stdafx.h"

#include "Car.h"


CCar::CCar()
{
}


CCar::~CCar()
{
}


bool CCar::TurnOnEngine()
{
	if (!m_isEngineTurnOn)
	{
		m_isEngineTurnOn = true;
		return true;
	}
	return false;
}


bool CCar::TurnOffEngine()
{
	if ((m_isEngineTurnOn) && (m_gear == Gear::Neutral) && (m_speed == 0))
	{
		m_isEngineTurnOn = false;
		return true;
	}
	return false;
}


bool CCar::IsEngineTurnOn() const
{
	return m_isEngineTurnOn;
}


bool IsInRange(unsigned number, unsigned start, unsigned end)
{
	return (start <= number) && (number <= end);
}

bool IsSpeedInGearInterval(Gear gear, unsigned speed)
{
	auto IsSpeedInRange = [=](Gear expectedGear, unsigned minSpeed, unsigned maxSpeed) {
		return IsInRange(speed, minSpeed, maxSpeed) && (gear == expectedGear);
	};

	return ((gear == Gear::Neutral) ||
		IsSpeedInRange(Gear::Reverse, 0, 20) ||
		(IsInRange(speed, 0, 30) && (gear == Gear::First)) ||
		(IsInRange(speed, 20, 50) && (gear == Gear::Second)) ||
		(IsInRange(speed, 30, 60) && (gear == Gear::Third)) ||
		(IsInRange(speed, 40, 90) && (gear == Gear::Fourth)) ||
		(IsInRange(speed, 50, 150) && (gear == Gear::Fifth)));
}

bool CCar::SetGear(Gear gear)
{
	if (!m_isEngineTurnOn)
	{
		if (gear == Gear::Neutral)
		{
			m_gear = gear;
			return true;
		}
	}
	else
	{
		if (IsSpeedInGearInterval(gear, m_speed))
		{
			m_gear = gear;
			return true;
		}
	}
	return false;
}


Gear CCar::GetGear() const
{
	return m_gear;
}


bool CCar::SetSpeed(unsigned speed)
{
	return false;
}


unsigned CCar::GetSpeed() const
{
	return 0;
}


Direction CCar::GetDirection() const
{
	if (m_speed == 0)
	{
		return Direction::Stop;
	}
	else if (m_speed < 0)
	{
		return Direction::Back;
	}
	else
	{
		return Direction::Forward;
	}
}

bool CCar::operator==(const CCar & car)
{
	return (m_isEngineTurnOn == car.m_isEngineTurnOn) && (m_speed == car.m_speed) && (m_gear == car.m_gear);
}
