#pragma once

#include "stdafx.h"

const int HTTP_PORT = 80;
const int HTTPS_PORT = 243;
const int FTP_PORT = 21;

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

bool ParseURL(std::string const & url, Protocol &  protocol, int & port, std::string & host, std::string & document);
