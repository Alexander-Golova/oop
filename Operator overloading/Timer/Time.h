#pragma once


class CTime
{
public:
	// инициализирует время заданным количеством часов, минут и секунд
	CTime(unsigned hours, unsigned minutes, unsigned seconds = 0);

private:
	unsigned m_hours;
	unsigned m_minutes;
	unsigned m_seconds;

};
