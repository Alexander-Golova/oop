#include "RemoteControl.h"

#include "RemoteControl.h"
#include "TVSet.h"

using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output)
	: m_tv(tv)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "TurnOn", [this](istream& strm) { return TurnOn(strm); } },
		  { "TurnOff", bind(&CRemoteControl::TurnOff, this, _1) },
		  { "Info", bind(&CRemoteControl::Info, this, _1) },
	  })
{
}

bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CRemoteControl::TurnOn(std::istream& /*args*/)
{
	m_tv.TurnOn();
	m_output << "TV is turned on" << endl;
	return true;
}

bool CRemoteControl::TurnOff(std::istream& /*args*/)
{
	m_tv.TurnOff();
	m_output << "TV is turned off" << endl;
	return true;
}

bool CRemoteControl::Info(std::istream& args)
{
	int channel = m_tv.GetChannel();
	std::string channelName;

	m_output << "TV info: " << std::endl
			 << " - is turned: " << (m_tv.IsTurnedOn() ? "on" : "off") << std::endl
			 << " - selected channel: " << channel << (m_tv.GetChannelName(channel, channelName) ? " - " + channelName : "") << std::endl;
	
	std::map<int, std::string> channelsData = m_tv.GetAllChannelWithName();
	if (!channelsData.empty())
	{
		m_output << " - channels with name: " << std::endl;
		for (const auto& channelData : channelsData)
		{
			m_output << channelData.first << " - " << channelData.second << std::endl;
		}		
	}	
	return true;
}
