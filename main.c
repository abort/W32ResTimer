/*
Written by J. Dijkstra (abort@digitalise.net), 2012
Feel free to use this example in any format/project (no licensing), although using these API's will be at your own risk :).
*/

#include <Windows.h>
#pragma warning(disable: 4005)
#include <ntstatus.h>
#pragma warning(default: 4005)
#include <stdio.h>

typedef NTSTATUS (NTAPI* pSetTimerResolution)(ULONG RequestedResolution, BOOLEAN Set, PULONG ActualResolution);
typedef NTSTATUS (NTAPI* pQueryTimerResolution)(PULONG MinimumResolution, PULONG MaximumResolution, PULONG CurrentResolution);

int main(void)
{
	NTSTATUS status;
	pSetTimerResolution setFunction;
	pQueryTimerResolution queryFunction;
	ULONG minResolution, maxResolution, actualResolution;
	const HINSTANCE hLibrary = LoadLibrary("NTDLL.dll");
	if (hLibrary == NULL)
	{
		printf("Failed to load NTDLL.dll (%d)\n", GetLastError());
		return 1;
	}

	queryFunction = (pQueryTimerResolution)GetProcAddress(hLibrary, "NtQueryTimerResolution");
	if (queryFunction == NULL)
	{
		printf("NtQueryTimerResolution is null (%d)\n", GetLastError());
		return 1;
	}

	queryFunction(&minResolution, &maxResolution, &actualResolution);
	printf("Win32 Timer Resolution:\n\tMinimum Value:\t%u\n\tMaximum Value:\t%u\n\tActual Value:\t%u\n\n", minResolution, maxResolution, actualResolution);

	setFunction = (pSetTimerResolution)GetProcAddress(hLibrary, "NtSetTimerResolution");
	if (setFunction == NULL)
	{
		printf("NtSetTimerResolution is null (%d)\n", GetLastError());
		return 1;
	}

	printf("Setting Timer Resolution to the maximum value (%d)...\n", maxResolution);
	status = setFunction(maxResolution, TRUE, &actualResolution);
	if (status == STATUS_SUCCESS)
	{
		printf("Success! (Current resolution: %d)\n", actualResolution);
		return 0;
	}

	if (status == STATUS_TIMER_RESOLUTION_NOT_SET)
	{
		printf("Timer not set (Return Code: %d)\n", status);
		return 2;
	}

	printf("Failed, Return Value: %d (Error Code: %d)\n", status, GetLastError());
	return 1;
}