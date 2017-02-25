#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <VersionHelpers.h>

const char *GetOsVersionName()
{
	if (IsWindows8Point1OrGreater())
	{
		return "8.1";
	}
	if (IsWindows8OrGreater())
	{
		return "8";
	}
	if (IsWindows7OrGreater())
	{
		return "7";
	}
	if (IsWindowsVistaOrGreater())
	{
		return "Vista";
	}
	if (IsWindowsXPOrGreater())
	{
		return "XP";
	}
	return "Unknown";
}

void PrintVersion()
{
	const char *osVersionName = GetOsVersionName();

	printf("Running under Windows %s\n", osVersionName);
}

int main()
{
	PrintVersion();
	
	return 0;
}
