#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <tchar.h>

#define SEMAPHORE_NAME "run_single_app"

int main()
{
	HANDLE hSemaphore = NULL;

	hSemaphore = OpenSemaphore(READ_CONTROL, FALSE, _T(SEMAPHORE_NAME));

	if (hSemaphore)
	{
		printf("This application is already running!\n");
		return 0;
	}

	hSemaphore = CreateSemaphore(NULL, 0, 1, _T(SEMAPHORE_NAME));

	if (hSemaphore == NULL)
	{
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}

	printf("\nSemaphore %s was created\n", SEMAPHORE_NAME);
	printf("Press any key...\n");
	_getch();

	CloseHandle(hSemaphore);

	return 0;
}
