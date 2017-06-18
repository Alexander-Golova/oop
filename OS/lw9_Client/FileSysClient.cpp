#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <exception>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define BUFFER_SIZE 2048
#define DEFAULT_PORT "27015"

using namespace std;

void InitializeWinSock();
void GetAddressInfo(char *address, PADDRINFOA &addrInfo);
SOCKET CreateSocket(PADDRINFOA addrInfo);
void ConnectToServer(SOCKET sock, PADDRINFOA addrInfo);
void ShutdownSocket(SOCKET sock);
void SendMsg(SOCKET sock, const string &message);
int ReceiveMsg(SOCKET sock, string &message);
void ReleaseSockResources(SOCKET sock, PADDRINFOA addrInfo);
void InteractionLoop(SOCKET sock);

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		cout << endl << "Invalid arguments count" << endl
			<< "Usage: client.exe <server-name>" << endl;
		return 1;
	}

	cout << endl << "File system emulator client start..." << endl;

	PADDRINFOA addrInfo = nullptr;
	SOCKET sock;

	try
	{
		InitializeWinSock();
		GetAddressInfo(argv[1], addrInfo);

		sock = CreateSocket(addrInfo);

		ConnectToServer(sock, addrInfo);
		freeaddrinfo(addrInfo);

		InteractionLoop(sock);
	}
	catch (const exception &err)
	{
		cout << err.what();
		return 1;
	}

	closesocket(sock);
	WSACleanup();

	return 0;
}

void InitializeWinSock()
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		throw exception("WSAStartup failed with error!");
	}
}

void GetAddressInfo(char *address, PADDRINFOA &addrInfo)
{
	ADDRINFOA hints;
	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (getaddrinfo(address, DEFAULT_PORT, &hints, &addrInfo) != 0)
	{
		ReleaseSockResources(NULL, nullptr);
		throw exception("GetAddressInfo failed with error!");
	}
}

SOCKET CreateSocket(PADDRINFOA addrInfo)
{
	SOCKET sock = socket(addrInfo->ai_family, addrInfo->ai_socktype, addrInfo->ai_protocol);

	if (sock == INVALID_SOCKET)
	{
		ReleaseSockResources(NULL, addrInfo);
		throw exception("CreateSocket failed with error!");
	}

	return sock;
}

void ConnectToServer(SOCKET sock, PADDRINFOA addrInfo)
{
	if (connect(sock, addrInfo->ai_addr, (int)addrInfo->ai_addrlen) == SOCKET_ERROR)
	{
		ReleaseSockResources(sock, addrInfo);
		throw exception("Unable to connect to server!");
	}
}

void SendMsg(SOCKET sock, const string &message)
{
	if (send(sock, message.c_str(), message.length(), 0) == SOCKET_ERROR)
	{
		ReleaseSockResources(sock, nullptr);
		throw exception("SendMsg failed with error!");
	}
}

void ShutdownSocket(SOCKET sock)
{
	if (shutdown(sock, SD_SEND) == SOCKET_ERROR)
	{
		ReleaseSockResources(sock, nullptr);
		throw exception("ShutdownSocket failed with error!");
	}
}

int ReceiveMsg(SOCKET sock, string &message)
{
	static char buffer[BUFFER_SIZE];
	ZeroMemory(&buffer, sizeof(buffer));
	message = "";

	int result = recv(sock, buffer, BUFFER_SIZE, 0);

	if (result > 0)
	{
		message.assign(buffer, result);
		cout << endl << "service> " << message;
	}
	else
	{
		if (result == 0)
		{
			cout << "Connection closed" << endl;
		}
		else
		{
			ReleaseSockResources(sock, nullptr);
			throw exception("ReceiveMsg failed with error!");
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
	string str;
	cout << endl << "> ";

	while (getline(cin, str))
	{
		SendMsg(sock, str);

		if (str == "disconnect" || str == "exit" || str == "fexit")
		{
			ShutdownSocket(sock);
			ReceiveMsg(sock, str);

			break;
		}

		ReceiveMsg(sock, str);
		cout << endl << "> ";
	}
}
