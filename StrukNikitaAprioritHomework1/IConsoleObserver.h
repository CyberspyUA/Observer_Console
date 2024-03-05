#pragma once
/**
 * \brief ����-��������� �����������
 * ̳����� ������:
 * StartObservation - ��������� ������ �� �� ������� ���������� �� ������ ��'����� � ������.
 * StopObservation - ��������� ������ �� �� ���������� ���������� �� ������ ��'����� � ������.
 */
class IConsoleObserver
{
public:
	virtual void StartObservation(HANDLE handleConsole) = 0;
	virtual void StopObservation(HANDLE handleConsole) = 0;
	virtual ~IConsoleObserver() = default;
};