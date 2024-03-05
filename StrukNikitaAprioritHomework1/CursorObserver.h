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
	void StartObservation(HANDLE handleConsole) final; // Kурсор заходить в область консольного вікна, колір тексту в консолі змінюється, а поточний час записується в лог файл з тегом "Enter".
	void StopObservation(HANDLE handleConsole) final; // Kурсор полишає область консольного вікна, колір тексту в  консолі змінюється на оригінальний і поточний час записується у лог з тегом "Leave".
	~CursorObserver() override = default;
};

