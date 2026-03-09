#pragma once
#include<map>
#include<string>


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
	bool SetChannelName(int channel, const std::string& channelName);
	
private:
	bool m_isOn = false;
	int m_selectedChannel = 1;
	int m_PreviousChannel = 0;

	std::map<int, std::string> m_channelsData;	
};
