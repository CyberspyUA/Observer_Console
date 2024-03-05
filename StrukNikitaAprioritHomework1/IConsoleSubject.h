#pragma once
#include <memory>

#include "IConsoleObserver.h"

/**
 * \brief 
 */
class IConsoleSubject
{
	public:
	virtual void Attach(std::shared_ptr<IConsoleObserver> observer) = 0;
    virtual void Detach(std::shared_ptr<IConsoleObserver> observer) = 0;
    virtual void NotifyEntrance() = 0;
    virtual void NotifyLeaving() = 0;
	virtual ~IConsoleSubject() = default;
};

