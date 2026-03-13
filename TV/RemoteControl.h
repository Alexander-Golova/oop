#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <map>


class CTVSet;

class CRemoteControl
{
public:
	CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	// функция-обработчик команды пользователя.
	// Возвращает true, если команда распознана и false, если были ошибки
	using Handler = std::function<bool(std::istream& args)>;

	bool TurnOn(std::istream& args);
	bool TurnOff(std::istream& args);
	bool Info(std::istream& args);

	// Отображает название команды на её обработчик
	using ActionMap = std::map<std::string, Handler>;

	CTVSet& m_tv;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};
