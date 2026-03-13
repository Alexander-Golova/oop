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
