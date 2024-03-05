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
	void StartObservation(HANDLE handleConsole) final; // K����� �������� � ������� ����������� ����, ���� ������ � ������ ���������, � �������� ��� ���������� � ��� ���� � ����� "Enter".
	void StopObservation(HANDLE handleConsole) final; // K����� ������ ������� ����������� ����, ���� ������ �  ������ ��������� �� ����������� � �������� ��� ���������� � ��� � ����� "Leave".
	~CursorObserver() override = default;
};

