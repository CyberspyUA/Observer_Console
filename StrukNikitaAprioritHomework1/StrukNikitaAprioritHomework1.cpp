#include <iostream>
#include <windows.h>
#include <ctime>

#include "CursorObserver.h"
#include "CursorSubject.h"

/**
 * \brief ����� ���������� ������ ������ ����������.
 * ����� ���������:
 * 1) �������� ����� �����. ϳ��� �����, ��������� ���� ��� ������.
 * � ��� ����� - ���������� ������ ����������. � ��� ������� - ���������� ������� ���� ������ �� �������� ������� � �������.
 * 2) ������������ ���������� ��� ����������� �������.
 * � ��� ����� - ���������� ������ ����������. � ��� ������� - ���������� ������� ���� ������ �� �������� ������� � �������.
 * 3) ������ ���������� �� ��'���, �� ���� ���� �������� �������������. ������ �������� �� ����������� �� ��'����.
 * 4) ������������ ���������� ��� ���� ����������� �������. �������� ������ �� ������ ����.
 * 5) �������� �������� �� �������� ����, ���� �� ���� ��������� ������ Q.
 *	5.1) �������� ���������� ���� �� ������ ���������� � ���������� �볺������ ������.
 *	5.2) ��������� ���������� ����������� ���� �� ���� ���������. ���������� ������ �� ������ ����������� ����.
 *	5.3) ��������� ������ �� ������ ���������. �������� ���������� ��� ���. ���������� ��� � ��������� ������. �������� ��� � � ������.
 *	5.4) ���������� - �� ������ ���� � ���� ����������� ����������.
 *	���� ��� - ������� ���� ������ ������ �� �������, �������� � ��������� ���� ��� ����� �� ����� Enter.
 *	���� � - ��������� ���� ������ �� ����� (�� ����), �������� � ��������� ���� ��� ����� �� ����� Leave.
 * 6) ������� ����� Hello world! ��� �������� ������ �����������.
 * 7) ��� �������� �� ������ Q - ��������� �������� �� ����������� �� ��'����, ��������� ���� ��� ���� �� ��������� ������ ����������.
 */
void StartApplication()
{
	const LPCWSTR fileName = L"ActionsLogs.txt"; //����� �� ������ �����, �� ������ ���������� ����.
	if (const HANDLE logFile = CreateFile(fileName, //����� ������������ �����
	                                      GENERIC_WRITE, //����������� ������ �� �����
	                                      0, //����������� ����� �������� ������� �� �����
	                                      0,//�������� �� ��������� SECURITY_ATTRIBUTES. ���� ��������: �������, �� ���� ���������� ���������� ���� ������������ �������� ���������.
	                                      CREATE_ALWAYS, //ĳ�, ��� ������� �������� ��� ������, ���� ���� ��� �� ����.
	                                      FILE_ATTRIBUTE_NORMAL, //�������� �� ������� �����. ���� ��������: � ����� �� ����������� ����� ��������. ������� ������ ���� � ��� ���� �������� ������������.
	                                      0)) //�� ������ ���������� �� ���� ������� � ������ ������� GENERIC_READ? 
    {
        HANDLE handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        try
        {
			if (handleConsole == INVALID_HANDLE_VALUE) 
	        {
		        throw std::runtime_error("Error getting console handle.");
			}

			std::shared_ptr<CursorObserver> cursorObserver = std::make_shared<CursorObserver>();
        	CursorSubject cursorSubject;
        	cursorSubject.Attach(cursorObserver);

			HWND consoleWindow = GetConsoleWindow();
			RECT windowRectangle;
			GetWindowRect(consoleWindow, &windowRectangle);
			int consoleWindowWidth = windowRectangle.right - windowRectangle.left;
			int consoleWindowHeight = windowRectangle.bottom - windowRectangle.top;
	        while(!(GetAsyncKeyState('Q'))) //���� ���������� �� �������� ������ Q.
	        {
		            DWORD bytesWritten;

		            POINT cursorPos;
                    GetCursorPos(&cursorPos);
					ScreenToClient(GetConsoleWindow(), &cursorPos);

                    time_t timer;
	            	tm timeInformation{};
	                char timeBuffer[26];
					// �������� �������� ��� � �������� ���� � 'timer'
	                time(&timer);
					// ���������� �������� ��� � 'timer' � �������� ��������� ���� 'timeInformation'
					localtime_s(&timeInformation, &timer);
					// ³���������� ���������� ��� ������� ��� � ����� � �������� �� � 'timeBuffer'
                    asctime_s(timeBuffer, sizeof(timeBuffer), &timeInformation);

	                if(cursorPos.x >= 0 && cursorPos.x < consoleWindowWidth && cursorPos.y >= 0 && cursorPos.y < consoleWindowHeight) //������ ������ �� ������
	                {
						cursorSubject.NotifyEntrance(handleConsole);
						std::string logMessage = "|Enter|" + std::string(timeBuffer);
						//������� ��� ����� ������� � ������� �� ����� Enter
						WriteFile(logFile,logMessage.c_str(),strlen(logMessage.c_str()),&bytesWritten,nullptr); 
	                }
	                else //������ ������ �� ������
	                {
						cursorSubject.NotifyLeaving(handleConsole);
                        std::string logMessage = "|Leave|" + std::string(timeBuffer);
						//������� ��� ������ ������� � ������� �� ����� Leave
                        WriteFile(logFile,logMessage.c_str(),strlen(logMessage.c_str()),&bytesWritten,nullptr);
	                }
	                std::cout << "Hello world!\n";
                    Sleep(1000);
	          
	        }
			cursorSubject.Detach(cursorObserver);
        }
        catch(const std::runtime_error& errorName)
        {
            std::cout << "Error: "<< errorName.what() << "\n";
            CloseHandle(logFile);
        }
    	Sleep(100);
        CloseHandle(logFile);
    }
    else
    {
        throw std::runtime_error("File creation failed.");
    }
}
int main()
{
    try
    {
	    StartApplication();
    }
    catch(...)
    {
	    std::cerr << "Error: " << GetLastError() << '\n';
        return EXIT_FAILURE;
    }
    return 0;
}
