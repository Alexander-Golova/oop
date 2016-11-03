#include "stdafx.h"

#include "CarMenu.h"

using namespace std;


CCarMenu::CCarMenu(CCar & car)
	:m_car(car)
{
}

bool IsNumber(const string & str)
{
	return all_of(str.begin(), str.end(), isdigit);
}

string DirectionToString(const Direction & direction)
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

string GearToString(const Gear & gear)
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

void Info(const CCar & car)
{
	cout << "Engine status: " << ((car.IsEngineTurnOn()) ? ("turned on") : ("turned off")) << endl;
	cout << "Speed: " << car.GetSpeed() << endl;
	cout << "Direction: " << DirectionToString(car.GetDirection()).c_str() << endl;
	cout << "Gear: " << GearToString(car.GetGear()).c_str() << endl;
}

void CCarMenu::GetInfo() const
{
	Info(m_car);
}

bool CCarMenu::TurnOnEngine()
{
	auto result = m_car.TurnOnEngine();
	if (result)
	{
		cout << "engine was turned on" << endl;
	}
	else
	{
		cout << "engine is already enabled" << endl;
	}
	return result;
}

bool CCarMenu::TurnOffEngine()
{
	auto result = m_car.TurnOffEngine();
	if (result)
	{
		cout << "engine was turned off" << endl;
	}
	else
	{
		cout << "engine wasn't turned off" << endl;
	}
	return result;
}

Gear IntToGear(const int gear)
{
	if (gear >= -1 && gear <= 5)
	{
		switch (gear)
		{
		case -1:
			return Gear::Reverse;
		case 0:
			return Gear::Neutral;
		case 1:
			return Gear::First;
		case 2:
			return Gear::Second;
		case 3:
			return Gear::Third;
		case 4:
			return Gear::Fourth;
		case 5:
			return Gear::Fifth;
		default:
			throw logic_error("<unknown gear>");
		}
	}
	throw runtime_error("gear must be -1..5");
}

bool CCarMenu::SetGear(int gear)
{
	try
	{
		auto carGear = IntToGear(gear);
		auto result = m_car.SetGear(carGear);
		if (result)
		{
			cout << "selected gear " << gear << endl;
		}
		else
		{
			cout << "gear didn't change" << endl;
		}
		return result;
	}
	catch (exception & exception)
	{
		cout << "gear didn't change" << endl;
		cerr << exception.what() << endl;
		return false;
	}
}

bool CCarMenu::SetSpeed(int speed)
{
	auto result = m_car.SetSpeed(speed);
	if (result)
	{
		cout << "selected speed " << speed << endl;
	}
	else
	{
		cout << "speed didn't changed" << endl;
	}
	return result;
}

void CCarMenu::RunCommand(string & command)
{
	boost::to_lower(command);
	vector<string> commands;
	boost::split(commands, command, boost::is_any_of(" "));
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
	else if ((commands[0] == "setgear") && IsNumber(commands[1]))
	{
		SetGear(stoi(commands[1]));
	}
	else if ((commands[0] == "setspeed") && IsNumber(commands[1]))
	{
		SetSpeed(stoi(commands[1]));
	}
	else
	{
		cout << "Unknown command" << endl;
	}
}
