#include "TVSet.h"

CTVSet::CTVSet()
	: m_isOn(false)
	, m_selectedChannel(1)
	, m_PreviousChannel(0)
{};

bool CTVSet::IsTurnedOn() const
{
	return m_isOn;
}

void CTVSet::TurnOn()
{
	m_isOn = true;
}

void CTVSet::TurnOff()
{
	m_isOn = false;
}

int CTVSet::GetChannel() const
{
	return m_isOn ? m_selectedChannel : 0;
}

bool CTVSet::IsValidChannel(int channel) const
{
	return (channel >= 1 && channel <= 99);
}

bool CTVSet::SelectChannel(int channel)
{
	if (IsValidChannel(channel) && m_isOn)
	{
		m_PreviousChannel = m_selectedChannel;
		m_selectedChannel = channel;
		return true;
	}
	return false;
}

bool CTVSet::SelectPreviousChannel()
{
	if (!m_isOn || (m_PreviousChannel == 0))
	{
		return false;
	}
	std::swap(m_selectedChannel, m_PreviousChannel);
	return true;	
}

bool CTVSet::SetChannelName(int channel, const std::string& channelName)
{
	std::string trimmedChannelName = RemoveExtraBlanks(channelName);
	if (!m_isOn || !IsValidChannel(channel) || trimmedChannelName.empty())
	{
		return false;
	}

	m_channelsData[channel] = trimmedChannelName;
	return true;
}

bool CTVSet::GetChannelName(int channel, std::string& channelName) const
{
	if (!m_isOn || !IsValidChannel(channel) || !IsChannelNameExist(channel))
	{
		return false;
	}
	channelName = m_channelsData.at(channel);
	
	return true;
}

bool CTVSet::IsChannelNameExist(int channel) const
{
	return m_channelsData.find(channel) != m_channelsData.end();
}

bool CTVSet::GetChannelByName(const std::string& channelName, int& channel) const
{
	if (!m_isOn || !IsValidChannel(channel) || FoundByName(channelName, channel))
	{
		return false;
	}
	return FoundByName(channelName, channel);	
}

bool CTVSet::FoundByName(const std::string& channelName, int& channel) const
{
	auto isEqual = [&channelName](const std::pair<int, std::string>& element) {
		return element.second == channelName;
	};

	auto it = std::find_if(m_channelsData.begin(), m_channelsData.end(), isEqual);

	if (it != std::end(m_channelsData))
	{
		channel = it->first;

		return true;
	}

	return false;
}

bool CTVSet::DeleteChannelName(const std::string& channelName)
{
	if (!m_isOn)
	{
		return false;
	}
	return RemoveChannelByName(channelName);
}

bool CTVSet::RemoveChannelByName(const std::string& channelName)
{
	int channel = 0;
	if (!FoundByName(channelName, channel))
	{
		return false;
	}

	RemoveChannelByKey(channel);

	return true;
}

void CTVSet::RemoveChannelByKey(int channel)
{
	m_channelsData.erase(channel);
}