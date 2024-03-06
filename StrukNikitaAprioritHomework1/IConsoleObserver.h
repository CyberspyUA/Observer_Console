#pragma once
/**
 * \brief ����-��������� �����������
 */
class IConsoleObserver
{
public:
	virtual void StartObservation(const HANDLE& handleConsole) = 0; // ��������� ������ �� �� ������� ���������� �� ������ ��'����� � ������.
	virtual void StopObservation(const HANDLE& handleConsole) = 0; // StopObservation - ��������� ������ �� �� ���������� ���������� �� ������ ��'����� � ������.
	virtual ~IConsoleObserver() = default;
};