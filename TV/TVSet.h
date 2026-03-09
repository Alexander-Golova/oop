#pragma once
//#include<vector>

class CTVSet
{
public:
	CTVSet();
	bool IsTurnedOn() const;
	void TurnOn();
	void TurnOff();
	int GetChannel() const;
	bool SelectChannel(int channel);
	bool SelectPreviousChannel();
	
private:
	bool m_isOn = false;
	int m_selectedChannel = 1;
	int m_PreviousChannel = 0;
};
