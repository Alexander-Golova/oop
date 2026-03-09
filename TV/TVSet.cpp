#include "TVSet.h"

CTVSet::CTVSet()
	: m_isOn(false)
	, m_selectedChannel(1)
	, m_PreviousChannel(1)
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

bool CTVSet::SelectChannel(int channel)
{
	bool isAvailableChannel = (channel >= 1) && (channel <= 99);
	if (isAvailableChannel && m_isOn)
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
	m_selectedChannel = m_PreviousChannel;
	return true;	
}

bool CTVSet::SetChannelName(int channel, const std::string& channelName)
{
	if (!m_isOn)
	{
		return false;
	}

	m_channelsData[channel] = channelName;
	return true;
}
