#include "stdafx.h"
#include "HTML_utils.h"

using namespace std;

bool ParseURL(string const & url, Protocol &  protocol, int & port, string & host, string & document)
{
	regex regexStr1("(http|https|ftp|HTTP|HTTPS|FTP)://([0-9a-z\.-]+):([0-9]+)/([^[:s:]]+){0,}");

	smatch result;
	if (regex_match(url, result, regexStr1))
	{
		string regProt(result[1].first, result[1].second);
		if (regProt == "http" || regProt == "HTTP")
		{
			protocol = Protocol::HTTP;
		}
		if (regProt == "https" || regProt == "HTTPS")
		{
			protocol = Protocol::HTTPS;
		}
		if (regProt == "ftp" || regProt == "FTP")
		{
			protocol = Protocol::FTP;
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
		if (regProt == "http" || regProt == "HTTP")
		{
			protocol = Protocol::HTTP;
		}
		if (regProt == "https" || regProt == "HTTPS")
		{
			protocol = Protocol::HTTPS;
		}
		if (regProt == "ftp" || regProt == "FTP")
		{
			protocol = Protocol::FTP;
		}

		if (protocol == Protocol::HTTP)
		{
			port = 80;
		}
		if (protocol == Protocol::HTTPS)
		{
			port = 443;
		}
		if (protocol == Protocol::FTP)
		{
			port = 21;
		}

		string regHost(result[2].first, result[2].second);
		host = regHost;

		string regDoc(result[3].first, result[3].second);
		document = regDoc;

		return true;
	}



	return false;
}