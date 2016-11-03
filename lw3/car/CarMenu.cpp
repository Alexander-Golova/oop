#include "stdafx.h"

#include "CarMenu.h"

using namespace std;


CCarMenu::CCarMenu(CCar & car)
	:m_car(car)
{
}

void Info(const CCar & car)
{
	cout << "Состояние двигателя: " << ((car.IsEngineTurnOn()) ? ("двигатель включен") : ("двигатель выключен")) << endl;
	cout << "Скорость: " << car.GetSpeed() << endl;

}

void CCarMenu::GetInfo() const
{
	Info(m_car);
}

void CCarMenu::RunCommand(std::string & command)
{
	boost::to_lower(command);
	vector<string> commands;
	boost::split(commands, command, boost::is_any_of(" "));
	if ((commands[0] == "info") && (commands.size() == 1))
	{
		GetInfo();
	}
}
