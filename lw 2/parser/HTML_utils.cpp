#include "stdafx.h"
#include "HTML_utils.h"

using namespace std;

string ToUpCase(string str)
{
	locale loc;
	for (auto & ch : str)
	{
		ch = toupper(ch, loc);
	}
	return str;
}

bool GetProtocol(const string & st, Protocol & protocol)
{
	if (ToUpCase(st) == "HTTP")
	{
		protocol = Protocol::HTTP;
		return true;
	}
	if (ToUpCase(st) == "HTTPS")
	{
		protocol = Protocol::HTTPS;
		return true;
	}
	if (ToUpCase(st) == "FTP")
	{
		protocol = Protocol::FTP;
		return true;
	}
	return false;
}

int GetPort(const Protocol & protocol)
{
	if (protocol == Protocol::HTTP)
	{
		return HTTP_PORT;
	}
	if (protocol == Protocol::HTTPS)
	{
		return HTTPS_PORT;
	}
	if (protocol == Protocol::FTP)
	{
		return FTP_PORT;
	}
	return -1;
}

bool ParseURL(string const & url, Protocol &  protocol, int & port, string & host, string & document)
{
	regex regexStr1("(http|https|ftp|HTTP|HTTPS|FTP)://([0-9a-z\.-]+):([0-9]+)/([^[:s:]]+){0,}");
	smatch result;
	if (regex_match(url, result, regexStr1))
	{
		string regProt(result[1].first, result[1].second);
		if (!GetProtocol(regProt, protocol))
		{
			return false;
		}		
		string regPort(result[3].first, result[3].second);
		port = atoi(regPort.c_str());
		if (port < 1 || port > 65535)
		{
			return false;
		}		
		string regHost(result[2].first, result[2].second);
		host = regHost;		
		string regDoc(result[4].first, result[4].second);
		document = regDoc;
		return true;
	}

	regex regexStr2("(http|https|ftp|HTTP|HTTPS|FTP)://([0-9a-z\.-]+)/([^[:s:]]+){0,}");

	if (regex_match(url, result, regexStr2))
	{
		string regProt(result[1].first, result[1].second);
		if (!GetProtocol(regProt, protocol))
		{
			return false;
		}
		port = GetPort(protocol);		
		string regHost(result[2].first, result[2].second);
		host = regHost;
		string regDoc(result[3].first, result[3].second);
		document = regDoc;
		return true;
	}
	return false;
}
