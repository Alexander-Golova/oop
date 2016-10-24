#pragma once

#include "stdafx.h"
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

bool ParseURL(std::string const & url, Protocol &  protocol, int & port, std::string & host, std::string & document);
