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

bool CCarMenu::TurnOnEngine()
{
	return m_car.TurnOnEngine();
}

bool CCarMenu::TurnOffEngine()
{
	return m_car.TurnOffEngine();
}

bool CCarMenu::SetGear(int gear)
{
	return m_car.SetGear(gear);
}

bool CCarMenu::SetSpeed(size_t speed)
{
	return m_car.SetSpeed(speed);
}

void CCarMenu::RunCommand(std::string& command)
{
	std::vector<std::string> commands;
	std::stringstream ss(command);
	std::string word;
	while (ss >> word)
	{
		commands.push_back(word);
	}

	if (commands.size() == 1 || commands.size() == 2)
	{
		if ((commands[0] == "info") && (commands.size() == 1))
		{
			GetInfo();
		}
		else if ((commands[0] == "engine") && (commands[1] == "on"))
		{
			TurnOnEngine();
		}
		else if ((commands[0] == "engine") && (commands[1] == "off"))
		{
			TurnOffEngine();
		}
		else if ((commands[0] == "setgear") && (stoi(commands[1]) >= -1 && stoi(commands[1]) <= 5))
		{
			SetGear(stoi(commands[1]));
		}
		else if ((commands[0] == "setspeed") && (stoi(commands[1]) >= 0))
		{
			SetSpeed(stoi(commands[1]));
		}
		else
		{
			std::cout << "Unknown command" << std::endl;
		}
	}
	else
	{
		std::cout << "Unknown command" << std::endl;
	}
}
