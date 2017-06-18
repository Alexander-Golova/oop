#include "stdafx.h"
#include "FileSysEmulator.h"

#pragma comment (lib, "Ws2_32.lib")

SERVICE_STATUS g_ServiceStatus = { 0 };
SERVICE_STATUS_HANDLE g_StatusHandle = NULL;

void WINAPI ServiceMain(DWORD argc, LPTSTR *argv);
void WINAPI ServiceCtrlHandler(DWORD);

bool ServiceStartPending();
bool ServiceRun();
bool ServiceStop(DWORD dwExitCode, DWORD dwCheckPoint);

bool IsStopServiceRequest(const std::string &msg);
bool IsDisconnectRequest(const std::string &msg);

void InteractionThroughSocket();

void InitializeWinSock();
void GetAddressInfo(char *address, PADDRINFOA &addrInfo);
SOCKET CreateSocket(PADDRINFOA addrInfo);
void BindSocket(SOCKET sock, PADDRINFOA addrInfo);
void Listen(SOCKET sock);
SOCKET AcceptClientSocket(SOCKET listenSock);
void ShutdownSocket(SOCKET sock);
void SendMsg(SOCKET sock, const std::string &message);
int ReceiveMsg(SOCKET sock, std::string &message);
void ReleaseSockResources(SOCKET sock, PADDRINFOA addrInfo);
void InteractionLoop(SOCKET sock);

#define SERVICE_NAME _T("File system emulator service")
#define DEFAULT_PORT "27015"

const DWORD BUFFER_SIZE = 2048;

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

	InteractionThroughSocket();
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

bool IsStopServiceRequest(const std::string &msg)
{
	if (regex_search(msg, std::regex("exit")) || regex_search(msg, std::regex("fexit")))
	{
		return true;
	}

	return false;
}

bool IsDisconnectRequest(const std::string &msg)
{
	return regex_search(msg, std::regex("disconnect"));
}

void InteractionThroughSocket()
{
	PADDRINFOA addrInfo = nullptr;
	SOCKET listenSocket;
	SOCKET clientSocket;

	try
	{
		InitializeWinSock();
		GetAddressInfo(nullptr, addrInfo);

		listenSocket = CreateSocket(addrInfo);

		BindSocket(listenSocket, addrInfo);
		freeaddrinfo(addrInfo);

		Listen(listenSocket);
		clientSocket = AcceptClientSocket(listenSocket);

		StartFileSystemEmulator();
		GetFileSystemEmulatorInfo();

		InteractionLoop(clientSocket);

		ShutdownSocket(clientSocket);
		ReleaseSockResources(clientSocket, nullptr);
	}
	catch (const std::exception &err)
	{
		std::cout << err.what();
	}
}

void InitializeWinSock()
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		throw std::exception("WSAStartup failed with error!");
	}
}

void GetAddressInfo(char *address, PADDRINFOA &addrInfo)
{
	ADDRINFOA hints;
	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(address, DEFAULT_PORT, &hints, &addrInfo) != 0)
	{
		ReleaseSockResources(NULL, nullptr);
		throw std::exception("GetAddressInfo failed with error!");
	}
}

SOCKET CreateSocket(PADDRINFOA addrInfo)
{
	SOCKET sock = socket(addrInfo->ai_family, addrInfo->ai_socktype, addrInfo->ai_protocol);

	if (sock == INVALID_SOCKET)
	{
		ReleaseSockResources(NULL, addrInfo);
		throw std::exception("CreateSocket failed with error!");
	}

	return sock;
}

void BindSocket(SOCKET sock, PADDRINFOA addrInfo)
{
	if (bind(sock, addrInfo->ai_addr, (int)addrInfo->ai_addrlen) == SOCKET_ERROR)
	{
		ReleaseSockResources(sock, addrInfo);
		throw std::exception("BindSocket failed with error!");
	}
}

void Listen(SOCKET sock)
{
	if (listen(sock, SOMAXCONN) == SOCKET_ERROR)
	{
		ReleaseSockResources(sock, nullptr);
		throw std::exception("Listen failed with error!");
	}
}

SOCKET AcceptClientSocket(SOCKET listenSock)
{
	SOCKET clientSock = accept(listenSock, NULL, NULL);

	if (clientSock == INVALID_SOCKET)
	{
		ReleaseSockResources(listenSock, nullptr);
		throw std::exception("AcceptClientSocket failed with error!");
	}

	closesocket(listenSock);

	return clientSock;
}

void ShutdownSocket(SOCKET sock)
{
	if (shutdown(sock, SD_SEND) == SOCKET_ERROR)
	{
		ReleaseSockResources(sock, nullptr);
		throw std::exception("ShutdownSocket failed with error!");
	}
}

void SendMsg(SOCKET sock, const std::string &message)
{
	if (send(sock, message.c_str(), message.length(), 0) == SOCKET_ERROR)
	{
		ReleaseSockResources(sock, nullptr);
		throw std::exception("SendMsg failed with error!");
	}
}

int ReceiveMsg(SOCKET sock, std::string &message)
{
	static char buffer[BUFFER_SIZE];
	ZeroMemory(&buffer, sizeof(buffer));
	message = "";

	int result = recv(sock, buffer, BUFFER_SIZE, 0);

	if (result > 0)
	{
		message.assign(buffer, result);
		std::cout << std::endl << "client> " << message;
	}
	else
	{
		if (result == 0)
		{
			std::cout << std::endl << "Connection closed" << std::endl;
		}
		else
		{
			ReleaseSockResources(sock, nullptr);
			throw std::exception("ReceiveMsg failed with error!");
		}
	}

	return result;
}

void ReleaseSockResources(SOCKET sock, PADDRINFOA addrInfo)
{
	if (sock)
	{
		closesocket(sock);
	}

	if (addrInfo)
	{
		freeaddrinfo(addrInfo);
	}

	WSACleanup();
}

void InteractionLoop(SOCKET sock)
{
	int result;
	std::string str;

	do
	{
		result = ReceiveMsg(sock, str);

		if (result)
		{
			if (IsStopServiceRequest(str) || IsDisconnectRequest(str))
			{
				continue;
			}

			HandleCommand(str);
			SendMsg(sock, GetActionResultMessage());
		}
	} while (result > 0);
}