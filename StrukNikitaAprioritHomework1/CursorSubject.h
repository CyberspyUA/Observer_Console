#pragma once
#include <vector>

#include "CursorObserver.h"
#include "IConsoleSubject.h"

/**
 * \brief Клас, що виступає у ролі обролювача подій, повязаних із курсором.
 */
class CursorSubject : public IConsoleSubject
{
private:
	std::vector<std::shared_ptr<CursorObserver>> cursorObservers;
public:
	void Attach(std::shared_ptr<IConsoleObserver> observer) override; //Додає вказівник на спостерігач до вектора
	void Detach(std::shared_ptr<IConsoleObserver> observer) override; //Видаляє вказівник на спостерігач із вектора
	void NotifyEntrance(const HANDLE &handleConsole) override; //Повідомляє усі привязані спостерігачі проте, що курсор увійшов до консолі.
	void NotifyLeaving(const HANDLE &handleConsole) override; //Повідомляє усі привязані спостерігачі проте, що курсор вийшов із консолі.
	~CursorSubject() override = default;

};