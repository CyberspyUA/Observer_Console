#pragma once
/**
 * \brief Клас-інтерфейс спостерігача
 * Містить методи:
 * StartObservation - виконання певних дій на початку слідкування за певним об'єктом у консолі.
 * StopObservation - виконання певних дій на завершення слідкування за певним об'єктом у консолі.
 */
class IConsoleObserver
{
public:
	virtual void StartObservation(HANDLE handleConsole) = 0;
	virtual void StopObservation(HANDLE handleConsole) = 0;
	virtual ~IConsoleObserver() = default;
};