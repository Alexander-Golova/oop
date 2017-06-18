#include "stdafx.h"

#define FIRST_THREAD  1
#define SECOND_THREAD 2

int g_count = 0;

int g_count1 = 0;
int g_count2 = 0;

const int REPEATS = 100000000;

DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
	int threadID = *(int*)lpParam;

	for (int i = 0; i < REPEATS; ++i)
	{
		++g_count;

		switch (threadID)
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

	int id1 = FIRST_THREAD;
	int id2 = SECOND_THREAD;

	hThreads[0] = CreateThread(NULL, 0, &ThreadFunc, &id1, 0, NULL);

	if (!hThreads[0])
	{
		printf("Failed to create first thread\n");
		return 1;
	}

	printf("First thread successfully created\n");

	hThreads[1] = CreateThread(NULL, 0, &ThreadFunc, &id2, 0, NULL);

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
