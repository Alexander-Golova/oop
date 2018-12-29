#include "stdafx.h"
#include <windows.h>
#include <stdio.h>

void PrintCurrentPriotityClass(HANDLE hProcess);
BOOL EnableDebugPrivilege(BOOL bEnable);

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Invalid arguments count!\nUsage: SetProcessPriority.exe <pid> <value>\n");
		return 1;
	}

	if (!EnableDebugPrivilege(TRUE))
	{
		printf("Failed to enable debug privilege\n");
		return 1;
	}

	DWORD dwPID = atoi(argv[1]);
	DWORD dwPriorityClass = atoi(argv[2]);

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);

	if (!hProcess)
	{
		DWORD dwError = GetLastError();
		printf("GetLastError: %d\n", dwError);
		printf("Failed to open process!\n");
		return 1;
	}

	PrintCurrentPriotityClass(hProcess);

	if (SetPriorityClass(hProcess, dwPriorityClass))
	{
		printf("Process priority has been successfully changed\n");
		PrintCurrentPriotityClass(hProcess);
	}
	else
	{
		DWORD dwError = GetLastError();
		printf("Failed to change process priority!\n");
		printf("GetLastError: %d\n", dwError);
	}

	CloseHandle(hProcess);
	return 0;
}

void PrintCurrentPriotityClass(HANDLE hProcess)
{
	DWORD dwPriorityClass;

	if (dwPriorityClass = GetPriorityClass(hProcess))
	{
		printf("Current priority class: %d\n", dwPriorityClass);
	}
	else
	{
		printf("Failed to get current priority class!\n");
	}
}

BOOL EnableDebugPrivilege(BOOL bEnable)
{
	HANDLE hToken = nullptr;
	LUID luid;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		return FALSE;
	}

	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid))
	{
		return FALSE;
	}

	TOKEN_PRIVILEGES tokenPriv;
	tokenPriv.PrivilegeCount = 1;
	tokenPriv.Privileges[0].Luid = luid;
	tokenPriv.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;

	if (!AdjustTokenPrivileges(hToken, FALSE, &tokenPriv, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
	{
		return FALSE;
	}

	return TRUE;
}
