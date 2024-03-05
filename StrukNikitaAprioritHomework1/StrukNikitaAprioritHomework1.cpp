#include <iostream>
#include <windows.h>

#include "CursorObserver.h"

void StartApplication()
{
	const LPCWSTR fileName = L"ActionsLogs.txt"; //Назва та формат файлу, де будуть зберігатися логи.
    const HANDLE logFile = CreateFile(fileName,
                          GENERIC_WRITE, 
                          0,
                          0,
                          CREATE_ALWAYS,
                          FILE_ATTRIBUTE_NORMAL,
                          0);
    if (logFile)
    {
        HANDLE handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        try
        {
			if (handleConsole == INVALID_HANDLE_VALUE) 
	        {
		        throw std::runtime_error("Error getting console handle.");
			}
	        while(!(GetAsyncKeyState('Q') & 0x8000)) //Поки користувач не натиснув клавішу Q.
	        {
		        CursorObserver cursorObserver;
	            DWORD bytesWritten;
	            POINT cursorPos;
                CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
				GetCursorPos(&cursorPos);
				ScreenToClient(GetConsoleWindow(), &cursorPos);
	            if(GetConsoleScreenBufferInfo(handleConsole, &consoleScreenBufferInfo))
	            {
	                if(cursorPos.x >= 0 && cursorPos.x < consoleScreenBufferInfo.dwSize.X && cursorPos.y >= 0 && cursorPos.y < consoleScreenBufferInfo.dwSize.Y)
	                {
						cursorObserver.StartObservation(handleConsole);
						WriteFile(logFile,"Enter\n",strlen("Enter\n"),&bytesWritten,nullptr);
	                }
	                else
	                {
		                cursorObserver.StopObservation(handleConsole);
                        WriteFile(logFile,"Leave\n",strlen("Leave\n"),&bytesWritten,nullptr);
	                }
	                std::cout << "Hello world!\n";
                    Sleep(1);
            		system("cls");
	            }
	            else
	            {
		            throw std::runtime_error("Error getting console buffer info.");
	            }
	        }
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
