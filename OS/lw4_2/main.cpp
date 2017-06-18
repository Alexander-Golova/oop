#include "stdafx.h"

#define FIRST_THREAD  0
#define SECOND_THREAD 1

int g_count = 0;

int g_count1 = 0;
int g_count2 = 0;

const int REPEATS = 1000;

boolean g_flag[2] = { false, false };
int g_turn = FIRST_THREAD;

DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
	int threadNumber = *(int*)lpParam;
	int otherThreadNumber = (threadNumber == FIRST_THREAD) ? SECOND_THREAD : FIRST_THREAD;

	for (int i = 0; i < REPEATS; ++i)
	{
		g_flag[threadNumber] = true;

		while (g_flag[otherThreadNumber])
		{
			if (g_turn == otherThreadNumber)
			{
				g_flag[threadNumber] = false;
				while (g_turn == otherThreadNumber);
				g_flag[threadNumber] = true;
			}
		}

		// ----- Critical section -------------
		++g_count;

		g_turn = otherThreadNumber;
		g_flag[threadNumber] = false;
		// ----- End of critical section ------

		switch (threadNumber)
		{
		case FIRST_THREAD:
			++g_count1;
			break;
		case SECOND_THREAD:
			++g_count2;
		}
	}

	ExitThread(0);
}

int main(int argc, char *argv[])
{
	HANDLE hThreads[2];

	int firstThreadNumber = FIRST_THREAD;
	int secondThreadNumber = SECOND_THREAD;

	hThreads[0] = CreateThread(NULL, 0, &ThreadFunc, &firstThreadNumber, 0, NULL);

	if (!hThreads[0])
	{
		printf("Failed to create first thread\n");
		return 1;
	}

	printf("First thread successfully created\n");

	hThreads[1] = CreateThread(NULL, 0, &ThreadFunc, &secondThreadNumber, 0, NULL);

	if (!hThreads[1])
	{
		printf("Failed to create second thread\n");
		return 1;
	}

	printf("Second thread successfully created\n");

	if (WaitForMultipleObjects(2, hThreads, TRUE, INFINITE) == WAIT_FAILED)
	{
		printf("Failed to join threads\n");
		return 1;
	}

	printf("\ng_count: %d from %d\n", g_count, REPEATS * 2);
	printf("g_count1: %d from %d\n", g_count1, REPEATS);
	printf("g_count2: %d from %d\n\n", g_count2, REPEATS);

	CloseHandle(hThreads[0]);
	CloseHandle(hThreads[1]);

	return 0;
}
