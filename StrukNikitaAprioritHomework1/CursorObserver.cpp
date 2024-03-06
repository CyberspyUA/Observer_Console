#include "CursorObserver.h"

#include <stdexcept>
#include <windows.h>

void CursorObserver::StartObservation(const HANDLE &handleConsole)
{
	WORD TextAttributes = FOREGROUND_GREEN;
	if (!SetConsoleTextAttribute(handleConsole, TextAttributes))
	{
		throw std::runtime_error("Cannot set appropriate console text attributes.");
	}
}

void CursorObserver::StopObservation(const HANDLE &handleConsole)
{
	WORD TextAttributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	if (!SetConsoleTextAttribute(handleConsole, TextAttributes))
	{
		throw std::runtime_error("Cannot set appropriate console text attributes.");
	}
}

