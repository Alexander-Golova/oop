#pragma once
#include<map>
#include<string>
#include "StringUtilites.h"


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
	bool GetChannelName(int channel, std::string& channelName) const;
	bool GetChannelByName(int& channel, const std::string& channelName) const;
	bool DeleteChannelName(const std::string& channelName);
	
private:
	bool IsValidChannel(int channel) const;
	bool IsChannelNameExist(int channel) const;
	bool FoundByName(int& channel, const std::string& channelName) const;
	bool RemoveChannelByName(const std::string& channelName);
	void RemoveChannelByKey(int channel);

	bool m_isOn = false;
	int m_selectedChannel = 1;
	int m_PreviousChannel = 0;

	std::map<int, std::string> m_channelsData;	
};
