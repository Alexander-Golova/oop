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
	if (m_speed == 0)
	{
		m_isOn = false;
		m_direction = Direction::Stop;
	}	
	return !IsTurnedOn();
}

bool CCar::SetGear(int gear)
{
	if (!m_isOn)
	{
		return false;
	}
	if (m_speed == 0 && gear == -1)
	{
		m_gear = Gear::Reverse;
		m_direction = Direction::Back;
		return true;
	}
	if (m_speed >= 0 && m_speed <= 30 && gear == 1)
	{
		m_gear = Gear::First;
		m_direction = Direction::Forward;
		return true;
	}
	if (m_direction == Direction::Forward && m_speed >= 20 && m_speed <= 50 && gear == 2)
	{
		m_gear = Gear::Second;
		return true;
	}
	if (m_direction == Direction::Forward && m_speed >= 30 && m_speed <= 60 && gear == 3)
	{
		m_gear = Gear::Third;
		return true;
	}
	if (m_direction == Direction::Forward && m_speed >= 40 && m_speed <= 90 && gear == 4)
	{
		m_gear = Gear::Fourth;
		return true;
	}
	if (m_direction == Direction::Forward && m_speed >= 50 && m_speed <= 150 && gear == 5)
	{
		m_gear = Gear::Fifth;
		return true;
	}
	if (gear == 0)
	{
		m_gear = Gear::Neutral;
		return true;
	}
	return false;
}

bool CCar::SetSpeed(size_t speed)
{
	if (m_gear == Gear::First && speed >= 0 && speed <= 30)
	{
		m_speed = speed;
		return true;
	}
	if (m_gear == Gear::Second && speed >= 20 && speed <= 50)
	{
		m_speed = speed;
		return true;
	}
	if (m_gear == Gear::Third && speed >= 30 && speed <= 60)
	{
		m_speed = speed;
		return true;
	}
	if (m_gear == Gear::Fourth && speed >= 40 && speed <= 90)
	{
		m_speed = speed;
		return true;
	}
	if (m_gear == Gear::Fifth && speed >= 50 && speed <= 150)
	{
		m_speed = speed;
		return true;
	}
	if (m_gear == Gear::Reverse && speed >= 0 && speed <= 20)
	{
		m_speed = speed;
		return true;
	}
	if (m_gear == Gear::Neutral && speed <= m_speed)
	{
		m_speed = speed;
		return true;
	}
	return false;
}
