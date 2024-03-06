#pragma once
#include <vector>

#include "CursorObserver.h"
#include "IConsoleSubject.h"

/**
 * \brief ����, �� ������� � ��� ���������� ����, ��������� �� ��������.
 */
class CursorSubject : public IConsoleSubject
{
private:
	std::vector<std::shared_ptr<CursorObserver>> cursorObservers;
public:
	void Attach(std::shared_ptr<IConsoleObserver> observer) override; //���� �������� �� ���������� �� �������
	void Detach(std::shared_ptr<IConsoleObserver> observer) override; //������� �������� �� ���������� �� �������
	void NotifyEntrance(const HANDLE &handleConsole) override; //��������� �� �������� ����������� �����, �� ������ ������ �� ������.
	void NotifyLeaving(const HANDLE &handleConsole) override; //��������� �� �������� ����������� �����, �� ������ ������ �� ������.
	~CursorSubject() override = default;

};