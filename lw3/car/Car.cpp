#include "stdafx.h"

#include "Car.h"


CCar::CCar()
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
	return ((start <= number) && (number <= end));
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
	if (gear == Gear::Neutral)
	{
		m_gear = gear;
		return true;
	}
	if (IsSpeedInGearInterval(gear, abs(m_speed)) && m_isEngineTurnOn)
	{
		if (((static_cast<int>(gear) > 0) && (m_speed >= 0)) ||
			((static_cast<int>(gear) < 0) && (m_speed == 0)))
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
	if (m_gear == Gear::Neutral)
	{
		if (speed <= static_cast<unsigned>(abs(m_speed)))
		{
			m_speed = speed;
			if (GetDirection() == Direction::Back)
			{
				m_speed *= -1;
			}
			return true;
		}
		return false;
	}
	if (IsSpeedInGearInterval(m_gear, speed))
	{
		int signedSpeed = speed;
		if (m_gear == Gear::Reverse)
		{
			m_speed = -signedSpeed;
		}
		else
		{
			m_speed = signedSpeed;
		}
		return true;
	}
	return false;
}

unsigned CCar::GetSpeed() const
{
	return abs(m_speed);
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
