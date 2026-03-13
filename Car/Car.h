#pragma once

enum class Direction
{
	Back,
	Stop,
	Forward
};


class CCar
{
public:
	bool IsTurnedOn() const;
	Direction GetDirection() const;
	size_t GetSpeed() const;

private:

	bool m_isOn = false;
	Direction m_direction = Direction::Stop;
	size_t m_speed = 0;
};
