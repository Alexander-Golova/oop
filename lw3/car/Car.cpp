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
	return false;
}


bool CCar::IsEngineTurnOn() const
{
	return m_isEngineTurnOn;
}


bool CCar::SetGear(Gear gear)
{
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
