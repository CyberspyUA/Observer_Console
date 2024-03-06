#pragma once
#include <windows.h>

#include "IConsoleObserver.h"
/**
 * \brief ���������� �� �����.
 *  ������������ �� ���������������� ����, �� ���� � ����� �� ���� ������.
 */
class CursorObserver : public IConsoleObserver
{
public:
	 void StartObservation(const HANDLE &handleConsole) final; // K����� �������� � ������� ����������� ����, ���� ������ � ������ ���������.
	 void StopObservation(const HANDLE &handleConsole) final; // K����� ������ ������� ����������� ����, ���� ������ �  ������ ��������� �� �����������.
	~CursorObserver() override = default;
};

