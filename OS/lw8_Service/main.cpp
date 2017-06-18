#include "stdafx.h"
#include "FileSysEmulator.h"

SERVICE_STATUS g_ServiceStatus = { 0 };
SERVICE_STATUS_HANDLE g_StatusHandle = NULL;

void WINAPI ServiceMain(DWORD argc, LPTSTR *argv);
void WINAPI ServiceCtrlHandler(DWORD);

bool ServiceStartPending();
bool ServiceRun();
bool ServiceStop(DWORD dwExitCode, DWORD dwCheckPoint);

using namespace std;

void InteractionThroughPipe();
bool SendMessageToClient(const string &msg);
bool IsStopServiceRequest(const string &msg);
bool IsDisconnectRequest(const string &msg);

#define SERVICE_NAME _T("File system emulator service")

const DWORD BUFFER_SIZE = 2097152; // 2 Mb

HANDLE g_hPipe;
bool g_stop = false;

int _tmain(int argc, _TCHAR* argv[])
{
	SERVICE_TABLE_ENTRY ServiceTable[] =
	{
		{ SERVICE_NAME, static_cast<LPSERVICE_MAIN_FUNCTION>(ServiceMain) },
		{ NULL, NULL }
	};

	if (StartServiceCtrlDispatcher(ServiceTable) == FALSE)
	{
		return GetLastError();
	}

	return 0;
}

void WINAPI ServiceMain(DWORD argc, LPTSTR *argv)
{
	g_StatusHandle = RegisterServiceCtrlHandler(SERVICE_NAME, ServiceCtrlHandler);

	if (g_StatusHandle == NULL)
	{
		return;
	}

	ZeroMemory(&g_ServiceStatus, sizeof(g_ServiceStatus));

	if (!ServiceStartPending() || !ServiceRun())
	{
		return;
	}

	InteractionThroughPipe();

	ServiceStop(0, 3);
}

bool ServiceStartPending()
{
	g_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	g_ServiceStatus.dwControlsAccepted = 0;
	g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	g_ServiceStatus.dwWin32ExitCode = 0;
	g_ServiceStatus.dwServiceSpecificExitCode = 0;
	g_ServiceStatus.dwCheckPoint = 0;

	if (SetServiceStatus(g_StatusHandle, &g_ServiceStatus) == FALSE)
	{
		OutputDebugString(_T("File system emulator service: ServiceMain: SetServiceStatus returned error"));
		return false;
	}

	return true;
}

bool ServiceRun()
{
	g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	g_ServiceStatus.dwWin32ExitCode = 0;
	g_ServiceStatus.dwCheckPoint = 0;

	if (SetServiceStatus(g_StatusHandle, &g_ServiceStatus) == FALSE)
	{
		OutputDebugString(_T("File system emulator service: ServiceMain: SetServiceStatus returned error"));
		return false;
	}

	OutputDebugString(_T("File system emulator service: ServiceMain: SetServiceStatus SERVICE_RUNNING success"));

	return true;
}

bool ServiceStop(DWORD dwExitCode, DWORD dwCheckPoint)
{
	g_ServiceStatus.dwControlsAccepted = 0;
	g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
	g_ServiceStatus.dwWin32ExitCode = dwExitCode;
	g_ServiceStatus.dwCheckPoint = dwCheckPoint;

	if (SetServiceStatus(g_StatusHandle, &g_ServiceStatus) == FALSE)
	{
		OutputDebugString(_T("File system emulator service: ServiceStop: SetServiceStatus returned error"));
		return false;
	}

	OutputDebugString(_T("File system emulator service: ServiceStop: SetServiceStatus SERVICE_STOPPED success"));

	return true;
}

void WINAPI ServiceCtrlHandler(DWORD CtrlCode)
{
	switch (CtrlCode)
	{
	case SERVICE_CONTROL_STOP:
		break;
	default:
		break;
	}
}

void InteractionThroughPipe()
{
	g_hPipe = CreateNamedPipe(L"\\\\.\\pipe\\fse_pipe", PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE | PIPE_WAIT, 1, 0, 0, 0, NULL);

	if (g_hPipe == INVALID_HANDLE_VALUE)
	{
		OutputDebugString(_T("File system emulator service: ServiceMain: INVALID_HANDLE_VALUE"));

		ServiceStop(ERROR_INVALID_HANDLE, 1);
		return;
	}

	StartFileSystemEmulator();

	static char buffer[BUFFER_SIZE];
	DWORD numBytes = 0;

	while (!g_stop)
	{
		if (!ConnectNamedPipe(g_hPipe, NULL))
		{
			OutputDebugString(_T("File system emulator service: ServiceMain: ERROR_PIPE_NOT_CONNECTED"));
			break;
		}

		GetFileSystemEmulatorInfo();
		SendMessageToClient(GetActionResultMessage());

		while (1)
		{
			if (!ReadFile(g_hPipe, buffer, BUFFER_SIZE, &numBytes, NULL))
			{
				break;
			}

			string cmd(buffer, numBytes);

			if (IsStopServiceRequest(cmd) || IsDisconnectRequest(cmd))
			{
				SendMessageToClient("disconnect");
				break;
			}

			HandleCommand(cmd);
			SendMessageToClient(GetActionResultMessage());
		}

		DisconnectNamedPipe(g_hPipe);
	}

	CloseHandle(g_hPipe);
}

bool SendMessageToClient(const string &msg)
{
	DWORD numBytes = 0;

	if (!WriteFile(g_hPipe, msg.c_str(), msg.length(), &numBytes, NULL))
	{
		OutputDebugString(_T("File system emulator service: WriteActionResultMessage: Failed to write data in the pipe"));
		return false;
	}

	return true;
}

bool IsStopServiceRequest(const string &msg)
{
	if (regex_search(msg, regex("exit")) || regex_search(msg, regex("fexit")))
	{
		g_stop = true;
		return true;
	}

	return false;
}

bool IsDisconnectRequest(const string &msg)
{
	return regex_search(msg, regex("disconnect"));
}
