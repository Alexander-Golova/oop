#pragma once

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
	bool IsTurnedOn() const;
	Direction GetDirection() const;
	size_t GetSpeed() const;
	Gear GetGear() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(size_t speed); 

private:

	bool m_isOn = false;
	Direction m_direction = Direction::Stop;
	size_t m_speed = 0;
	Gear m_gear = Gear::Neutral;
};
