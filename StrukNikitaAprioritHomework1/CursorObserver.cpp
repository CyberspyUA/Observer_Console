#include "CursorObserver.h"

#include <windows.h>

void CursorObserver::StartObservation(HANDLE handleConsole)
{
	WORD TextAttributes = FOREGROUND_GREEN;
	if (!SetConsoleTextAttribute(handleConsole, TextAttributes))
	{
		throw "Cannot set appropriate console text attributes.";
	}
}

void CursorObserver::StopObservation(HANDLE handleConsole)
{
	WORD TextAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	if (!SetConsoleTextAttribute(handleConsole, TextAttributes))
	{
		throw "Cannot set appropriate console text attributes.";
	}
}

