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

private:

	bool m_isOn = false;
	Direction m_direction = Direction::Stop;
};
