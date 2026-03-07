#pragma once


class CTVSet
{
public:
	bool IsTurnedOn() const;
	
private:
	bool m_isOn = false;
	int m_selectedChannel = 1;
};
