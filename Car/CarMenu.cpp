#include "CarMenu.h"

CCarMenu::CCarMenu(CCar& car)
	: m_car(car)
{
}

std::string DirectionToString(const Direction& direction)
{
	switch (direction)
	{
	case Direction::Back:
		return "back";
	case Direction::Forward:
		return "forward";
	case Direction::Stop:
		return "stop";
	default:
		assert(!"unexpected direction");
		return "<unknown direction>";
	}
}

std::string GearToString(const Gear& gear)
{
	switch (gear)
	{
	case Gear::Reverse:
		return "reverse";
	case Gear::Neutral:
		return "neutral";
	case Gear::First:
		return "first";
	case Gear::Second:
		return "second";
	case Gear::Third:
		return "third";
	case Gear::Fourth:
		return "fourth";
	case Gear::Fifth:
		return "fifth";
	default:
		assert(!"unexpected gear");
		return "<unknown gear>";
	}
}



void Info(const CCar& car)
{
	std::cout << "Engine status: " << ((car.IsTurnedOn()) ? ("turned on") : ("turned off")) << std::endl;
	std::cout << "Speed: " << car.GetSpeed() << std::endl;
	std::cout << "Direction: " << DirectionToString(car.GetDirection()).c_str() << std::endl;
	std::cout << "Gear: " << GearToString(car.GetGear()).c_str() << std::endl;
}

void CCarMenu::GetInfo() const
{
	Info(m_car);
}
