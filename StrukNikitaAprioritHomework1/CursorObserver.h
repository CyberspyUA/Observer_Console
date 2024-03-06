#pragma once
#include <windows.h>

#include "IConsoleObserver.h"
/**
 * \brief Спостерігач за мишою.
 *  Спотерігатиме за місцезнаходженням миші, чи вона у межах чи поза консолі.
 */
class CursorObserver : public IConsoleObserver
{
public:
	 void StartObservation(const HANDLE &handleConsole) final; // Kурсор заходить в область консольного вікна, колір тексту в консолі змінюється.
	 void StopObservation(const HANDLE &handleConsole) final; // Kурсор полишає область консольного вікна, колір тексту в  консолі змінюється на оригінальний.
	~CursorObserver() override = default;
};

