#include "Car.h"


bool CCar::IsTurnedOn() const
{
	return m_isOn;
}

Direction CCar::GetDirection() const
{
	return m_direction;
}

size_t CCar::GetSpeed() const
{
	return m_speed;
}

Gear CCar::GetGear() const
{
	return m_gear;
}

bool CCar::TurnOnEngine()
{
	m_isOn = true;
	return IsTurnedOn();
}

bool CCar::TurnOffEngine()
{
	m_isOn = false;
	return !IsTurnedOn();
}
