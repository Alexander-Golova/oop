#include "stdafx.h"

using namespace std;

const DWORD BUFFER_SIZE = 2097152;

int _tmain()
{
	cout << endl << "File system emulator client start..." << endl;

	HANDLE hPipe = CreateFile(L"\\\\.\\pipe\\fse_pipe", GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hPipe == INVALID_HANDLE_VALUE)
	{
		cout << "Failed to connect to named pipe" << endl;
		return 1;
	}

	string command;
	static char buffer[BUFFER_SIZE];
	DWORD numBytes = 0;

	ReadFile(hPipe, buffer, BUFFER_SIZE, &numBytes, NULL);

	string startMsg(buffer, numBytes);
	cout << endl << startMsg;

	cout << endl << "> ";

	while (getline(cin, command))
	{
		if (!WriteFile(hPipe, command.c_str(), command.length(), &numBytes, NULL))
		{
			cout << "Failed to write data in the pipe" << endl;
		}

		if (!ReadFile(hPipe, buffer, BUFFER_SIZE, &numBytes, NULL))
		{
			cout << "Failed to read data from the pipe" << endl;
			continue;
		}

		string msg(buffer, numBytes);
		cout << endl << "service> " << msg;

		if (msg == "disconnect")
		{
			break;
		}

		cout << endl << "> ";
	}

	CloseHandle(hPipe);

	return 0;
}
