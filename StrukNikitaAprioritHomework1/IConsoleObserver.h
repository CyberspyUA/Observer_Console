#pragma once
/**
 * \brief Клас-інтерфейс спостерігача
 */
class IConsoleObserver
{
public:
	virtual void StartObservation(const HANDLE& handleConsole) = 0; // Виконання певних дій на початку слідкування за певним об'єктом у консолі.
	virtual void StopObservation(const HANDLE& handleConsole) = 0; // StopObservation - виконання певних дій на завершення слідкування за певним об'єктом у консолі.
	virtual ~IConsoleObserver() = default;
};