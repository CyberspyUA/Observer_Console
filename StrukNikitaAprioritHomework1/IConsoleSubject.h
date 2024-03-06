#pragma once
#include <memory>

#include "IConsoleObserver.h"

/**
 * \brief 
 */
class IConsoleSubject
{
	public:
	virtual void Attach(std::shared_ptr<IConsoleObserver> observer) = 0; //Додає вказівник на спостерігача із контейнера
    virtual void Detach(std::shared_ptr<IConsoleObserver> observer) = 0; //Видаляє вказівник на спостерігач із контейнера
    virtual void NotifyEntrance(const HANDLE &handleConsole) = 0; //Повідомляє усі привязані спостерігачі проте, що об'єкт з'явився у консолі.
    virtual void NotifyLeaving(const HANDLE &handleConsole) = 0; //Повідомляє усі привязані спостерігачі проте, що об'єкт видалений із консолі.
	virtual ~IConsoleSubject() = default;
};

