#include "Car.h"


bool CCar::IsTurnedOn() const
{
	return m_isOn;
}

Direction CCar::GetDirection() const
{
	return m_direction;
}
