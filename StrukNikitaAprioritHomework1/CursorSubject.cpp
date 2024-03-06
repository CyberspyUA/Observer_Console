#include "CursorSubject.h"

#include <string>


void CursorSubject::Attach(std::shared_ptr<IConsoleObserver> observer)
{
	if(std::shared_ptr<CursorObserver> cursorObserverPtr = std::dynamic_pointer_cast<CursorObserver>(observer))
	cursorObservers.push_back(cursorObserverPtr);
}

void CursorSubject::Detach(std::shared_ptr<IConsoleObserver> observer)
{
	if(std::shared_ptr<CursorSubject> cursorObserverPtr = std::dynamic_pointer_cast<CursorSubject>(observer))
	{
		auto observerIter = std::find(cursorObservers.begin(), cursorObservers.end(), observer);
        if (observerIter != cursorObservers.end()) {
            cursorObservers.erase(observerIter);
        }
	}
}
void CursorSubject::NotifyEntrance(const HANDLE &handleConsole)
{
	for (auto observer : cursorObservers)
	{
		observer->StartObservation(handleConsole);
	}
}
void CursorSubject::NotifyLeaving(const HANDLE &handleConsole)
{
	for (auto observer : cursorObservers)
	{
		observer->StopObservation(handleConsole);
	}
}